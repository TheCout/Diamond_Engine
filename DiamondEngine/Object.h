#pragma once
#include "glm/glm.hpp"
#include "Texture.h"
#include "cg.h"


struct Object {
	GLuint id;
	glm::vec3 pos;
	glm::vec3 size;
	Texture* tex;
	Object():id(0), pos(glm::vec3(0.0, 0.0, 0.0)), size(glm::vec3(0.0, 0.0, 0.0)), tex(nullptr){}
	Object(GLuint id_, glm::vec3 pos_, glm::vec3 size_, Texture* tex_) : id(id_), pos(pos_), size(size_), tex(tex_) {}
};