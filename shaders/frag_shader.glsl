#version 450 core
	out vec4 color;

struct  Texture {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

uniform Texture text;

uniform bool useTexture;

void main(){
  vec3 lightColor = vec3(1.0,1.0,1.0);
  vec3 lightPos = vec3(0.0,0.0,2.0);
  if (useTexture){
    color =  mix(texture(text.diffuse, TexCoords), texture(text.specular, TexCoords), 1.0);  
  }else{
    // ambient
    vec3 ambient = lightColor * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);
    
    // specular
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);  
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = lightColor * (spec * material.specular);  
        
    vec3 result = ambient;
    color = vec4(result, 1.0);
  }
  

}
