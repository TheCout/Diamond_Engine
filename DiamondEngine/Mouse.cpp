#include "Mouse.h"


Mouse::Mouse(Camera& _camera) : m_pos(glm::vec2(0.0, 0.0)), camera(_camera), m_screen_size(glm::vec2(423.0, 267.0))  {}
Mouse::~Mouse() {}



glm::vec3 Mouse::toEyeSpace() {
    GLdouble x, y, z;

    int* viewport = new int[4];
    double* modelview = new double[16];
    double* projection = new double[16];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    //Real Mouse y coordinate 
    GLfloat realY = (float)viewport[3] - (float)m_pos.y;

    //Get Mouse Depth
    GLfloat fb[1];
    glReadPixels(m_pos.x, realY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, fb);
    gluUnProject(m_pos.x, realY, fb[0], modelview, projection,
        viewport, &x, &y, &z);

    float normalizedX = ((m_pos.x - (m_screen_size.x/2)) / (m_screen_size.x)) * 2;
    float normalizedY = ((m_pos.y - (m_screen_size.y/2)) / (m_screen_size.y)) * 2;

    normalized_pos = (glm::vec3(normalizedX, normalizedY, z));
    return glm::vec3(camera.m_dir.x, camera.m_dir.y, z);
}



glm::vec3 Mouse::toWorldSpace(glm::vec3 eye_space_pos) {
    float ang = cvtToRad(camera.m_yaw);
    float angy = cvtToRad(camera.m_yawy);

    //Opengl default fov is 45
    float fov = 45.0f;
    //Gets mouse rotation in radians
    float mouseX = cvtToRad(fov / 2 * normalized_pos.x);
    float mouseY = cvtToRad((fov / 2 * normalized_pos.y) / (PI / 2));
    //Gets the real mouse pos;
    float realX = (camera.m_pos.x - (eye_space_pos.z * sin(ang + mouseX)));
    float realY = (camera.m_pos.y - (eye_space_pos.z * -cos(angy + mouseY)));
    float realZ = (camera.m_pos.z - (eye_space_pos.z * -cos(ang + mouseX)));
    glm::vec3 realPos(realX, realY, realZ);

    pos = realPos;
    return realPos;
}