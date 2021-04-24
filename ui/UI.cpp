#include "UI.hpp"
#include <imgui.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"

void UI::initializeGL(std::string assetsPath) {
	loadTextureFromFile("./build/bin/3d-world/assets/maps/ground_texture.png", &my_image_texture);
	loadTextureFromFile("./build/bin/3d-world/assets/maps/ground_texture.png", &my_image_texture);
}

void UI::paintUI() {
	ImGui::Begin("OpenGL Texture Text");
	ImGui::ImageButton((void*)(intptr_t)my_image_texture, ImVec2(64.0f, 64.0f));
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
