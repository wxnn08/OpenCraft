#include "Camera.hpp"

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

void Camera::dolly(float dt) {
	// Compute forward vector (view direction)
	glm::vec3 forward = glm::normalize(m_at - m_eye);

	m_eye += forward * m_dollySpeed * dt;
	m_at += forward * m_dollySpeed * dt;

	computeViewMatrix();
}

void Camera::truck(float dt) {
	// Compute forward vector (view direction)
	glm::vec3 forward = glm::normalize(m_at - m_eye);
	// Compute vector to the left
	glm::vec3 left = glm::cross(m_up, forward);

	m_at -= left * m_truckSpeed * dt;
	m_eye -= left * m_truckSpeed * dt;

	computeViewMatrix();
}

void Camera::pan(float dt) {
	glm::mat4 transform{glm::mat4(1.0f)};

	// Rotate camera around its local y axis
	transform = glm::translate(transform, m_eye);
	transform = glm::rotate(transform, -m_panSpeed * dt, m_up);
	transform = glm::translate(transform, -m_eye);

	m_at = transform * glm::vec4(m_at, 1.0f);

	computeViewMatrix();
}

void Camera::vertical(float dt) {
	m_eye.y += m_verticalSpeed * dt;
	m_at.y += m_verticalSpeed * dt;
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
