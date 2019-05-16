#include <Model.h>

Model::Model(const GLchar* path){
  string Path = path;
  loadModel(Path);
}
void Model::draw(ShaderProgram shader){
  for(unsigned int i = 0; i < this->meshes.size(); i++){
    this->meshes[i].Draw(shader);
  }
}

void Model::loadModel(string path){
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
  //Error checking
  if(!scene || !scene->mRootNode || scene->mFlags==AI_SCENE_FLAGS_INCOMPLETE){
    std::cout << "ERROR::ASSIMP::SCENE LOADING::"<< importer.GetErrorString() << std::endl;
    return;
  }
  //Retrieve a direction path of the filepath
  this->directory = path.substr(0, path.find_last_of('/'));

  //Process ASSIMP Node with the recursive function
  this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene){
    //Get the data from the meshes and recursively process child nodes
    for(GLuint i = 0; i < node->mNumMeshes; i++){
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      this->meshes.push_back(processMesh(mesh, scene));
    }
    for(GLuint i = 0; i < node->mNumChildren; i++){
      this->processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
  vector<Vertex> vertices;
  vector<GLuint> indices;
  vector<Texture> textures;

  //Go to each of the meshes vertices
  for(GLuint i = 0; i < mesh->mNumVertices; i++){
    Vertex vertex;
    //Creating placeholder vector for converting Assimp vectors into glm vectors
    glm::vec3 vector;
    //Positions
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;
    //Normals
    vector.x = mesh->mNormals[i].x;
    vector.y = mesh->mNormals[i].y;
    vector.z = mesh->mNormals[i].z;
    vertex.Normal = vector;
    //Texture coordinates
    if(mesh->mTextureCoords[0]){ //Verify the existance of texture coordinates in the mesh
      glm::vec2 vec;
      // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
      // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoords = vec;
    }else{
      vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    }
    vertices.push_back(vertex);
  }
  //Process indices
  for(GLuint i = 0; i < mesh->mNumFaces; i++){
    //Get each face
    aiFace face = mesh->mFaces[i];
    for(GLuint j = 0; j < face.mNumIndices; j++){
      //And get each indice of that face
      indices.push_back(face.mIndices[j]);
    }
  }
  //Process materials
  if(mesh->mMaterialIndex >= 0){
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // Diffuse: texture_diffuseN
    // Specular: texture_specularN
    // Normal: texture_normalN

    // 1. Diffuse maps
    vector<Texture> diffuseMap = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());
    // 2. Specular maps
    vector<Texture> specularMap = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMap.begin(), specularMap.end());
  }
  //Return a mesh object created with the assimp mesh data
  return Mesh(vertices, indices, textures);
}

// Checks all material textures of a given type and loads the textures if they're not loaded yet.
// The required info is returned as a Texture struct.

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName){
  vector<Texture> textures;
  for(GLuint i = 0; i < mat->GetTextureCount(type); i++){
    aiString str;
    mat->GetTexture(type, i, &str);
    //Check if texture wal loaded and if so, continue to nex iteration: skip loading a new texture
    bool skip = false;
    for(GLuint j = 0; j < textures_loaded.size(); j++){
      if(textures_loaded[j].path == str){
        skip = true;
        break;
      }
    }
    if(!skip){
      //If texture hasnt been loaded
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), this->directory);
      texture.type = typeName;
      texture.path = str;
      textures.push_back(texture);
      this->textures_loaded.push_back(texture);//add loaded textures
    }
  }
  return textures;
}

GLint Model::TextureFromFile(const char* path, string directory){
  //Load texture and generate id
  string filename = string(path);
  filename = directory + '/' + filename;
  GLuint textureID;
  glGenTextures(1, & textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(filename.c_str()), filename.c_str());
  FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
  int imageHeight = FreeImage_GetHeight(pImage);
  int imageWidth = FreeImage_GetWidth(pImage);
  if(!pImage){
    std::cout << "ERROR::LOADING TEXTURE" << std::endl;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
  glGenerateMipmap(GL_TEXTURE_2D);

  //Set parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
  FreeImage_Unload(bitmap);
  FreeImage_Unload(pImage);

  return textureID;
}

Model::~Model(){

}
