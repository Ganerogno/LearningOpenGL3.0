#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	glm::vec3 cameraPos;
	static glm::vec3 cameraDir;
	glm::vec3 cameraUp;
	GLfloat cameraSpeed = 0.05f;
	static glm::mat4x4 ViewMatrix;
	static GLfloat yaw;
	static GLfloat pitch;
	static GLfloat lastX;
	static GLfloat lastY;
	static bool firstTest;
public:
	static bool keys[];
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 dir = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

	void Update();
	static void MoveMouse(GLFWwindow* window, double xpos, double ypos);
	static glm::mat4x4 GetMatrix();
	glm::vec3 GetPosition();
};

