#ifndef GROUND_BLOCK_HPP_
#define GROUND_BLOCK_HPP_

#include "model.hpp"
#include "textureshader.hpp"
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OpenGLWindow;

class GroundBlock {
	protected:
		friend OpenGLWindow;
 		Model* m_model;

		glm::mat4 m_modelMatrix{1.0f};
		glm::vec4 m_Ka;
		glm::vec4 m_Kd;
		glm::vec4 m_Ks;
		float m_shininess{};

	public:
		GroundBlock(){}
		GroundBlock(glm::vec3 position) {
			m_modelMatrix = glm::mat4{
				{1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f},
				{position.x, position.y, position.z, 1.0f},
			};
		}

		void loadModel(const std::string &assetsPath, const GLuint &program);
		void render();
};

#endif
