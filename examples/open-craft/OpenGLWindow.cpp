#include "OpenGLWindow.hpp"
#include <imgui.h>
#include <cppitertools/itertools.hpp>
#include <glm/vec3.hpp>
#include <fmt/core.h>

void OpenGLWindow::handleEvent(SDL_Event& ev) {
	m_eventHandler.handleEvent(ev, m_camera);

	if(ev.type == SDL_MOUSEBUTTONDOWN){

		glm::vec3 rayDirection = m_camera->createRay(ev.motion.x, ev.motion.y, m_viewportWidth, m_viewportHeight);
		glm::vec3 rayOrigin = m_camera->m_eye;

		m_map->rayBlocksIntersection(rayOrigin, rayDirection);

		if(m_map->m_clickedBlock && ev.button.button == SDL_BUTTON_RIGHT) {
			m_map->removeBlock(m_map->m_clickedBlock);
		}
		if(m_map->m_clickedBlock && ev.button.button == SDL_BUTTON_LEFT) {
			glm::vec3 pos = glm::round(m_map->m_clickedBlock->m_position + (m_map->m_closestPointIntersection - m_map->m_clickedBlock->m_position) * 1.1f);
			m_map->createBlock(m_ui->m_cubeSelected, pos);
		}
	}
}

void OpenGLWindow::initializeGL() {
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	m_ui = new UI();
	m_ui->initializeGL(getAssetsPath());

	m_camera = new Camera();
	m_light = new Light();

	auto path{getAssetsPath() + "shaders/"};
	FluidRender::setup(createProgramFromFile(path + "WaterShader.vert", path + "WaterShader.frag"), m_camera, m_light);
	TextureRender::setup(createProgramFromFile(path + "TextureShader.vert", path + "TextureShader.frag"), m_camera, m_light);

	m_map = new SeaMap(getAssetsPath());
	m_map->initializeGL();
}

void OpenGLWindow::paintGL() {
	float deltaTime{static_cast<float>(getDeltaTime())};

	m_camera->dolly(deltaTime);
	m_camera->truck(deltaTime);
	m_camera->pan(deltaTime);
	m_camera->vertical(deltaTime);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_viewportWidth, m_viewportHeight);

	m_map->render(deltaTime);

	glUseProgram(0);
}

void OpenGLWindow::paintUI() {
	abcg::OpenGLWindow::paintUI();
	m_ui->paintUI(m_viewportWidth, m_viewportHeight);
}

void OpenGLWindow::resizeGL(int width, int height) {
	m_viewportWidth = width;
	m_viewportHeight = height;
	m_camera->computeProjectionMatrix(m_viewportWidth, m_viewportHeight);
}

void OpenGLWindow::terminateGL() {
	glDeleteProgram(m_program);
}

