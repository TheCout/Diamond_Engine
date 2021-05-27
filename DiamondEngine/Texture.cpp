#include "Texture.h"



Texture::Texture() :
	m_id(0), m_width(0),
	m_height(0), m_channels(0)
{
}


Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}


void Texture::Load(std::string filePath) {
	unsigned char* imgData;

	stbi_set_flip_vertically_on_load(true);
	imgData = stbi_load(filePath.c_str(), &m_width, &m_height, &m_channels, 4);
	if (imgData) {
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(imgData);
	}
	else {
		//ERROR
	}
}


void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, m_id);
}


void Texture::UnBind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}