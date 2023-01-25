#version 330 core

in vec3 fragPos;
in vec3 fragNorm;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
	color = texture2D(texture_diffuse1, TexCoords);
}