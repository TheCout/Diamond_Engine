#pragma once
#include "glm/glm/glm.hpp"
#include "Texture.h"
#include "Object.h"
#include "Hitbox.h"
#include "primitives.h"
#include "math.h"
#include <vector>


using namespace std;


class Loader {
	//List
	GLuint objects_total;
	vector<Object> objects;
	//Last object of the list
	Object last_obj;
	//Texture
	Texture* m_Tex;

public:
	GLuint ObjectsTotal();
	Object getObject(int index);
	Object getLastObject();
	vector<Object>* getObjects();

	Loader(int quantity, Texture* Tex);

	void PreLoad();
	void LoadTextures(string textures_files_names[]);
	void LoadLine(glm::vec3 p1, glm::vec3 p2);
	void LoadCube(float cube_size, glm::vec3 cube_pos, Texture* tex);
	void LoadSphere(float sphere_radius, glm::vec3 sphere_pos, Texture* tex);
	void LoadObj(string file_path, glm::vec3 pos);
	void LoadHitbox(bool show, Object ob1, Object ob2);

	void GenerateRandom();

	void DrawEverything();
};
