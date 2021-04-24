#ifndef LIGHT_HPP_
#define LIGHT_HPP_

class Light {
	public:
		glm::vec4 m_lightDir{1.0f, -1.0f, 1.0f, 0.0f};
		glm::vec4 m_Ia{1.0f};
		glm::vec4 m_Id{1.0f};
		glm::vec4 m_Is{1.0f};
};

#endif
