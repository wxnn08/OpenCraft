#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include "abcg.hpp"
#include "../model/Model.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>
#include <utility>

class Block {
	protected:
 		Model* m_model;

		glm::mat4 m_modelMatrix{1.0f};
		glm::vec4 m_Ka{1.0f};
		glm::vec4 m_Kd{1.0f};
		glm::vec4 m_Ks{1.0f};
		float m_shininess{};

		float m_virtualRadius{0.8f};

	public:
		Block(int id, glm::vec3 position) {
			m_id = id;
			m_position = position;
			m_modelMatrix = glm::translate(m_modelMatrix, position);
			m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(0.87f, 0.87f, 0.87f));
		}

		int m_id{};
		glm::vec3 m_position;

		bool rayIntersect(glm::vec3, glm::vec3);
		std::pair<glm::vec3, glm::vec3> intersectionPoints(glm::vec3, glm::vec3);
		virtual void loadModel(const std::string&) = 0;
		virtual void render() = 0;
};

#endif
