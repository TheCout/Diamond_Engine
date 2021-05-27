#pragma once
#include "glm/glm/glm.hpp"
#include <cmath>
#include <iomanip>
#include <algorithm>


struct edge;
struct face;
struct ray;


double Distance(glm::vec3 p1, glm::vec3 p2);


struct edge {
    glm::vec3 p1, p2;
    edge() : p1(0.0, 0.0, 0.0), p2(0.0, 0.0, 0.0) {}
    edge(glm::vec3 p1_, glm::vec3 p2_) : p1(p1_), p2(p2_) {}
    edge operator+(const edge& v)const { return edge(p1 + v.p1, p2 + v.p2); }
    edge operator*(float k) { return edge(p1 * k, p2 * k); }
};


struct face {
    glm::vec3 p1, p2, p3, p4;
    face() : p1(0.0, 0.0, 0.0), p2(0.0, 0.0, 0.0), p3(0.0, 0.0, 0.0), p4(0.0, 0.0, 0.0) {}
    face(glm::vec3 p1_, glm::vec3 p2_, glm::vec3 p3_, glm::vec3 p4_) : p1(p1_), p2(p2_), p3(p3_), p4(p4_) {}
    face operator+(const face& v)const { return face(p1 + v.p1, p2 + v.p2, p3 + v.p3, p4 + v.p4); }
    face operator*(float k) { return face(p1 * k, p2 * k, p3 * k, p4 * k); }
};


struct ray {
    glm::vec3 v1, v2;
    ray() : v1(0.0, 0.0, 0.0), v2(0.0, 0.0, 0.0) {}
    ray(glm::vec3 v1_, glm::vec3 v2_) : v1(v1_), v2(v2_) {}
};