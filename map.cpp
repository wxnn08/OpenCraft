#include "map.hpp"

#include <glm/vec3.hpp>

void Map::initialize() {
	createBlock(glm::vec3{0.0f, 0.0f, 0.0f});
	createBlock(glm::vec3{1.0f, 0.0f, 0.0f});
}

void Map::createBlock(glm::vec3 position) {
	auto block = new GroundBlock(position);
	m_blocks.push_back(block);
}

void Map::loadModel(const std::string &assetsPath, const GLuint &program) {
	for(auto block : m_blocks)
		block->loadModel(assetsPath, program);
}
