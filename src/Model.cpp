#include <Model.h>

Model::Model(const GLchar* path){
  string Path = path;
  loadModel(Path);
}
void Model::draw(ShaderProgram shader, bool useTexture){
  for(unsigned int i = 0; i < this->meshes.size(); i++){
    this->meshes[i].Draw(shader, useTexture);
  }
}

std::string get_right_of_delim(std::string const& str, std::string const& delim){
  return str.substr(str.find(delim) + delim.size());
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
    //Positions
    vertex.Position[0] = mesh->mVertices[i].x;
    vertex.Position[1] = mesh->mVertices[i].y;
    vertex.Position[2] = mesh->mVertices[i].z;
    this->maxCoordinate = fmax(this->maxCoordinate, vertex.Position[0]);
    this->maxCoordinate = fmax(this->maxCoordinate, vertex.Position[1]);
    this->maxCoordinate = fmax(this->maxCoordinate, vertex.Position[2]);
    //Normals
    if (mesh->mNormals != nullptr){
      vertex.Normal[0] = mesh->mNormals[i].x;
      vertex.Normal[1] = mesh->mNormals[i].y;
      vertex.Normal[2] = mesh->mNormals[i].z; 
    }
    //Texture coordinates
    if(mesh->mTextureCoords[0]){ //Verify the existance of texture coordinates in the mesh
      // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
      // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
      vertex.TexCoords[0] = mesh->mTextureCoords[0][i].x;
      vertex.TexCoords[1] = mesh->mTextureCoords[0][i].y;
    }else{
      vertex.TexCoords[0] = 0.0;
      vertex.TexCoords[1] = 0.0;
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
  Material materialMap;
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
    // 3. Material
    materialMap = this->loadMaterial(material);
  }
  //Return a mesh object created with the assimp mesh data
  return Mesh(vertices, indices, textures, materialMap);
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

Material Model::loadMaterial(aiMaterial* mat) {
  Material material;
  aiColor3D color(0.f, 0.f, 0.f);
  float shininess;

  mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
  material.Diffuse[0] = color.r;
  material.Diffuse[1] = color.b;
  material.Diffuse[2] = color.g;

  mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
  material.Ambient[0] = color.r;
  material.Ambient[1] = color.b;
  material.Ambient[2] = color.g;

  mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
  material.Specular[0] = color.r;
  material.Specular[1] = color.b;
  material.Specular[2] = color.g;

  mat->Get(AI_MATKEY_SHININESS, shininess);
  material.Shininess = shininess;

  return material;
}

GLint Model::TextureFromFile(const char* path, string directory){
  //Load texture and generate id
  
  istringstream iss(path);
  string aux;
  while (std::getline( iss, aux, '/' )){
  }

  string filename = string(aux);
  filename = directory + '/' + filename;
  GLuint textureID;
  glGenTextures(1, & textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  std::cout << "LOADING IMAGE " << filename.c_str() << std::endl;
  FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(filename.c_str()), filename.c_str());
  if(!bitmap){
    std::cout << "ERROR::LOADING IMAGE" << std::endl;
  }
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
