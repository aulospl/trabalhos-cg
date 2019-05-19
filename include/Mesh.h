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

class Mesh {
public:
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    /*  Functions  */
    // Constructor
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    // Render the mesh
    void Draw(ShaderProgram shader);

private:
    /*  Render data  */
    GLuint VAO, VBO, EBO;

    /*  Functions    */
    // Initializes all the buffer objects/arrays
    void setupMesh();
};

#endif
