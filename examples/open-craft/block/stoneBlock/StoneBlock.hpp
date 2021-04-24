#ifndef STONE_BLOCK_HPP_
#define STONE_BLOCK_HPP_

#include "../Block.hpp"
#include "../../render/TextureRender.hpp"

class StoneBlock : public Block {
	private:
		glm::vec4 m_Ka = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
		glm::vec4 m_Kd = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		glm::vec4 m_Ks = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	public:
		StoneBlock(int id, glm::vec3 p) : Block(id, p){}
		void loadModel(const std::string&);
		void render();
};

#endif
