#include "openglwindow.hpp"
#include <imgui.h>
#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "abcg.hpp"

void OpenGLWindow::handleEvent(SDL_Event& ev) {
	if (ev.type == SDL_KEYDOWN) {
		if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w)
			m_dollySpeed = 1.0f;
		if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s)
			m_dollySpeed = -1.0f;
		if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a)
			m_panSpeed = -1.0f;
		if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d)
			m_panSpeed = 1.0f;
		if (ev.key.keysym.sym == SDLK_q) m_truckSpeed = -1.0f;
		if (ev.key.keysym.sym == SDLK_e) m_truckSpeed = 1.0f;
	}
	if (ev.type == SDL_KEYUP) {
		if ((ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) &&
				m_dollySpeed > 0)
			m_dollySpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) &&
				m_dollySpeed < 0)
			m_dollySpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) &&
				m_panSpeed < 0)
			m_panSpeed = 0.0f;
		if ((ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) &&
				m_panSpeed > 0)
			m_panSpeed = 0.0f;
		if (ev.key.keysym.sym == SDLK_q && m_truckSpeed < 0) m_truckSpeed = 0.0f;
		if (ev.key.keysym.sym == SDLK_e && m_truckSpeed > 0) m_truckSpeed = 0.0f;
	}
	//glm::ivec2 mousePosition;
	//SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

	//if (event.type == SDL_MOUSEMOTION) {
	//	m_trackBallModel.mouseMove(mousePosition);
	//	m_trackBallLight.mouseMove(mousePosition);
	//}
	//if (event.type == SDL_MOUSEBUTTONDOWN) {
	//	if (event.button.button == SDL_BUTTON_LEFT) {
	//		m_trackBallModel.mousePress(mousePosition);
	//	}
	//	if (event.button.button == SDL_BUTTON_RIGHT) {
	//		m_trackBallLight.mousePress(mousePosition);
	//	}
	//}
	//if (event.type == SDL_MOUSEBUTTONUP) {
	//	if (event.button.button == SDL_BUTTON_LEFT) {
	//		m_trackBallModel.mouseRelease(mousePosition);
	//	}
	//	if (event.button.button == SDL_BUTTON_RIGHT) {
	//		m_trackBallLight.mouseRelease(mousePosition);
	//	}
	//}
	//if (event.type == SDL_MOUSEWHEEL) {
	//	m_zoom += (event.wheel.y > 0 ? 1.0f : -1.0f) / 5.0f;
	//	m_zoom = glm::clamp(m_zoom, -1.5f, 1.0f);
	//}
}

void OpenGLWindow::initializeGL() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	auto path{getAssetsPath() + "shaders/" + "texture"};
	m_program = createProgramFromFile(path + ".vert", path + ".frag");

	// Load default model
	loadModel(getAssetsPath() + "cube.obj");
	m_mappingMode = 3;  // "From mesh" option
}

void OpenGLWindow::loadModel(std::string_view path) {
	m_model.loadDiffuseTexture(getAssetsPath() + "maps/ground_texture.png");
	m_model.loadFromFile(path);
	m_model.setupVAO(m_program);


	// Use material properties from the loaded model
	m_Ka = m_model.getKa();
	m_Kd = m_model.getKd();
	m_Ks = m_model.getKs();
	m_shininess = m_model.getShininess();
}

void OpenGLWindow::paintGL() {
	update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_viewportWidth, m_viewportHeight);

	// Use currently selected program
	glUseProgram(m_program);

	// Get location of uniform variables
	GLint viewMatrixLoc{glGetUniformLocation(m_program, "viewMatrix")};
	GLint projMatrixLoc{glGetUniformLocation(m_program, "projMatrix")};
	GLint modelMatrixLoc{glGetUniformLocation(m_program, "modelMatrix")};
	GLint normalMatrixLoc{glGetUniformLocation(m_program, "normalMatrix")};
	GLint lightDirLoc{glGetUniformLocation(m_program, "lightDirWorldSpace")};
	GLint shininessLoc{glGetUniformLocation(m_program, "shininess")};
	GLint IaLoc{glGetUniformLocation(m_program, "Ia")};
	GLint IdLoc{glGetUniformLocation(m_program, "Id")};
	GLint IsLoc{glGetUniformLocation(m_program, "Is")};
	GLint KaLoc{glGetUniformLocation(m_program, "Ka")};
	GLint KdLoc{glGetUniformLocation(m_program, "Kd")};
	GLint KsLoc{glGetUniformLocation(m_program, "Ks")};
	GLint diffuseTexLoc{glGetUniformLocation(m_program, "diffuseTex")};
	GLint mappingModeLoc{glGetUniformLocation(m_program, "mappingMode")};

	// Set uniform variables used by every scene object
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_camera.m_viewMatrix[0][0]);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
	glUniform1i(diffuseTexLoc, 0);
	glUniform1i(mappingModeLoc, m_mappingMode);

	auto lightDirRotated{m_lightDir};
	glUniform4fv(lightDirLoc, 1, &lightDirRotated.x);
	glUniform4fv(IaLoc, 1, &m_Ia.x);
	glUniform4fv(IdLoc, 1, &m_Id.x);
	glUniform4fv(IsLoc, 1, &m_Is.x);

	// Set uniform variables of the current object
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

	auto modelViewMatrix{glm::mat3(m_camera.m_viewMatrix * m_modelMatrix)};
	glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

	glUniform1f(shininessLoc, m_shininess);
	glUniform4fv(KaLoc, 1, &m_Ka.x);
	glUniform4fv(KdLoc, 1, &m_Kd.x);
	glUniform4fv(KsLoc, 1, &m_Ks.x);

	m_model.render(m_model.getNumTriangles());

	glUseProgram(0);
}

void OpenGLWindow::paintUI() {
	abcg::OpenGLWindow::paintUI();
	glFrontFace(GL_CW);
	auto aspect{static_cast<float>(m_viewportWidth) /
		static_cast<float>(m_viewportHeight)};
	m_projMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 5.0f);
}

void OpenGLWindow::resizeGL(int width, int height) {
	m_viewportWidth = width;
	m_viewportHeight = height;
}

void OpenGLWindow::terminateGL() {
	glDeleteProgram(m_program);
}

void OpenGLWindow::update() {
	float deltaTime{static_cast<float>(getDeltaTime())};

	// Update LookAt camera
	m_camera.dolly(m_dollySpeed * deltaTime);
	m_camera.truck(m_truckSpeed * deltaTime);
	m_camera.pan(m_panSpeed * deltaTime);
}
