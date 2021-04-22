#ifndef GROUND_BLOCK_HPP_
#define GROUND_BLOCK_HPP_

#include "model.hpp"
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OpenGLWindow;

class GroundBlock {
	protected:
		friend OpenGLWindow;
 		Model* m_model;

		glm::vec4 m_position;

		glm::mat4 m_modelMatrix{1.0f};
		glm::vec4 m_Ka;
		glm::vec4 m_Kd;
		glm::vec4 m_Ks;
		float m_shininess{};


	public:
		GroundBlock(){}
		GroundBlock(glm::vec3 position) {
			m_modelMatrix[3][0] = position.x;
			m_modelMatrix[3][1] = position.y;
			m_modelMatrix[3][2] = position.z;
		}

		void loadModel(const std::string &assetsPath, const GLuint &program);
};

#endif
