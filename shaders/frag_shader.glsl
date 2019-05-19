#version 450 core
	out vec4 color;

struct  Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


uniform Material material;


void main(){

  color =  mix(texture(material.diffuse, TexCoords), texture(material.specular, TexCoords), 0.2);
}
