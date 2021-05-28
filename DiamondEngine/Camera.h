#ifndef _camera_
#define _camera_
#pragma once
#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "glm/glm/glm.hpp"
#include "cg.h"
#include "math.h"
#include <iostream>
#include <vector> 


#ifdef __WXMAC__
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif


# define PI 3.14159265358979323846


class Camera {
private:
	Camera* camera;

	glm::vec3 look;
	glm::vec3 m_dir;
	glm::vec3 m_left;
	glm::vec3 m_up;
	glm::vec3 m_vel;
	float m_scl = 0.25;

	friend class PhysicsEngine;
	friend class Mouse;

public:
	glm::vec3 m_pos;

	float m_yaw = 0;
	float m_yawy = 0;
	Camera();
	~Camera();
	void activate();

	glm::mat4 getViewMatrix();

	void forward();
	void back();
	void left();
	void right();

	void up();
	void down();

	void updateYaw(float dYaw, float dYawy);
	void update();
};
#endif