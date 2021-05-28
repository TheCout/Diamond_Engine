#ifndef _texture_
#define _texture_
#pragma once
#include "stb_image.h"
#include "GLpane.h"


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
#endif