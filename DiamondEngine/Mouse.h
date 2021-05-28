#ifndef _mouse_
#define _mouse_
#pragma once
#include "glm/glm/glm.hpp"
#include "Camera.h"
#include "GLpane.h"
#include "cg.h"
#include <algorithm>
#include <math.h>
#include <new>


class Mouse 
{
private:
    Camera& camera;

    glm::vec2 m_screen_size;
    glm::vec2 m_pos;
    glm::vec3 normalized_pos;
public:
    glm::vec3 pos;

    Mouse(Camera& camera);
    ~Mouse();

    glm::vec2 getPos() { return pos; };
    void setPos(glm::vec2 pos) { m_pos = pos; };
    glm::vec3 toEyeSpace();
    glm::vec3 toWorldSpace(glm::vec3 eye_space_pos);
};
#endif