#ifndef SEAMAP_HPP_
#define SEAMAP_HPP_

#include "../block/Block.hpp"
#include "../block/grassBlock/GrassBlock.hpp"
#include "../block/stoneBlock/StoneBlock.hpp"
#include "../sea/Sea.hpp"
#include "abcg.hpp"
#include <vector>

class OpenGLWindow;

class SeaMap {
	private:
		friend OpenGLWindow;
		int m_currId{0};
		std::string m_assetsPath;
		std::vector<Block*> m_blocks;
		Sea* m_sea;
	
	public:
		SeaMap(std::string assetsPath){
			m_assetsPath = assetsPath;
		}
		void initializeGL();
		void createBlock(glm::vec3 position);
		void removeBlock(Block*);
		void render(float);
};

#endif
