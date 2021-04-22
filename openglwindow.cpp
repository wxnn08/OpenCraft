#include "openglwindow.hpp"
#include <imgui.h>
#include <cppitertools/itertools.hpp>
#include <glm/vec3.hpp>
#include <fmt/core.h>


void OpenGLWindow::handleEvent(SDL_Event& ev) {
	m_eventHandler.handleEvent(ev, m_camera);
}

void OpenGLWindow::initializeGL() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_camera = new Camera();
	m_light = new Light();

	auto path{getAssetsPath() + "shaders/"};
	GLuint program{};

	program = createProgramFromFile(path + "WaterShader"+ ".vert", path + "WaterShader" + ".frag");
	WaterShader::setup(program, m_camera, m_light);

	//m_map = new Map();
	//m_map->initialize(getAssetsPath());
	//m_map->loadModel(getAssetsPath(), m_program);

	m_sea = new Sea(
			glm::vec3{0.0f, -0.2f, 0.0f},
			glm::vec3{50.0f, 1.0f, 50.0f});
	m_sea->loadModel(getAssetsPath());
}

void OpenGLWindow::paintGL() {
	float deltaTime{static_cast<float>(getDeltaTime())};

	m_camera->dolly(m_camera->m_dollySpeed * deltaTime);
	m_camera->truck(m_camera->m_truckSpeed * deltaTime);
	m_camera->pan(m_camera->m_panSpeed * deltaTime);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_viewportWidth, m_viewportHeight);

	//for(auto block : m_map->m_blocks) {
	//	// Set uniform variables of the current object
	//	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &block->m_modelMatrix[0][0]);

	//	auto modelViewMatrix{glm::mat3(m_camera->m_viewMatrix * block->m_modelMatrix)};
	//	glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
	//	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

	//	glUniform1f(shininessLoc, block->m_shininess);
	//	glUniform4fv(KaLoc, 1, &block->m_Ka.x);
	//	glUniform4fv(KdLoc, 1, &block->m_Kd.x);
	//	glUniform4fv(KsLoc, 1, &block->m_Ks.x);

	//	block->m_model->render();
	//}
	
	m_sea->render(deltaTime);

	glUseProgram(0);
}

void OpenGLWindow::paintUI() {
	abcg::OpenGLWindow::paintUI();
	glFrontFace(GL_CCW);
	m_camera->computeProjectionMatrix(m_viewportWidth, m_viewportHeight);
}

void OpenGLWindow::resizeGL(int width, int height) {
	m_viewportWidth = width;
	m_viewportHeight = height;
}

void OpenGLWindow::terminateGL() {
	glDeleteProgram(m_program);
}
