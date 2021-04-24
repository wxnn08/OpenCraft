#ifndef SEAMAP_HPP_
#define SEAMAP_HPP_

#include "../block/grassBlock/GrassBlock.hpp"
#include "abcg.hpp"
#include <vector>

class OpenGLWindow;

class Map {
	private:
		int m_currId{0};
		friend OpenGLWindow;
		std::vector<GrassBlock*> m_blocks;
		std::string m_assetsPath;
	
	public:
		Map(std::string assetsPath){
			m_assetsPath = assetsPath;
		}
		void initialize();
		void createBlock(glm::vec3 position);
		void removeBlock(GrassBlock*);
};

#endif
