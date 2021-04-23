#include "camera.hpp"

#include <fmt/core.h>

void Camera::computeProjectionMatrix(int width, int height) {
	m_projMatrix = glm::mat4(1.0f);
	auto aspect{static_cast<float>(width) / static_cast<float>(height)};
	m_projMatrix = glm::perspective(m_fov, aspect, m_near, m_far);
}

void Camera::computeViewMatrix() {
	m_viewMatrix = glm::lookAt(m_eye, m_at, m_up);
	//fmt::print("{0} , {1} , {2}\n", m_eye.x, m_eye.y, m_eye.z);
}

void Camera::dolly(float speed) {
	// Compute forward vector (view direction)
	glm::vec3 forward = glm::normalize(m_at - m_eye);

	// Move eye and center forward (speed > 0) or backward (speed < 0)
	m_eye += forward * speed;
	m_at += forward * speed;

	computeViewMatrix();
}

void Camera::truck(float speed) {
	// Compute forward vector (view direction)
	glm::vec3 forward = glm::normalize(m_at - m_eye);
	// Compute vector to the left
	glm::vec3 left = glm::cross(m_up, forward);

	// Move eye and center to the left (speed < 0) or to the right (speed > 0)
	m_at -= left * speed;
	m_eye -= left * speed;

	computeViewMatrix();
}

void Camera::pan(float speed) {
	glm::mat4 transform{glm::mat4(1.0f)};

	// Rotate camera around its local y axis
	transform = glm::translate(transform, m_eye);
	transform = glm::rotate(transform, -speed, m_up);
	transform = glm::translate(transform, -m_eye);

	m_at = transform * glm::vec4(m_at, 1.0f);

	computeViewMatrix();
}

glm::vec3 Camera::createRay(float mouseScreenX, float mouseScreenY, float viewPortWidth, float viewPortHeight) {
    float mouseX = 2.0f * mouseScreenX / viewPortWidth - 1.0f;
    float mouseY = 1.0f - 2.0f * mouseScreenY / viewPortHeight;
    glm::vec4 ray_clip = glm::vec4(mouseX, mouseY, -1.0f, 1.0f);
	glm::vec4 ray_eye = glm::inverse(m_projMatrix) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
	glm::vec4 ray_world = (glm::inverse(m_viewMatrix) * ray_eye);
	glm::vec3 dir = glm::normalize(glm::vec3(ray_world.x, ray_world.y, ray_world.z));
    return dir;
}
