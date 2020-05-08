#version 330 core

struct Material 
{
	vec3 ambientClr;
	vec3 diffuseClr;
	vec3 specularClr;
	float shininess;

	sampler2D diffuseTexture;
	sampler2D specTexture;
};

struct Light
{
	vec3 position;

	vec3 ambientClr;
	vec3 diffuseClr;
	vec3 specularClr;
	vec3 direction;
};


in vec3 normal;
in vec3 fragPos;
in vec2 TexCoords;

//uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

out vec4 fragColor;


void main()
{
	//float ambientStrength = 0.1;
	vec3 ambient = light.ambientClr * texture(material.diffuseTexture, TexCoords).xyz;   // 


	vec3 norm = normalize(normal);
	//vec3 lightDir = normalize(light.position - fragPos);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuseClr * (diff * texture(material.diffuseTexture, TexCoords).rgb);   //


	//float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fragPos);    // FUCKING NORMALIZE
	vec3 reflectionDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectionDir, viewDir), 0.0), material.shininess);
	vec3 specular = light.specularClr * (spec * ( texture(material.specTexture, TexCoords).rgb  + vec3(0.2)) );


	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0);

}