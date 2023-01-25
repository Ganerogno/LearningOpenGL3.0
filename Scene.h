#pragma once

#include <vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "ComplexObject.h"

class Scene
{
	std::vector<GLObject*> objects;
	std::vector<glm::vec3> lightPositions;
	std::vector<glm::vec3> lightColors;
	GLuint lights;
	Shader* shader;
	Camera& camera;
public:
	Scene(Shader &sShader, Camera& sCamera);
	void AddObject(GLObject& object);
	void AddLight(SimpleObject&light, glm::vec3 pos, glm::vec3 color);
	void GenerateLightsBuffer();
	void UseLights();
	void Draw();
};

