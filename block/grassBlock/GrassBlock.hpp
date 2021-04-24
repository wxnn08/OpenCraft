#ifndef GRASS_BLOCK_HPP_
#define GRASS_BLOCK_HPP_

#include "../Block.hpp"
#include "../../render/TextureRender.hpp"

class GrassBlock : public Block {
	public:
		GrassBlock(int id, glm::vec3 p) : Block(id, p){}
		void loadModel(const std::string&, const GLuint &);
		void render();
};

#endif
