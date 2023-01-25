#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
{
	cameraPos = pos;
	cameraDir = dir;
	cameraUp = up;
	Update();
}
void Camera::Update()
{
	ViewMatrix = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);
}

void Camera::MoveMouse(GLFWwindow* window, double xpos, double ypos)
{
    GLfloat sensitivity = 5;
    xpos *= sensitivity;
    ypos *= sensitivity;

    yaw += xpos;
    pitch -= ypos;

    glfwSetCursorPos(window, 400, 400);

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    //front.x = cos(yaw) * cos(pitch);
    //front.y = sin(pitch);
    //front.z = sin(yaw) * cos(pitch);
    cameraDir = glm::normalize(front);
}
glm::mat4x4 Camera::GetMatrix()
{
	return ViewMatrix;
}
glm::vec3 Camera::GetPosition()
{
    return cameraPos;
}