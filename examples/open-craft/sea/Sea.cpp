#include "Sea.hpp"
#include "abcg.hpp"
#include <fmt/core.h>

void Sea::loadModel(const std::string &assetsPath) {
	m_model = new Model();

	m_model->loadDiffuseTexture(assetsPath + "maps/sea_texture.png");
	m_model->loadNoiseTexture1(assetsPath + "maps/noise1.png");
	m_model->loadNoiseTexture2(assetsPath + "maps/noise2.png");
	m_model->loadFromFile(assetsPath + "plane.obj");
	m_model->setupVAO(FluidRender::m_program);

	// Use material properties from the loaded model
	m_Ka = m_model->getKa();
	m_Kd = m_model->getKd();
	m_Ks = m_model->getKs();
	m_shininess = m_model->getShininess();
}

void Sea::render(float dt = 0.0f) {
	m_time += dt;
	FluidRender::useProgram(m_modelMatrix, m_time, m_shininess, m_Ka, m_Kd, m_Ks);
	m_model->render();
}

