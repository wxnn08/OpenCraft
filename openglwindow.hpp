#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <string_view>

#include "abcg.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "eventhandler.hpp"
#include "map.hpp"
#include "sea.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
	protected:
		void handleEvent(SDL_Event& ev) override;
		void initializeGL() override;
		void paintGL() override;
		void paintUI() override;
		void resizeGL(int width, int height) override;
		void terminateGL() override;

	private:
		float m_time{0};
		int m_viewportWidth{};
		int m_viewportHeight{};


		float m_zoom{};

		Camera m_camera;
		float m_dollySpeed{0.0f};
		float m_truckSpeed{0.0f};
		float m_panSpeed{0.0f};

		glm::mat4 m_viewMatrix{1.0f};
		glm::mat4 m_projMatrix{1.0f};

		// Map
		Map* m_map;

		Sea* m_sea;

		// Event Handler
		EventHandler m_eventHandler;

		// Shader
		GLuint m_program;

		// Light and material properties
		glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
		glm::vec4 m_Ia{1.0f};
		glm::vec4 m_Id{1.0f};
		glm::vec4 m_Is{1.0f};
		glm::vec4 m_Ka;
		glm::vec4 m_Kd;
		glm::vec4 m_Ks;
		float m_shininess{};

		void loadModel(std::string_view path);
		void update();
};

#endif
