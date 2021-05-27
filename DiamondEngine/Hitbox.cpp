#include "Hitbox.h"



bool Hitbox::isColliding() {
    return colliding;
}
glm::vec3* Hitbox::getVertices() {
    return vertices;
}
edge* Hitbox::getEdges() {
    return edges;
}
face* Hitbox::getFaces() {
    return faces;
}



void Hitbox::generateEdges() {
    edge ed1  = edges[0]  = { vertices[0], vertices[1] };
    edge ed2  = edges[1]  = { vertices[0], vertices[3] };
    edge ed3  = edges[2]  = { vertices[0], vertices[7] };
    edge ed4  = edges[3]  = { vertices[1], vertices[2] };
    edge ed5  = edges[4]  = { vertices[1], vertices[6] };
    edge ed6  = edges[5]  = { vertices[2], vertices[3] };
    edge ed7  = edges[6]  = { vertices[2], vertices[5] };
    edge ed8  = edges[7]  = { vertices[3], vertices[4] };
    edge ed9  = edges[8]  = { vertices[4], vertices[7] };
    edge ed10 = edges[9]  = { vertices[4], vertices[5] };
    edge ed11 = edges[10] = { vertices[5], vertices[6] };
    edge ed12 = edges[11] = { vertices[7], vertices[6] };
}



void Hitbox::generateFaces() {
    //Front
    face fac1 = faces[0] = { vertices[0], vertices[1], vertices[2], vertices[3] };
    //Right
    face fac2 = faces[1] = { vertices[3], vertices[2], vertices[5], vertices[4] };
    //Back
    face fac3 = faces[2] = { vertices[4], vertices[7], vertices[6], vertices[5] };
    //Left
    face fac4 = faces[3] = { vertices[0], vertices[7], vertices[6], vertices[1] };
    //Top
    face fac5 = faces[4] = { vertices[0], vertices[3], vertices[4], vertices[7] };
    //Bottom
    face fac6 = faces[5] = { vertices[1], vertices[6], vertices[5], vertices[2] };
}



Hitbox::Hitbox(Object obj) {

    glm::vec3 pos, size;
    pos = obj.pos;
    size = obj.size;

    m_pos = pos; m_size = size;
    float x = size.x / 2.0 + 0.01;
    float y = size.y / 2.0 + 0.01;
    float z = size.z / 2.0 + 0.01;

    float pos_x = pos.x;
    float pos_y = pos.y;
    float pos_z = pos.z;

    glm::vec3 v1 = vertices[0] = { -x,  y,  z };
    glm::vec3 v2 = vertices[1] = { -x, -y,  z };
    glm::vec3 v3 = vertices[2] = {  x, -y,  z };
    glm::vec3 v4 = vertices[3] = {  x,  y,  z };
    glm::vec3 v5 = vertices[4] = {  x,  y, -z };
    glm::vec3 v6 = vertices[5] = {  x, -y, -z };
    glm::vec3 v7 = vertices[6] = { -x, -y, -z };
    glm::vec3 v8 = vertices[7] = { -x,  y, -z };

    generateEdges();
    generateFaces();
}



void Hitbox::showHitbox(GLuint ID) {
    glNewList(ID, GL_COMPILE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    for (int i = 0; i < sizeof(edges) / sizeof(*edges); i++) {
        glVertex3f(edges[i].p1.x, edges[i].p1.y, edges[i].p1.z);
        glVertex3f(edges[i].p2.x, edges[i].p2.y, edges[i].p2.z);
    }
    glEnd();
    glEndList();
}




bool Hitbox::isCollidingWith(Object obj) {

    glm::vec3 pos, size;
    pos = obj.pos;
    size = obj.size;

    if (pos.x + size.x / 2 > m_pos.x - m_size.x / 2  &&  pos.x - size.x / 2 < m_pos.x + m_size.x / 2   ||   pos.x - size.x / 2 < m_pos.x + m_size.x / 2  &&  pos.x - size.x / 2 > m_pos.x - m_size.x / 2) {
        if (pos.y + size.y / 2 > m_pos.y - m_size.y / 2 && pos.y - size.y / 2 < m_pos.y + m_size.y / 2   ||   pos.y - size.y / 2 < m_pos.y + m_size.y / 2 && pos.y - size.y / 2 > m_pos.y - m_size.y / 2) {
            if (pos.z + size.z / 2 > m_pos.z - m_size.z / 2 && pos.z - size.z / 2 < m_pos.z + m_size.z / 2   ||   pos.z - size.z / 2 < m_pos.z + m_size.z / 2 && pos.z - size.z / 2 > m_pos.z - m_size.z / 2) {
                colliding = true;
                return colliding;
            }
        }
    }
    colliding  = false;
    return colliding;
}




Hitbox::~Hitbox() {
}