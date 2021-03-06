#ifndef SEA_HPP_
#define SEA_HPP_

#include "../model/Model.hpp"
#include "../render/FluidRender.hpp"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class OpenGLWindow;

class Sea {
	protected:
		friend OpenGLWindow;
 		Model* m_model;

		glm::vec4 m_position;

		glm::mat4 m_modelMatrix{1.0f};
		glm::vec4 m_Ka;
		glm::vec4 m_Kd;
		glm::vec4 m_Ks;
		float m_shininess{};
		float m_time{0};

	public:
		Sea(){}
		Sea(glm::vec3 position, glm::vec3 scale) {
			m_modelMatrix = glm::translate(m_modelMatrix, position);
			m_modelMatrix = glm::scale(m_modelMatrix, scale);
		}

		void loadModel(const std::string &assetsPath);
		void render(float);
};

#endif
