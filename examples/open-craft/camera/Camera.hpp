#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
	private:
		float m_fov{glm::radians(60.0f)};
		float m_near{1.0f};
		float m_far{300.0f};

	public:
		void computeViewMatrix();
		void computeProjectionMatrix(int, int);
		glm::vec3 createRay(float, float, float, float);

		void dolly(float dt);
		void truck(float dt);
		void pan(float dt);
		void vertical(float dt);

		float m_dollySpeed{0.0f};
		float m_truckSpeed{0.0f};
		float m_panSpeed{0.0f};
		float m_verticalSpeed{0.0f};

		glm::vec3 m_eye{glm::vec3(-8.0f, 9.54f, 8.0f)};  // Camera position
		//glm::vec3 m_eye{glm::vec3(-2.0f, 2.0f, 2.0f)};  // Camera position
		glm::vec3 m_at{glm::vec3(0.0f, 0.0f, 0.0f)};   // Look-at point
		glm::vec3 m_up{glm::vec3(0.0f, 1.0f, 0.0f)};   // "up" direction

		// Matrix to change from world space to camera soace
		glm::mat4 m_viewMatrix;

		// Matrix to change from camera space to clip space
		glm::mat4 m_projMatrix;
};

#endif
