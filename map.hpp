#ifndef MAP_HPP_
#define MAP_HPP_

#include "groundblock.hpp"
#include "abcg.hpp"
#include <vector>

class OpenGLWindow;

class Map {
	private:
		friend OpenGLWindow;
		std::vector<GroundBlock*> m_blocks;

	
	public:
		void initialize(const std::string &assetsPath);
		void loadModel(const std::string &assetsPath, const GLuint &program);
		void createBlock(glm::vec3 position);
};

#endif
