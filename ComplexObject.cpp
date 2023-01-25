#include "ComplexObject.h"

ComplexObject::ComplexObject(Shader& oShader, glm::mat4x4 oMatrix, float size, float cSpeed) : GLObject(oShader,oMatrix)
{
	currentAnimation = 0;
	currentTime = 0;
	Scale(glm::vec3(size, size, size));
	coeff = 1 / size;
	speed = cSpeed;
	viewDir = glm::vec3(0.0f, 0.0f, -1.0f);
	position = glm::vec3(1.0f);
}
void ComplexObject::Draw()
{
	shader.Use();
	glPolygonMode(GL_FRONT, GL_LINE);
	GLint modelLoc = glGetUniformLocation(shader.GetProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	GLint viewLoc = glGetUniformLocation(shader.GetProgram(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Camera::GetMatrix()));
	GLint projectionLoc = glGetUniformLocation(shader.GetProgram(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	if (currentAnimation < animations.size())
	{

		animations[currentAnimation]->setBoneTransformations(currentTime += 0.04, shader);
		animations[currentAnimation]->Draw(shader);
	}
	shader.UseBaseShader();
	if (controlledObject && currentAnimation == 1 && currentTime > 5)
	{
		currentTime = 0;
		ChangeViewDir();
	}
}
void ComplexObject::ChangeCurrentAnimation(GLuint i)
{
	currentAnimation = i;
	currentTime = 0;
}
void ComplexObject::AddAnimation(SkinnedMesh& mesh)
{
	animations.push_back(&mesh);
}
void ComplexObject::Translate(glm::vec3 pos)
{
	glm::vec3 temp(pos.x * coeff,pos.y * coeff,pos.z * coeff);
	GLObject::Translate(temp);
	position += temp;
}
void ComplexObject::Rotate(float angle, glm::vec3 pos)
{
	GLObject::Rotate(angle, pos);
	glm::mat4 temp(1);
	temp = glm::rotate(temp, glm::radians(angle), viewDir);
	std::cout << viewDir.x << " " << viewDir.y << " " << viewDir.z << std::endl;
	viewDir *= glm::vec3(temp * glm::vec4(viewDir, 1.0f));
	std::cout << viewDir.x << " " << viewDir.y << " " << viewDir.z << std::endl;
}

void ComplexObject::MoveFront()
{
	glm::vec3 temp = speed * viewDir;
	Translate(glm::vec3(temp.x, 0, temp.z));
}
void ComplexObject::Move()
{
	if (controlledObject)
	{
		if (currentAnimation != 1)
			ChangeCurrentAnimation(1);
		Translate(viewDir * speed);
	}
	else
	{
		if (Camera::keys[GLFW_KEY_W])
		{
			MoveFront();
			if (currentAnimation != 1)
				ChangeCurrentAnimation(1);
		}
		else
		{
			Stand();
		}
		if (Camera::keys[GLFW_KEY_A])
		{
			Rotate(10, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (Camera::keys[GLFW_KEY_D])
		{
			Rotate(-10, glm::vec3(0.0f, 1.0f, 0.0f));
		}

	}
}
void ComplexObject::Stand()
{
	if(currentAnimation != 0)
		ChangeCurrentAnimation(0);
}
void ComplexObject::StayAngry()
{
	if (currentAnimation != 4)
		ChangeCurrentAnimation(4);
}
void ComplexObject::ChangeViewDir()
{
	int i = rand() % 90 + 45;
	Rotate(i, glm::vec3(0.0f, 1.0f, 0.0f));
}
void ComplexObject::AddControlledObject(ComplexObject* pObj)
{
	controlledObject = pObj;
}
glm::vec3 ComplexObject::GetPosition()
{
	return position;
}