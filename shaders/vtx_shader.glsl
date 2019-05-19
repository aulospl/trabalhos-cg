#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;

void main()
{
  gl_Position = model * vec4(aPos, 1.0f);
  TexCoords = texCoords;
  Normal = mat3(transpose(inverse(model))) * normal;
  //lightPos = vec3(vec4(lightPosition, 1.0f));
  FragPos = vec3(model * vec4(aPos, 1.0f));
}
