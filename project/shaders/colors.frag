#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec2 TexCoords;




struct Material 
{
	//vec3 ambientClr;
	//vec3 diffuseClr;
	//vec3 specularClr;
	float shininess;

	sampler2D diffuseTexture;
	sampler2D specTexture;
};


struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


struct PointLight
{
	vec3 position;

	float k_constant;
	float k_linear;
	float k_quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float cutoff;
	float cutoffOuter;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float k_constant;
	float k_linear;
	float k_quadratic;
};




vec3 CalcDirLight (DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal,  vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir);



uniform Material material;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform vec3 viewPos;





//uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform vec3 lightPos;




out vec4 fragColor;







void main()
{
// properties
vec3 norm = normalize(normal);
vec3 viewDir = normalize(viewPos - fragPos);

// phase 1: Directional lighting
vec3 result = CalcDirLight(dirLight, norm, viewDir);
//vec3 result = vec3(0.0);


// phase 2: Point lights

	//result += CalcPointLight(pointLights[0], norm, fragPos, viewDir);
	//result += CalcPointLight(pointLights[1], norm, fragPos, viewDir);

// phase 3: Spot light
result += CalcSpotLight(spotLight, norm, fragPos, viewDir);

fragColor = vec4(result, 1.0);


}



vec3 CalcDirLight (DirLight light, vec3 normal, vec3 viewDir)
{

	vec3 lightDir = normalize(-light.direction);
	// ambient


	// diffuse
	float diff = max(    dot(normal, lightDir), 0.0);

	// specular
	vec3 reflectionDir = reflect(-lightDir, normal);
	float spec = pow( max(   dot(reflectionDir, viewDir), 0.0),  material.shininess);

	// combined
	vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specTexture, TexCoords));

	return (ambient + diffuse + specular);

}



vec3 CalcPointLight(PointLight light, vec3 normal,  vec3 fragPos, vec3 viewDir)
{

	vec3 lightDir = normalize(light.position - fragPos);
	// ambient


	// diffuse
	float diff = max(    dot(normal, lightDir), 0.0);

	// specular
	vec3 reflectionDir = reflect(-lightDir, normal);
	float spec = pow( max(   dot(reflectionDir, viewDir), 0.0),  material.shininess);

	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / ( light.k_constant + light.k_linear * distance + light.k_quadratic * (distance * distance)   );


	vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, TexCoords));
	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuseTexture, TexCoords));
	vec3 specular = spec * light.specular * vec3(texture(material.specTexture, TexCoords));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}




vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir)
{

	vec3 lightDir = normalize(spotLight.position - fragPos);

	float theta = dot( lightDir, normalize(-spotLight.direction));
	float epsilon = spotLight.cutoff - spotLight.cutoffOuter;
	float intensity =     clamp ((theta - spotLight.cutoffOuter) / epsilon, 0.0, 1.0);


		// diffuse
		float diff = max (  dot(normal, viewDir), 0.0);


		// specular
			vec3 reflectionDir = reflect(-lightDir, normal);
	float spec = pow( max(   dot(reflectionDir, viewDir), 0.0),  material.shininess);

		// attenuation
	float distance = length(spotLight.position - fragPos);
	float attenuation = 1.0 / ( spotLight.k_constant + spotLight.k_linear * distance + spotLight.k_quadratic * (distance * distance)   );


	vec3 ambient = spotLight.ambient * vec3(texture(material.diffuseTexture, TexCoords));
	vec3 diffuse = diff * spotLight.diffuse * vec3(texture(material.diffuseTexture, TexCoords));
	vec3 specular = spec * spotLight.specular * vec3(texture(material.specTexture, TexCoords));

	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

		return (ambient + diffuse + specular);

}