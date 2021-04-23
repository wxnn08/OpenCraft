#include "map.hpp"
#include <fstream>
#include <glm/vec3.hpp>
#include <fmt/core.h>

void Map::initialize(const std::string &assetsPath) {
	//createBlock(glm::vec3{0.0f, 0.0f, 0.0f});
	//createBlock(glm::vec3{1.0f, 0.0f, 0.0f});

	std::string line;
	std::ifstream file(assetsPath + "MapDescription.txt");

	if(file) {
		getline(file, line);
		int height{std::stoi(line)};
			getline(file, line);
		int width{std::stoi(line)};

		for(int row = 0; row < height; row++) {
			getline(file, line);
			for(int col = 0; col < width; col++) {
				float xPos = (float)(-width/2) + col;
				float zPos = (float)(height/2) - row;
				if(line[col] == '1')
					createBlock(glm::vec3{xPos, 0.0f, zPos});
			}
		}
	}

	file.close();
}

void Map::createBlock(glm::vec3 position) {
	auto block = new GroundBlock(position);
	m_blocks.push_back(block);
}

void Map::loadModel(const std::string &assetsPath) {
	for(auto block : m_blocks)
		block->loadModel(assetsPath, TextureShader::m_program);
}
