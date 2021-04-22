#include "sea.hpp"
#include "abcg.hpp"
#include <fmt/core.h>

void Sea::loadModel(const std::string &assetsPath, const GLuint &program) {
	m_model = new Model();

	m_model->loadDiffuseTexture(assetsPath + "maps/sea_texture.png");
	m_model->loadNoiseTexture(assetsPath + "maps/noise1.png");
	m_model->loadFromFile(assetsPath + "plane.obj");
	m_model->setupVAO(program);

	// Use material properties from the loaded model
	m_Ka = m_model->getKa();
	m_Kd = m_model->getKd();
	m_Ks = m_model->getKs();
	m_shininess = m_model->getShininess();
}


