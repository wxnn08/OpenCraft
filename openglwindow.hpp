#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <string_view>

#include "abcg.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "eventhandler.hpp"
#include "map.hpp"
#include "sea.hpp"
#include "light.hpp"
#include "watershader.hpp"

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

		glm::mat4 m_viewMatrix{1.0f};
		glm::mat4 m_projMatrix{1.0f};

		Camera* m_camera;
		Light* m_light;
		Map* m_map;
		Sea* m_sea;
		EventHandler m_eventHandler;

		// Shader
		GLuint m_program;

		void loadModel(std::string_view path);
};

#endif
