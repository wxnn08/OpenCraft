#include "groundblock.hpp"
#include "abcg.hpp"
#include <fmt/core.h>
#include <math.h>

void GroundBlock::loadModel(const std::string &assetsPath, const GLuint &program) {
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

void GroundBlock::render() {
	TextureShader::useProgram(m_modelMatrix, m_shininess, m_Ka, m_Kd, m_Ks);
	m_model->render();
}

bool GroundBlock::rayIntersect(glm::vec3 rayOrigin, glm::vec3 rayDirection) {
	float b = glm::dot(rayDirection, (rayOrigin - m_position));
	float c = glm::dot(rayOrigin - m_position, rayOrigin - m_position) - m_virtualRadius * m_virtualRadius;
	return b * b - c >= 0.0f;
}

std::pair<glm::vec3, glm::vec3> GroundBlock::intersectionPoints(glm::vec3 rayOrigin, glm::vec3 rayDirection) {

	glm::vec3 p1{0.0f}, p2{0.0f}; 
	
	float b = glm::dot(rayDirection, (rayOrigin - m_position));
	float c = glm::dot(rayOrigin - m_position, rayOrigin - m_position) - m_virtualRadius * m_virtualRadius;

	if(b * b - c >= 0.0f) {
		float sqrtDelta = sqrt(b*b-c);
		float t1 = (-b + sqrtDelta);
		float t2 = (-b - sqrtDelta);
		p1 = glm::vec3(rayOrigin + rayDirection * t1);
		p2 = glm::vec3(rayOrigin + rayDirection * t2);
	}

	return std::pair<glm::vec3, glm::vec3>{p1, p2};
}
