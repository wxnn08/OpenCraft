#include "GrassBlock.hpp"

void GrassBlock::loadModel(const std::string &assetsPath, const GLuint &program) {
	m_model = new Model();

	m_model->loadDiffuseTexture(assetsPath + "maps/ground_texture.png");
	m_model->loadFromFile(assetsPath + "cube.obj");
	m_model->setupVAO(program);

	// Use material properties from the loaded model
	m_Ka = m_model->getKa();
	m_Kd = m_model->getKd();
	m_Ks = m_model->getKs();
	m_shininess = m_model->getShininess();
}

void GrassBlock::render() {
	TextureRender::useProgram(m_modelMatrix, m_shininess, m_Ka, m_Kd, m_Ks);
	m_model->render();
}
