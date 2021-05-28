#ifndef _hitbox_
#define _hitbox_
#pragma once
#include "cg.h"
#include "GLpane.h"
#include "Object.h"


class Hitbox {
	bool colliding = false;
	glm::vec3 m_pos;
	glm::vec3 m_size;
	glm::vec3 vertices[8];
	edge edges[12];
	face faces[6];

	void generateEdges();
	void generateFaces();

public:
	Hitbox() {}
	Hitbox(Object obj);

	bool isColliding();
	glm::vec3 * getVertices();
	edge * getEdges();
	face * getFaces();

	void showHitbox(GLuint ID);
	bool isCollidingWith(Object obj);

	~Hitbox();
};
#endif