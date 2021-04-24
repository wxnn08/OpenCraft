#include "OpenGLWindow.hpp"
#include <imgui.h>
#include <cppitertools/itertools.hpp>
#include <glm/vec3.hpp>
#include <fmt/core.h>
#include <utility>

void OpenGLWindow::handleEvent(SDL_Event& ev) {
	m_eventHandler.handleEvent(ev, m_camera);

	if(ev.type == SDL_MOUSEBUTTONDOWN){

		glm::vec3 rayDirection = m_camera->createRay(ev.motion.x, ev.motion.y, m_viewportWidth, m_viewportHeight);
		glm::vec3 rayOrigin = m_camera->m_eye;

		Block* clickedBlock = nullptr;
		glm::vec3 closestPointIntersection{0.0f};
		float closestPointDistance{0.0f};

		std::pair<glm::vec3, glm::vec3> points;
		
		for(auto block : m_map->m_blocks) {
			if(block->rayIntersect(rayOrigin, rayDirection)) {
				if(clickedBlock == nullptr) {
					clickedBlock = block;
					points = block->intersectionPoints(rayOrigin, rayDirection);
					float distanceP1 = glm::distance(m_camera->m_eye, points.first);
					float distanceP2 = glm::distance(m_camera->m_eye, points.second);
					closestPointIntersection = distanceP1 < distanceP2 ? points.first : points.second;
					closestPointDistance = std::min(distanceP1, distanceP2);
				}

				points = block->intersectionPoints(rayOrigin, rayDirection);
				float distanceP1 = glm::distance(m_camera->m_eye, points.first);
				float distanceP2 = glm::distance(m_camera->m_eye, points.second);

				if(closestPointDistance > distanceP1){
					clickedBlock = block;
					closestPointDistance = distanceP1;
					closestPointIntersection = points.first;
				}

				if(closestPointDistance > distanceP2){
					clickedBlock = block;
					closestPointDistance = distanceP2;
					closestPointIntersection = points.second;
				}
			}
		}

		if(clickedBlock && ev.button.button == SDL_BUTTON_RIGHT) {
			m_map->removeBlock(clickedBlock);
		}
		if(clickedBlock && ev.button.button == SDL_BUTTON_LEFT) {
			glm::vec3 pos = glm::round(clickedBlock->m_position + (closestPointIntersection - clickedBlock->m_position) * 1.1f);
			m_map->createBlock(m_ui->m_cubeSelected, pos);
		}
	}
}

void OpenGLWindow::initializeGL() {
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CCW);

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

	m_camera->dolly(m_camera->m_dollySpeed * deltaTime);
	m_camera->truck(m_camera->m_truckSpeed * deltaTime);
	m_camera->pan(m_camera->m_panSpeed * deltaTime);

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

