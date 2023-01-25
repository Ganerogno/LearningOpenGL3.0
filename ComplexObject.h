#pragma once
#include <cstdlib>
#include "GLObject.h"
#include "skinnedmesh.h"
#include <glm/gtx/rotate_vector.hpp>

class ComplexObject :
    public GLObject
{
protected:
	ComplexObject* controlledObject;
	std::vector<SkinnedMesh*> animations;
	GLuint currentAnimation;
	double currentTime;
	float coeff;
	glm::vec3 viewDir;
	glm::vec3 position = glm::vec3(1.0f);
	float speed;
public:

	void MoveFront();
	void Draw() override;
	ComplexObject(Shader& oShader, glm::mat4x4 oMatrix, float size, float cSpeed);
	void ChangeCurrentAnimation(GLuint i);
	void AddAnimation(SkinnedMesh& mesh);
	void Translate(glm::vec3 pos) override;
	void Rotate(float angle, glm::vec3 pos) override;
	void Move();
	void Stand();
	void StayAngry();
	void AddControlledObject(ComplexObject* pObj);
	glm::vec3 GetPosition();
	void ChangeViewDir();
};

