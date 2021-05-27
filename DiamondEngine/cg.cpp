#include "cg.h"


double Distance(glm::vec3 p1, glm::vec3 p2) {
    double d = sqrt(pow(p2.x - p1.x, 2) +
        pow(p2.y - p1.y, 2) +
        pow(p2.z - p1.z, 2) * 1.0);
    return d;
}