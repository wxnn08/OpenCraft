#ifndef LIGHT_HPP_
#define LIGHT_HPP_

class Light {
	public:
		glm::vec4 m_lightDir{0.5f, -1.0f, 0.1f, 0.0f};
		glm::vec4 m_Ia{1.0f};
		glm::vec4 m_Id{1.0f};
		glm::vec4 m_Is{1.0f};
};

#endif
