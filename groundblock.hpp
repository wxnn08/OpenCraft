#ifndef GROUND_BLOCK_HPP_
#define GROUND_BLOCK_HPP_

#include "model.hpp"
#include "textureshader.hpp"
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>

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

		float m_virtualRadius{0.6f};

	public:
		GroundBlock(){}
		GroundBlock(int id, glm::vec3 position) {
			m_id = id;
			m_position = position;
			m_modelMatrix = glm::translate(m_modelMatrix, position);
			m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.87f, 0.87f, 0.87f));
		}

		int m_id{};
		glm::vec3 m_position;
		void loadModel(const std::string &assetsPath, const GLuint &program);
		void render();
		bool rayIntersect(glm::vec3, glm::vec3);
		std::pair<glm::vec3, glm::vec3> intersectionPoints(glm::vec3, glm::vec3);
};

#endif
