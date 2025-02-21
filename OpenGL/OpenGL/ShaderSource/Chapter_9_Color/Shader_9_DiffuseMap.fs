#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// 搭配 Material 一起使用, 使用光照贴图
in vec2 TexCoords;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

// 如果要使用 sampler2D, 需要设置为uniform
uniform Material material;
uniform Light light;
void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos -	FragPos);
	vec3 norm = normalize(Normal);
	vec3 reflectDir = reflect(-lightDir, norm);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}