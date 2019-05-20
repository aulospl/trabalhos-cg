#ifndef Mesh_H
#define Mesh_H

#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
// GL Includes
#include <glad/glad.h> // Contains all the necessery OpenGL includes
#include <assimp/scene.h>

#include <readShader.h>


struct Vertex {
    // Position
    float Position[3];
    // Normal
    float Normal[3];
    // TexCoords
    float TexCoords[2];
};

struct Texture {
    GLuint id;
    string type;
    aiString path;
};

struct Material {
    float Diffuse[3];
    float Specular[3];
    float Ambient[3];
    float Shininess;
};

class Mesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    Material material;
    /*  Functions  */
    // Constructor
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, Material);
    // Render the mesh
    void Draw(ShaderProgram shader, bool useTexture);

private:
    /*  Render data  */
    GLuint VAO, VBO, EBO;

    /*  Functions    */
    // Initializes all the buffer objects/arrays
    void setupMesh();
};

#endif
