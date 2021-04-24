#ifndef SEAMAP_HPP_
#define SEAMAP_HPP_

#include "../block/Block.hpp"
#include "../block/grassBlock/GrassBlock.hpp"
#include "abcg.hpp"
#include <vector>

class OpenGLWindow;

class SeaMap {
	private:
		int m_currId{0};
		friend OpenGLWindow;
		std::vector<Block*> m_blocks;
		std::string m_assetsPath;
	
	public:
		SeaMap(std::string assetsPath){
			m_assetsPath = assetsPath;
		}
		void initialize();
		void createBlock(glm::vec3 position);
		void removeBlock(Block*);
};

#endif
