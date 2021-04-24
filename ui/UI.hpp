#ifndef UI_HPP_ 
#define UI_HPP_ 

#include "abcg.hpp"
#include <imgui.h>

class UI {
	private:
		GLuint grass_texture = 0;
		GLuint stone_texture = 0;

		ImGuiWindowFlags m_cubeSelectFlags{ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize};

	public:
		int m_cubeSelected{0};
		void initializeGL(std::string);
		void paintUI(int, int);
		bool loadTextureFromFile(const char* filename, GLuint* out_texture);
};

#endif
