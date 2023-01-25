#version 330 core

in vec3 fragPos;
in vec3 fragNorm;

out vec4 color;


uniform vec4 objectColor;

uniform int count;
uniform vec3 lightColors[10];
uniform vec3 lightPositions[10];
uniform vec3 viewPosition;

void main()
{
	float ambientStrength = 0.1f;
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPosition - fragPos);
	vec3 result = vec3(0.0f);

	for(int i = 0; i < count; i++)
	{
		vec3 ambient = ambientStrength * lightColors[i];
	
		vec3 lightDir = normalize(lightPositions[i] - fragPos);
		float diff = max(dot(fragNorm,lightDir),0.0f);
		vec3 diffuse = diff * lightColors[i];

		vec3 reflectDir = reflect(-lightDir, fragNorm);

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lightColors[i];
		result += (ambient + diffuse)/count;
	}
	


	color = vec4((result),1.0f) * objectColor;
}