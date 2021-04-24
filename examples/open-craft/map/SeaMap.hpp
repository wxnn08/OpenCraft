#ifndef SEAMAP_HPP_
#define SEAMAP_HPP_

#include "../block/Block.hpp"
#include "../block/grassBlock/GrassBlock.hpp"
#include "../block/stoneBlock/StoneBlock.hpp"
#include "../block/glassBlock/GlassBlock.hpp"
#include "../block/woodBlock/WoodBlock.hpp"
#include "../sea/Sea.hpp"
#include "abcg.hpp"
#include <vector>

class OpenGLWindow;

class SeaMap {
	private:
		friend OpenGLWindow;
		int m_currId{0};
		std::string m_assetsPath;
		std::vector<Block*> m_oppaqueBlocks;
		std::vector<Block*> m_transparentBlocks;
		Sea* m_sea;

		void setupBlock(Block*, bool);
		void createGrassBlock(glm::vec3);
		void createStoneBlock(glm::vec3);
		void createWoodBlock(glm::vec3);
		void createGlassBlock(glm::vec3);
	
	public:
		SeaMap(std::string assetsPath){ m_assetsPath = assetsPath; }

		Block* m_clickedBlock = nullptr;
		glm::vec3 m_closestPointIntersection{0.0f};

		void initializeGL();
		void createBlock(int, glm::vec3);
		void removeBlock(Block*);
		void render(float);

		void rayBlocksIntersection(const glm::vec3&, const glm::vec3&);
		void assignIntersectionInVec(const glm::vec3&, const glm::vec3&, float&, const std::vector<Block*>&);
};

#endif
