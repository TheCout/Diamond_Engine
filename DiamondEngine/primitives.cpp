#include "primitives.h"


#ifdef __WXMAC__
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif



void Rect(face face, color color) {
    glColor3fv(color);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3fv(&face.p1.x);
    glTexCoord2f(1.0, 0.0); glVertex3fv(&face.p2.x);
    glTexCoord2f(1.0, 1.0); glVertex3fv(&face.p3.x);
    glTexCoord2f(0.0, 1.0); glVertex3fv(&face.p4.x);
    glEnd();
}



void FilledCircle(float radius, glm::vec3 Padding) {
    float x1, y1, x2, y2;
    x1 = 0.0, y1 = 0.0;

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x1 +Padding.x, y1 + Padding.y, Padding.z);
    for (float angle = 1.0f; angle < 361.0f; angle += 0.2) {
        x2 = x1 + sin(angle) * radius;
        y2 = y1 + cos(angle) * radius;
        glVertex3f(x2 + Padding.x, y2 + Padding.y, Padding.z);
    }
    glEnd();
}



void Line(GLuint ID, glm::vec3 p1, glm::vec3 p2) {
    glNewList(ID, GL_COMPILE);
    glBegin(GL_LINES);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    glEnd();
    glEndList();
}



void Cube(GLuint ID, Texture* texture, float size, color color) {
    float d = size / 2.0;
    glm::vec3 v1 = { -d,  d,  d };
    glm::vec3 v2 = { -d, -d,  d };
    glm::vec3 v3 = {  d, -d,  d };
    glm::vec3 v4 = {  d,  d,  d };
    glm::vec3 v5 = {  d,  d, -d };
    glm::vec3 v6 = {  d, -d, -d };
    glm::vec3 v7 = { -d, -d, -d };
    glm::vec3 v8 = { -d,  d, -d };

    float matSpecular[] = { 1.f, 1.f, 1.f, 1.f };
    float matAmb[] = { 0.f, 0.f, 0.f, 1.f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
    glNewList(ID, GL_COMPILE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture->Bind();


    //Front
    face fac1 = { v1, v2, v3, v4 };
    glNormal3f(0.f, 0.f, 1.f);
    Rect(fac1, color);

    //Right
    face fac2 = { v4, v3, v6, v5 };
    glNormal3f(1.f, 0.f, 0.f);
    Rect(fac2, color);

    //Back
    face fac3 = { v5, v8, v7, v6 };
    glNormal3f(0.f, 0.f, -1.f);
    Rect(fac3, color);

    //Left
    face fac4 = { v1, v8, v7, v2 };
    glNormal3f(-1.f, 0.f, 0.f);
    Rect(fac4, color);

    //Top
    face fac5 = { v1, v4, v5, v8 };
    glNormal3f(0.f, 1.f, 0.f);
    Rect(fac5, color);

    //Bottom
    face fac6 = { v2, v7, v6, v3 };
    glNormal3f(0.f, -1.f, 0.f);
    Rect(fac6, color);

    texture->UnBind();
    glEndList();
}



void RectangularPrism(GLuint ID, Texture* texture, glm::vec3 size, color color) {
    float w = size.x / 2.0;
    float h = size.y / 2.0;
    float z = size.z / 2.0;
    glm::vec3 v1 = { -w,  h,  z };
    glm::vec3 v2 = { -w, -h,  z };
    glm::vec3 v3 = { w, -h,  z };
    glm::vec3 v4 = { w,  h,  z };
    glm::vec3 v5 = { w,  h, -z };
    glm::vec3 v6 = { w, -h, -z };
    glm::vec3 v7 = { -w, -h, -z };
    glm::vec3 v8 = { -w,  h, -z };

    float matSpecular[] = { 1.f, 1.f, 1.f, 1.f };
    float matAmb[] = { 0.f, 0.f, 0.f, 1.f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
    glNewList(ID, GL_COMPILE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture->Bind();


    //Front
    face fac1 = { v1, v2, v3, v4 };
    glNormal3f(0.f, 0.f, 1.f);
    Rect(fac1, color);

    //Right
    face fac2 = { v4, v3, v6, v5 };
    glNormal3f(1.f, 0.f, 0.f);
    Rect(fac2, color);

    //Back
    face fac3 = { v5, v8, v7, v6 };
    glNormal3f(0.f, 0.f, -1.f);
    Rect(fac3, color);

    //Left
    face fac4 = { v1, v8, v7, v2 };
    glNormal3f(-1.f, 0.f, 0.f);
    Rect(fac4, color);

    //Top
    face fac5 = { v1, v4, v5, v8 };
    glNormal3f(0.f, 1.f, 0.f);
    Rect(fac5, color);

    //Bottom
    face fac6 = { v2, v7, v6, v3 };
    glNormal3f(0.f, -1.f, 0.f);
    Rect(fac6, color);

    texture->UnBind();
    glEndList();
}



void Sphere(GLuint ID, float radius, int sectors, int stacks, color color) {
    std::vector<glm::vec3> points;
    GLfloat deltaPhi = PI / stacks;
    GLfloat deltaTheta = 2 * PI / sectors;

    for (GLuint i = 0; i < stacks; i++) {
        GLfloat phi = -PI / 2.0 + i * deltaPhi;
        GLfloat temp = radius * cos(phi);
        GLfloat y = radius * sin(phi);
        for (GLuint j = 0; j < sectors; j++) {
            GLfloat theta = j * deltaTheta;
            GLfloat x = temp * sin(theta);
            GLfloat z = temp * cos(theta);

            points.push_back(glm::vec3(x, y, z));
        }
    }
    glNewList(ID, GL_COMPILE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);
    glColor4fv(color);
    for (GLuint i = 1; i < points.size() - sectors - 1; i++) {
        glVertex3fv(&points[i].x);
        glVertex3fv(&points[(i + sectors)].x);
        glVertex3fv(&points[i + 1].x);
        glVertex3fv(&points[i + 1].x);
        glVertex3fv(&points[(i + sectors)].x);
        glVertex3fv(&points[(i + sectors) + 1].x);
    }
    glEnd();
    glEndList();
}



void DrawGluSphere(GLuint ID, Texture* texture, float radius, int slices, int stacks, color color) {
    GLUquadricObj* quadricObj = gluNewQuadric();
    gluQuadricDrawStyle(quadricObj, GLU_FILL);
    gluQuadricTexture(quadricObj, GL_TRUE);
    gluQuadricNormals(quadricObj, GLU_SMOOTH);

    glNewList(ID, GL_COMPILE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture->Bind();
    glColor3fv(color);
    gluSphere(quadricObj, radius, slices, stacks);
    texture->UnBind();
    glEndList();
}



void Annulus(float radius1, float radius2) {
    float x1, y1, x2, y2;
    glBegin(GL_TRIANGLES);
    for (float angle = 1.0f; angle < 361.0f; angle += 0.2) {
        x1 = sin(angle) * radius2;
        y1 = cos(angle) * radius2;
        glVertex2f(x1, y1);
        x2 = x1 + sin(angle) * radius1;
        y2 = y1 + cos(angle) * radius1;
        glVertex2f(x2, y2);
    }
    glEnd();
}



void AnnulusCone(float radius1, float radius2, float sectors) {
    std::vector<glm::vec2> points;

    float x1, y1, x2, y2;
    glBegin(GL_TRIANGLES);
    for (float angle = 1.0f; angle < sectors; angle += 0.2) {
        x1 = sin(angle) * radius2;
        y1 = cos(angle) * radius2;
        glVertex3f(x1, y1, 0);
        x2 = x1 + sin(angle) * radius1;
        y2 = y1 + cos(angle) * radius1;
        points.push_back(glm::vec2(x2, y2));
        glVertex3f(x2, y2, 0);
    }
    for (int i = 1; i < points.size(); i++) {
        glVertex2fv(&points[i].x);
        glVertex3f(0, 0, -radius1 * 2);
    }
    glEnd();
}



void Cylinder(int numMajor, int numMinor, float height, float radius) {
    double majorStep = height / numMajor;
    double minorStep = 2.0 * M_PI / numMinor;
    int i, j;

    FilledCircle(radius, glm::vec3(0.0, 0.0, -(0.5 * height)));
    FilledCircle(radius, glm::vec3(0.0, 0.0, 0.5 * height));
    for (i = 0; i < numMajor; ++i) {
        GLfloat z0 = 0.5 * height - i * majorStep;
        GLfloat z1 = z0 - majorStep;

        glBegin(GL_TRIANGLE_STRIP);
        for (j = 0; j <= numMinor; ++j) {
            double a = j * minorStep;
            GLfloat x = radius * cos(a);
            GLfloat y = radius * sin(a);
            glNormal3f(x / radius, y / radius, 0.0);
            glTexCoord2f(j / (GLfloat)numMinor, i / (GLfloat)numMajor);
            glVertex3f(x, y, z0);
            glNormal3f(x / radius, y / radius, 0.0);
            glTexCoord2f(j / (GLfloat)numMinor, (i + 1) / (GLfloat)numMajor);
            glVertex3f(x, y, z1);
        }
        glEnd();
    }
}



void Arrow(GLuint ID, float radius, color color) {
    glNewList(ID, GL_COMPILE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glColor3fv(color);
    AnnulusCone(radius, radius / 2, 100.0f);
    glTranslatef(0, 0, 0.5 * (radius * 2));
    Cylinder(2, 16, radius * 2, radius / 2);

    glEndList();
}



void DrawTerrain(GLuint ID) {
    float L = 500.0;
    float incr = 1.0;
    float y = -0.5;

    glNewList(ID, GL_COMPILE);
    glColor3fv(white);
    glBegin(GL_LINES);
    for (float i = -L; i <= L; i += incr) {
        glVertex3f(i, y, -L);
        glVertex3f(i, y, L);

        glVertex3f(-L, y, i);
        glVertex3f(L, y, i);
    }
    glEnd();
    glEndList();
}