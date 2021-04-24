#ifndef UI_HPP_ 
#define UI_HPP_ 

#include "abcg.hpp"

class UI {
	private:
		GLuint my_image_texture = 0;

	public:
		void initializeGL(std::string);
		void paintUI();
		bool loadTextureFromFile(const char* filename, GLuint* out_texture);
};

#endif
