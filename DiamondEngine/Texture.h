#pragma once
#include "stb_image.h"
#include "opengl.h"


class Texture {
private:
	unsigned int m_id;
	int m_width, m_height, m_channels;
public:
	Texture();
	~Texture();
	void Load(std::string filePath);
	void Bind();
	void UnBind();
};