#version 330 core

in vec3 normal;
in vec3 fragPos;


uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


out vec4 fragColor;


void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;   // 


	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;   //


	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fragPos);    // FUCKING NORMALIZE
	vec3 reflectionDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectionDir, viewDir), 0.0), 32.0);
	vec3 specular = specularStrength * spec * lightColor;


	vec3 result = (ambient + diffuse + specular) * objectColor;
	fragColor = vec4(result, 1.0);

}