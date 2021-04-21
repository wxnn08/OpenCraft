#include "openglwindow.hpp"
#include <imgui.h>
#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "abcg.hpp"

void OpenGLWindow::handleEvent(SDL_Event& ev) {
	m_eventHandler.handleEvent(ev, m_dollySpeed, m_panSpeed, m_truckSpeed);
}

void OpenGLWindow::initializeGL() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	auto path{getAssetsPath() + "shaders/" + "texture"};
	m_program = createProgramFromFile(path + ".vert", path + ".frag");

	// Load default model
	loadModel(getAssetsPath() + "cube.obj");
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

	// Set uniform variables used by every scene object
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_camera.m_viewMatrix[0][0]);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_camera.m_projMatrix[0][0]);
	glUniform1i(diffuseTexLoc, 0);

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

	m_model.render();

	glUseProgram(0);
}

void OpenGLWindow::paintUI() {
	abcg::OpenGLWindow::paintUI();
	glFrontFace(GL_CW);
	m_camera.computeProjectionMatrix(m_viewportWidth, m_viewportHeight);
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
