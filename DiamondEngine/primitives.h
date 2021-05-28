#ifndef _primitives_
#define _primitives_
#pragma once
#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "glm/glm/glm.hpp"
#include "cg.h"
#include "Texture.h"
#include "Color.h"
#include <vector> 


#define PI 3.14159265358979323846


//Simple 2D
void Rect(face face, color color);
void FilledCircle(float radius, glm::vec3 Padding);


//Simple 3D
void Line(GLuint ID, glm::vec3 p1, glm::vec3 p2);
void Cube(GLuint ID, Texture* texture, float size, color color);
void RectangularPrism(GLuint ID, Texture* texture, glm::vec3 size, color color);
void Sphere(GLuint ID, float radius, int sectors, int stacks, color color);
void DrawGluSphere(GLuint ID, Texture* texture, float radius, int slices, int stacks, color color);
void Cylinder(int numMajor, int numMinor, float height, float radius);


//Hard 3D
void Annulus(float radius1, float radius2);
void AnnulusCone(float radius1, float radius2, float sectors);


//Complex 3D
void Arrow(GLuint ID, float radius, color color);


//Special / Not defined
void DrawTerrain(GLuint ID);
#endif