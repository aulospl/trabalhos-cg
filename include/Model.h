#ifndef Model_H
#define Model_H

#pragma once

#include <string>
#include <map>
#include <vector>
//Image library include
#include <FreeImage.h>
//assimp include
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <readShader.h>
#include "Mesh.h"

using namespace std;

class Model{
  public:
    //Functions
    void draw(ShaderProgram shader);
    //Constructor and destructor
    Model(const GLchar* path);
    ~Model();
  private:
    //Data
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    //Functions

    //Load a model with ASSIMP
    void loadModel(string path);
    //Process nodes with recursive call
    void processNode(aiNode* Node, const aiScene* scene);
    //Process assimp meshesinto mesh object
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    //load textures
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    //load image to textures
    GLint TextureFromFile(const char* path, string directory);

};

#endif
