#ifndef STONE_BLOCK_HPP_
#define STONE_BLOCK_HPP_

#include "../Block.hpp"
#include "../../render/TextureRender.hpp"

class StoneBlock : public Block {
	public:
		StoneBlock(int id, glm::vec3 p) : Block(id, p){}
		void loadModel(const std::string&);
		void render();
};

#endif
