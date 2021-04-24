#include "GrassBlock.hpp"

void GrassBlock::loadModel(const std::string &assetsPath) {
	m_model = new Model();

	m_model->loadDiffuseTexture(assetsPath + "maps/ground_texture.png");
	m_model->loadFromFile(assetsPath + "grass_cube.obj");
	m_model->setupVAO(TextureRender::m_program);

	// Use material properties from the loaded model
	m_shininess = m_model->getShininess();
}

void GrassBlock::render() {
	TextureRender::useProgram(m_modelMatrix, m_shininess, m_Ka, m_Kd, m_Ks);
	m_model->render();
}
