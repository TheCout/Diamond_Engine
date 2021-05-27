#include "Loader.h"
#include "ObjLoader.h"


//Textures
string DefaultPath = "Images/";




GLuint Loader::ObjectsTotal() {
    return objects_total;
}
Object Loader::getObject(int index) {
    return objects.at(objects[0].id + index - 2);
}
Object Loader::getLastObject() {
	return last_obj;
}
vector<Object>* Loader::getObjects() {
    return &objects;
}




Loader::Loader(int quantity, Texture* Tex) {
    objects_total = quantity;
    m_Tex = Tex;
}




void Loader::PreLoad() {
    objects[0].id = glGenLists(objects_total + 1);
    DrawTerrain(objects[0].id);
}


void Loader::LoadTextures(string textures_files_names[]) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    string textures_file_names[] = {"sus.png", "brickTexture.jpg", "woodTexture.jpg", "metalTexture.jpg", "woodBoxTexture.png", "worldTexture.jpg", "ricardoTexture.png"};

    for (int index = 0; index < (sizeof(textures_file_names) / sizeof(*textures_file_names)); index++) {
        m_Tex[index].Load(DefaultPath + textures_file_names[index]);
    }
}


void Loader::LoadLine(glm::vec3 p1, glm::vec3 p2) {
    int x, y, z;
    objects.push_back(last_obj);

    //Generate Info
    last_obj.id = objects[objects_total].id = objects[0].id + objects_total;
    last_obj.size = objects[objects_total].size = p2 - p1;

    //Check x, y, z (position)
    if (p2.x > p1.x)
        x = p2.x - p1.x;
    else
        x = p1.x - p2.x;
    if (p2.y > p1.y)
        y = p2.y - p1.y;
    else
        y = p1.y - p2.y;
    if (p2.z > p1.z)
        z = p2.z - p1.z;
    else
        z = p1.z - p2.z;

    last_obj.pos = objects[objects_total].pos = glm::vec3(x, y, z);

    //Load Object
    Line(last_obj.id, p1, p2);

    //Update Index
    objects_total++;
}


void Loader::LoadCube(float cube_size, glm::vec3 cube_pos, Texture* tex) {
    objects.push_back(last_obj);

    //Generate Info
    last_obj.id = objects[objects_total].id = objects[0].id + objects_total;
    last_obj.size = objects[objects_total].size = glm::vec3(cube_size, cube_size, cube_size);
    last_obj.pos = objects[objects_total].pos = cube_pos;

    //Load Object
    Cube(last_obj.id, tex, cube_size, red);

    //Update Index
    objects_total++;
}


void Loader::LoadSphere(float sphere_radius, glm::vec3 sphere_pos, Texture* tex) {
    objects.push_back(last_obj);

    //Generate Info
    last_obj.id = objects[objects_total].id = objects[0].id + objects_total;
    last_obj.size = objects[objects_total].size = glm::vec3(sphere_radius, sphere_radius, sphere_radius);
    last_obj.pos = objects[objects_total].pos = sphere_pos;

    //Load Object
    DrawGluSphere(last_obj.id, tex, sphere_radius, 10, 10, red);

    //Update Index
    objects_total++;
}


void Loader::LoadObj(string file_path, glm::vec3 pos) {
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(file_path);

    if (loadout) {
        objects.push_back(last_obj);
        //Generate ID
        last_obj.id = objects[objects_total].id = objects[0].id + objects_total;
        //Set position
        last_obj.pos = objects[objects_total].pos = pos;


        std::ofstream file("e1Out.txt");

        float matSpecular[] = { 1.f, 1.f, 1.f, 1.f };
        float matAmb[] = { 0.f, 0.f, 0.f, 1.f };
        glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, 128);
        glNewList(last_obj.id, GL_COMPILE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for (int i = 0; i < Loader.LoadedMeshes.size(); i++) {
            // Copy one of the loaded meshes to be our current mesh
            objl::Mesh curMesh = Loader.LoadedMeshes[i];
            file << "Mesh " << i << ": " << curMesh.MeshName << "\n";
            file << "Vertices:\n";

            glBegin(GL_TRIANGLES);
            for (int j = 0; j < curMesh.Vertices.size(); j++) {
                glVertex3f(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z);
            }
            glEnd();

            file << "Indices:\n";
            // Go through every 3rd index and print the triangle that these indices represent
            for (int j = 0; j < curMesh.Indices.size(); j += 3) {
                file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
            }file << "\n";
        }file.close();
        glEndList();
        //Update Index
        objects_total++;
    } else {
        std::ofstream file("e1Out.txt");
        file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";
        file.close();
    }
}


void Loader::LoadHitbox(bool show, Object ob1, Object ob2) {
    objects.push_back(last_obj);

    //Generate ID
    objects[objects_total].id = objects[0].id + objects_total;

    //Load Hitbox
    Hitbox hitbox = Hitbox(ob1);
    if (show && hitbox.isCollidingWith(ob2)) {
        hitbox.showHitbox(objects[objects_total].id);
    }
    objects[objects_total].pos = ob1.pos;

    //Update Index
    objects_total++;
}




void Loader::GenerateRandom() {
    for (int i = 0; i < objects_total; i++) {
        Object p;
        objects.push_back(p);
    }
    objects[0].id = glGenLists(objects_total + 1);
    DrawTerrain(objects[0].id);

    srand(time(0));
    for (int i = 1; i < objects_total; i++) {
        objects[i].id = objects[0].id + i;
        float x = random(-40, 40);
        float y = random(-8, 8);
        float z = random(-40, 40);
        float size = random(1.0, 2.0);
        objects[i].pos = glm::vec3(x, y, z);

        float k = (float)rand() / RAND_MAX;
        if (k <= 0.33) {
            Texture* sus_tex;
            sus_tex = &m_Tex[5];
            Cube(objects[i].id, sus_tex, size, red);
        }
        else if (k <= 0.665) {
            Texture* world_tex;
            world_tex = &m_Tex[3];
            DrawGluSphere(objects[i].id, world_tex, 1.0, 1.0, 10, red);
        }
        else {
            Arrow(objects[i].id, 0.3, green);
        }
    }
}




void Loader::DrawEverything() {
    glCallList(objects[0].id);
    for (int i = 1; i < objects_total; i++) {
        float x = objects[i].pos.x;
        float y = objects[i].pos.y;
        float z = objects[i].pos.z;
        glPushMatrix();
        glTranslatef(x, y, z);
        glCallList(objects[i].id);
        glPopMatrix();
    }
}