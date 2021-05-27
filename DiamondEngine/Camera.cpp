#include "Camera.h"


Camera::Camera() {
	m_pos = glm::vec3(0, 0, 0);
	m_dir = glm::vec3(0, 0, -1);
	m_left = glm::vec3(-1, 0, 0);
	m_up = glm::vec3(0, 1, 0);
	m_vel = glm::vec3(0, 0, 0);
}


Camera::~Camera() {

}


void Camera::activate() {
	look = m_pos + m_dir;
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
}


glm::mat4 Camera::getViewMatrix() {
	glm::vec3 z = look - m_pos;
	glm::normalize(z);
	glm::vec3 y = m_up;
	glm::vec3 x = glm::cross(y, z);

	glm::dot(-x, m_pos);
	glm::mat4 view_matrix = {
		x.x, y.x, z.x, glm::dot(-x, look),
		x.y, y.y, z.y, glm::dot(-y, look),
		x.z, y.z, z.z, glm::dot(-z, look),
		0, 0, 0, 1.0
	};
	return view_matrix;
}


void Camera::forward() {
	m_vel = m_dir * m_scl;
	m_pos = m_pos + m_vel;
}
void Camera::back() {
	m_vel = m_dir * -m_scl;
	m_pos = m_pos + m_vel;
}
void Camera::left() {
	m_vel = m_left * m_scl;
	m_pos = m_pos + m_vel;
}
void Camera::right() {
	m_vel = m_left * -m_scl;
	m_pos = m_pos + m_vel;
}


void Camera::up() {
	m_vel = m_up * m_scl;
	m_pos = m_pos + m_vel;
}
void Camera::down() {
	m_vel = m_up * -m_scl;
	m_pos = m_pos + m_vel;
}


void Camera::updateYaw(float dYaw, float dYawy) {
	m_yaw += dYaw;
	m_yawy += dYawy;
}


void Camera::update() {
	float ang = cvtToRad(m_yaw);
	float angy = cvtToRad(m_yawy);
	m_dir.x = sin(ang);
	m_dir.y = -cos(angy);
	m_dir.z = -cos(ang);
	glm::normalize(m_dir);
	m_left = glm::cross(m_up, m_dir);
}