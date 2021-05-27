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



PhysicsEngine::PhysicsEngine(Camera& _camera) : camera(_camera) {}
PhysicsEngine::~PhysicsEngine() {}



bool PhysicsEngine::ray_sphere(glm::vec3 ray_origin_wor, glm::vec3 ray_direction_wor, float sphere_radius) {
	/*glm::vec3 v = glm::vec3(m_Transformation.GetPos().x, m_Transformation.GetPos().y, 0.5f) - camera.m_pos;
	long double a = glm::dot(ray_direction_wor, ray_direction_wor);
	long double b = 2.0 * glm::dot(v, ray_direction_wor);
	long double c = glm::dot(v, v) - sphere_radius * sphere_radius;
	long double b_squared_minus_4ac = b * b + (-4.0) * a * c;

	if (b_squared_minus_4ac == 0) {
		// One real root 
		return true;
	}
	else if (b_squared_minus_4ac > 0) {
		// Two real roots 
		long double x1 = (-b - sqrt(b_squared_minus_4ac)) / (2.0 * a);
		long double x2 = (-b + sqrt(b_squared_minus_4ac)) / (2.0 * a);

		if (x1 >= 0.0 || x2 >= 0.0)
			return true;
		if (x1 < 0.0 || x2 >= 0.0)
			return true;
	}*/
	return false;
}