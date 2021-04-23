#ifndef MAP_HPP_
#define MAP_HPP_

#include "groundblock.hpp"
#include "abcg.hpp"
#include <vector>

class OpenGLWindow;

class Map {
	private:
		int m_currId{0};
		friend OpenGLWindow;
		std::vector<GroundBlock*> m_blocks;
		std::string m_assetsPath;
	
	public:
		Map(std::string assetsPath){
			m_assetsPath = assetsPath;
		}
		void initialize();
		void createBlock(glm::vec3 position);
		void removeBlock(GroundBlock*);
};

#endif
