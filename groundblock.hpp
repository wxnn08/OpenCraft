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
			m_modelMatrix = glm::translate(m_modelMatrix, position);
			m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(1.0f, 0.87f, 1.0f));
		}

		void loadModel(const std::string &assetsPath, const GLuint &program);
		void render();
};

#endif
