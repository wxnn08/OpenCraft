#include "SeaMap.hpp"
#include <fstream>
#include <glm/vec3.hpp>
#include <fmt/core.h>
#include <utility>

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
		case 3:
			createGlassBlock(position);
			break;
	}
}

void SeaMap::setupBlock(Block* block, bool transparent) {
	block->loadModel(m_assetsPath);
	if(transparent)
		m_transparentBlocks.push_back(block);
	else
		m_oppaqueBlocks.push_back(block);

	m_currId++;
}

void SeaMap::createGrassBlock(glm::vec3 position) {
	auto block = new GrassBlock(m_currId, position);
	setupBlock(block, false);
}

void SeaMap::createStoneBlock(glm::vec3 position) {
	auto block = new StoneBlock(m_currId, position);
	setupBlock(block, false);
}

void SeaMap::createWoodBlock(glm::vec3 position) {
	auto block = new WoodBlock(m_currId, position);
	setupBlock(block, false);
}

void SeaMap::createGlassBlock(glm::vec3 position) {
	auto block = new GlassBlock(m_currId, position);
	setupBlock(block, true);
}


void SeaMap::removeBlock(Block* delBlock) {
	for(auto& block : m_oppaqueBlocks)
		if(block->m_id == delBlock->m_id) {
			std::swap(block, m_oppaqueBlocks.back());
			m_oppaqueBlocks.pop_back();
			break;
		}
	for(auto& block : m_transparentBlocks)
		if(block->m_id == delBlock->m_id) {
			std::swap(block, m_transparentBlocks.back());
			m_transparentBlocks.pop_back();
			break;
		}
}

void SeaMap::render(float dt) {
	m_sea->render(dt);
	for(auto block : m_oppaqueBlocks) 
		block->render();
	for(auto block : m_transparentBlocks) 
		block->render();
}

void SeaMap::assignIntersectionInVec(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, float& closestPointDistance, const std::vector<Block*>& blocks) {
	std::pair<glm::vec3, glm::vec3> points;

	for(auto block : blocks) {
		if(block->rayIntersect(rayOrigin, rayDirection)) {
			if(m_clickedBlock == nullptr) {
				m_clickedBlock = block;
				points = block->intersectionPoints(rayOrigin, rayDirection);
				float distanceP1 = glm::distance(rayOrigin, points.first);
				float distanceP2 = glm::distance(rayOrigin, points.second);
				m_closestPointIntersection = distanceP1 < distanceP2 ? points.first : points.second;
				closestPointDistance = std::min(distanceP1, distanceP2);
			}

			points = block->intersectionPoints(rayOrigin, rayDirection);
			float distanceP1 = glm::distance(rayOrigin, points.first);
			float distanceP2 = glm::distance(rayOrigin, points.second);

			if(closestPointDistance > distanceP1){
				m_clickedBlock = block;
				closestPointDistance = distanceP1;
				m_closestPointIntersection = points.first;
			}

			if(closestPointDistance > distanceP2){
				m_clickedBlock = block;
				closestPointDistance = distanceP2;
				m_closestPointIntersection = points.second;
			}
		}
	}
}

void SeaMap::rayBlocksIntersection(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) {
	m_clickedBlock = nullptr;
	m_closestPointIntersection = glm::vec3{0.0f};
	float closestPointDistance{0.0f};

	assignIntersectionInVec(rayOrigin, rayDirection, closestPointDistance, m_oppaqueBlocks);
	assignIntersectionInVec(rayOrigin, rayDirection, closestPointDistance, m_transparentBlocks);
}
