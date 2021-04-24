#include "UI.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"

void UI::initializeGL(std::string assetsPath) {
	loadTextureFromFile("./build/bin/3d-world/assets/cubetypes/grass.png", &m_grassTexture);
	loadTextureFromFile("./build/bin/3d-world/assets/cubetypes/stone.png", &m_stoneTexture);
	loadTextureFromFile("./build/bin/3d-world/assets/cubetypes/wood.png", &m_woodTexture);
	loadTextureFromFile("./build/bin/3d-world/assets/cubetypes/glass.png", &m_glassTexture);
}

void UI::paintUI(int width, int height) {

	auto size{ImVec2(90, 400)};
    //auto position{ImVec2((width - size.x) / 2.0f,
    //                     (height - size.y) / 2.0f)};

    auto position{ImVec2(width - size.x,
						(height - size.y) / 2.0f)};


	ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
	
	ImGui::Begin("OpenGL Texture Text", nullptr, m_cubeSelectFlags);
	if(ImGui::ImageButton((void*)(intptr_t)m_grassTexture, ImVec2(64.0f, 64.0f))) 
		m_cubeSelected = 0;
	if(ImGui::ImageButton((void*)(intptr_t)m_stoneTexture, ImVec2(64.0f, 64.0f))) 
		m_cubeSelected = 1;
	if(ImGui::ImageButton((void*)(intptr_t)m_woodTexture, ImVec2(64.0f, 64.0f))) 
		m_cubeSelected = 2;
	if(ImGui::ImageButton((void*)(intptr_t)m_glassTexture, ImVec2(64.0f, 64.0f))) 
		m_cubeSelected = 3;
	ImGui::End();
}

bool UI::loadTextureFromFile(const char* filename, GLuint* out_texture) {
	// Load from file
	int image_width = 32.0f;
	int image_height = 32.0f;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;

	return true;
}
