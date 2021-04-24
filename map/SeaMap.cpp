#include "SeaMap.hpp"
#include <fstream>
#include <glm/vec3.hpp>
#include <fmt/core.h>

void SeaMap::initializeGL() {

	m_sea = new Sea( glm::vec3{0.0f, -0.2f, 0.0f}, glm::vec3{200.0f, 1.0f, 200.0f});
	m_sea->loadModel(m_assetsPath);

	int height = 10;
	int width = 10;
	for(int row = 0; row < height; row++) {
		for(int col = 0; col < width; col++) {
			float xPos = (float)(-width/2) + col;
			float zPos = (float)(-height/2) + row;
			createBlock(glm::vec3{xPos, 0.0f, zPos});
		}
	}

	//std::string line;
	//std::ifstream file(m_assetsPath + "MapDescription.txt");

	//if(file) {
	//	getline(file, line);
	//	int height{std::stoi(line)};
	//		getline(file, line);
	//	int width{std::stoi(line)};

	//	for(int row = 0; row < height; row++) {
	//		getline(file, line);
	//		for(int col = 0; col < width; col++) {
	//			float xPos = (float)(-width/2) + col;
	//			float zPos = (float)(-height/2) + row;
	//			if(line[col] == '1')
	//				createBlock(glm::vec3{xPos, 0.0f, zPos});
	//		}
	//	}
	//}

	//file.close();
}

void SeaMap::createBlock(glm::vec3 position) {
	auto* block = new StoneBlock(m_currId, position);
	block->loadModel(m_assetsPath);
	m_currId++;
	m_blocks.push_back(block);
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
