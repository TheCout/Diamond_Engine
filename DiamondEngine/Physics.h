#ifndef _physics_
#define _physics_
#pragma once
#include "Camera.h"



class PhysicsEngine 
{
private:
	Camera& camera;

public:
	PhysicsEngine(Camera& camera);
	~PhysicsEngine();
	bool ray_sphere(glm::vec3 ray_origin_wor, glm::vec3 ray_direction_wor, float sphere_radius);
};
#endif