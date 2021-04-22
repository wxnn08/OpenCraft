#ifndef SEA_HPP_
#define SEA_HPP_

#include "model.hpp"
#include "watershader.hpp"
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
			m_modelMatrix = glm::mat4{
				{scale.x, 0.0f, 0.0f, 0.0f},
				{0.0f, scale.y, 0.0f, 0.0f},
				{0.0f, 0.0f, scale.z, 0.0f},
				{position.x, position.y, position.z, 1.0f},
			};
		}

		void loadModel(const std::string &assetsPath);
		void render(float);
};

#endif
