#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera {
	public:
		void computeViewMatrix();
		void computeProjectionMatrix(int width, int height);

		void dolly(float speed);
		void truck(float speed);
		void pan(float speed);

		float m_dollySpeed{0.0f};
		float m_truckSpeed{0.0f};
		float m_panSpeed{0.0f};

		glm::vec3 m_eye{glm::vec3(-6.03f, 7.54f, -6.03f)};  // Camera position
		//glm::vec3 m_eye{glm::vec3(0.0f, 5.0f, 0.000000001f)};  // Camera position
		glm::vec3 m_at{glm::vec3(0.0f, 0.0f, 0.0f)};   // Look-at point
		glm::vec3 m_up{glm::vec3(0.0f, 1.0f, 0.0f)};   // "up" direction

		// Matrix to change from world space to camera soace
		glm::mat4 m_viewMatrix;

		// Matrix to change from camera space to clip space
		glm::mat4 m_projMatrix;
};

#endif
