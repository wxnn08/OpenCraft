#include "FluidRender.hpp"

GLint FluidRender::m_program;
Light* FluidRender::m_light;
Camera* FluidRender::m_camera;

void FluidRender::setup(GLint program, Camera* camera, Light* light) {
	m_program = program;
	m_camera = camera;
	m_light = light;
}

void FluidRender::useProgram(const glm::mat4& modelMatrix, float time, float shininess, const glm::vec4& Ka, const glm::vec4& Kd, const glm::vec4& Ks) {
	// Use currently selected program
	glUseProgram(m_program);

	// Get location of uniform variables
	GLint viewMatrixLoc{glGetUniformLocation(m_program, "viewMatrix")};
	GLint projMatrixLoc{glGetUniformLocation(m_program, "projMatrix")};
	GLint modelMatrixLoc{glGetUniformLocation(m_program, "modelMatrix")};
	GLint normalMatrixLoc{glGetUniformLocation(m_program, "normalMatrix")};
	GLint lightDirLoc{glGetUniformLocation(m_program, "lightDirWorldSpace")};
	GLint shininessLoc{glGetUniformLocation(m_program, "shininess")};
	GLint IaLoc{glGetUniformLocation(m_program, "Ia")};
	GLint IdLoc{glGetUniformLocation(m_program, "Id")};
	GLint IsLoc{glGetUniformLocation(m_program, "Is")};
	GLint KaLoc{glGetUniformLocation(m_program, "Ka")};
	GLint KdLoc{glGetUniformLocation(m_program, "Kd")};
	GLint KsLoc{glGetUniformLocation(m_program, "Ks")};
	GLint diffuseTexLoc{glGetUniformLocation(m_program, "diffuseTex")};
	GLint noiseTexLoc1{glGetUniformLocation(m_program, "noiseTex1")};
	GLint noiseTexLoc2{glGetUniformLocation(m_program, "noiseTex2")};
	GLint timeLoc{glGetUniformLocation(m_program, "time")};

	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_camera->m_viewMatrix[0][0]);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_camera->m_projMatrix[0][0]);
	glUniform1i(diffuseTexLoc, 0);
	glUniform1i(noiseTexLoc1, 1);
	glUniform1i(noiseTexLoc2, 2);

	auto lightDirRotated{m_light->m_lightDir};
	glUniform4fv(lightDirLoc, 1, &lightDirRotated.x);
	glUniform4fv(IaLoc, 1, &m_light->m_Ia.x);
	glUniform4fv(IdLoc, 1, &m_light->m_Id.x);
	glUniform4fv(IsLoc, 1, &m_light->m_Is.x);

	// Set uniform variables of the current object
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &modelMatrix[0][0]);

	auto modelViewMatrix{glm::mat3(m_camera->m_viewMatrix * modelMatrix)};
	glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

	glUniform1f(shininessLoc, shininess);
	glUniform1f(timeLoc, time);
	glUniform4fv(KaLoc, 1, &Ka.x);
	glUniform4fv(KdLoc, 1, &Kd.x);
	glUniform4fv(KsLoc, 1, &Ks.x);


}
