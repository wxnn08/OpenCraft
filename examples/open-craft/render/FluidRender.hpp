#ifndef WATER_SHADER_HPP_
#define WATER_SHADER_HPP_

#include "abcg.hpp"
#include "../camera/Camera.hpp"
#include "../light/Light.hpp"

#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

class FluidRender {
	public:
		static GLint m_program;
		static Camera* m_camera;
		static Light* m_light;

		static void setup(GLint, Camera*, Light*);
		static void useProgram(const glm::mat4&, float, float, const glm::vec4&, const glm::vec4&, const glm::vec4&);
};

#endif
