#include "openglwindow.hpp"
#include <imgui.h>
#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/vec3.hpp>
#include "abcg.hpp"
#include <fmt/core.h>

void OpenGLWindow::handleEvent(SDL_Event& ev) {
	m_eventHandler.handleEvent(ev, m_dollySpeed, m_panSpeed, m_truckSpeed);
}

void OpenGLWindow::initializeGL() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	auto path{getAssetsPath() + "shaders/" + "texture"};
	m_program = createProgramFromFile(path + ".vert", path + ".frag");

	//m_map = new Map();
	//m_map->initialize(getAssetsPath());
	//m_map->loadModel(getAssetsPath(), m_program);

	m_sea = new Sea(
			glm::vec3{0.0f, -0.2f, 0.0f},
			glm::vec3{50.0f, 1.0f, 50.0f});
	m_sea->loadModel(getAssetsPath(), m_program);
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
	GLint noiseTexLoc{glGetUniformLocation(m_program, "noiseTex")};

	GLint timeLoc{glGetUniformLocation(m_program, "time")};

	// Set uniform variables used by every scene object
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_camera.m_viewMatrix[0][0]);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_camera.m_projMatrix[0][0]);
	glUniform1i(diffuseTexLoc, 0);
	glUniform1i(noiseTexLoc, 1);

	auto lightDirRotated{m_lightDir};
	glUniform4fv(lightDirLoc, 1, &lightDirRotated.x);
	glUniform4fv(IaLoc, 1, &m_Ia.x);
	glUniform4fv(IdLoc, 1, &m_Id.x);
	glUniform4fv(IsLoc, 1, &m_Is.x);

	//for(auto block : m_map->m_blocks) {
	//	// Set uniform variables of the current object
	//	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &block->m_modelMatrix[0][0]);

	//	auto modelViewMatrix{glm::mat3(m_camera.m_viewMatrix * block->m_modelMatrix)};
	//	glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
	//	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

	//	glUniform1f(shininessLoc, block->m_shininess);
	//	glUniform4fv(KaLoc, 1, &block->m_Ka.x);
	//	glUniform4fv(KdLoc, 1, &block->m_Kd.x);
	//	glUniform4fv(KsLoc, 1, &block->m_Ks.x);

	//	block->m_model->render();
	//}
	// Set uniform variables of the current object
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_sea->m_modelMatrix[0][0]);

	auto modelViewMatrix{glm::mat3(m_camera.m_viewMatrix * m_sea->m_modelMatrix)};
	glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

	glUniform1f(shininessLoc, m_sea->m_shininess);
	glUniform1f(timeLoc, m_time);
	glUniform4fv(KaLoc, 1, &m_sea->m_Ka.x);
	glUniform4fv(KdLoc, 1, &m_sea->m_Kd.x);
	glUniform4fv(KsLoc, 1, &m_sea->m_Ks.x);

	m_sea->m_model->render();

	glUseProgram(0);
}

void OpenGLWindow::paintUI() {
	abcg::OpenGLWindow::paintUI();
	glFrontFace(GL_CCW);
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
	m_time += deltaTime;

	// Update LookAt camera
	m_camera.dolly(m_dollySpeed * deltaTime);
	m_camera.truck(m_truckSpeed * deltaTime);
	m_camera.pan(m_panSpeed * deltaTime);
}
