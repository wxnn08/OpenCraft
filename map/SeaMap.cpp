#include "SeaMap.hpp"
#include <fstream>
#include <glm/vec3.hpp>
#include <fmt/core.h>

void SeaMap::initializeGL() {

	m_sea = new Sea( glm::vec3{0.0f, -0.2f, 0.0f}, glm::vec3{200.0f, 1.0f, 200.0f});
	m_sea->loadModel(m_assetsPath);

	int height = 3;
	int width = 3;
	for(int row = 0; row < height; row++) {
		for(int col = 0; col < width; col++) {
			float xPos = (float)(-width/2) + col;
			float zPos = (float)(-height/2) + row;
				createBlock(0, glm::vec3{xPos, 0.0f, zPos});
		}
	}
}

void SeaMap::createBlock(int type, glm::vec3 position) {
	switch(type) {
		case 0:
			createGrassBlock(position);
			break;
		case 1:
			createStoneBlock(position);
			break;
		case 2:
			createWoodBlock(position);
			break;
	}
}

void SeaMap::setupBlock(Block* block) {
	block->loadModel(m_assetsPath);
	m_blocks.push_back(block);
	m_currId++;
}

void SeaMap::createGrassBlock(glm::vec3 position) {
	auto block = new GrassBlock(m_currId, position);
	setupBlock(block);
}

void SeaMap::createStoneBlock(glm::vec3 position) {
	auto block = new StoneBlock(m_currId, position);
	setupBlock(block);
}

void SeaMap::createWoodBlock(glm::vec3 position) {
	auto block = new WoodBlock(m_currId, position);
	setupBlock(block);
}

void SeaMap::removeBlock(Block* delBlock) {
	int index;
	for(index = 0; index < (int)m_blocks.size(); index++) 
		if(m_blocks[index]->m_id == delBlock->m_id) break;

	std::swap(m_blocks[index], m_blocks.back());
	m_blocks.pop_back();
}

void SeaMap::render(float dt) {
	for(auto block : m_blocks) 
		block->render();
	m_sea->render(dt);
}
