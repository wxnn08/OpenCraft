#include "Block.hpp"
#include <fmt/core.h>
#include <math.h>

bool Block::rayIntersect(glm::vec3 rayOrigin, glm::vec3 rayDirection) {
	float b = glm::dot(rayDirection, (rayOrigin - m_position));
	float c = glm::dot(rayOrigin - m_position, rayOrigin - m_position) - m_virtualRadius * m_virtualRadius;
	return b * b - c >= 0.0f;
}

std::pair<glm::vec3, glm::vec3> Block::intersectionPoints(glm::vec3 rayOrigin, glm::vec3 rayDirection) {

	glm::vec3 p1{0.0f}, p2{0.0f}; 
	
	float b = glm::dot(rayDirection, (rayOrigin - m_position));
	float c = glm::dot(rayOrigin - m_position, rayOrigin - m_position) - m_virtualRadius * m_virtualRadius;

	if(b * b - c >= 0.0f) {
		float sqrtDelta = sqrt(b*b-c);
		float t1 = (-b + sqrtDelta);
		float t2 = (-b - sqrtDelta);
		p1 = glm::vec3(rayOrigin + rayDirection * t1);
		p2 = glm::vec3(rayOrigin + rayDirection * t2);
	}

	return std::pair<glm::vec3, glm::vec3>{p1, p2};
}
