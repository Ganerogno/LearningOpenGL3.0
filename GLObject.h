#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Shader.h"
#include "Camera.h"

struct Normals
{
	virtual void InitBuffer(GLuint &NBO) = 0;
	virtual void GenNormals(std::vector<GLfloat> vertexes, std::vector<GLfloat>& normals, std::vector<GLuint> indexes, GLuint NBO) = 0;
	virtual void EnableAttribute() = 0;
	virtual void DisableAttribute() = 0;
};
struct NoNormals : public Normals
{
	void InitBuffer(GLuint &NBO) override {};
	void GenNormals(std::vector<GLfloat> vertexes, std::vector<GLfloat>& normals, std::vector<GLuint> indexes, GLuint NBO) override {};
	void EnableAttribute() override {};
	void DisableAttribute() override {};
};
struct HaveNormals : public Normals
{
	void InitBuffer(GLuint &NBO) override;
	virtual void GenNormals(std::vector<GLfloat> vertexes, std::vector<GLfloat>& normals, std::vector<GLuint> indexes, GLuint NBO) override;
	void EnableAttribute() override;
	void DisableAttribute() override;
};
struct CentrallNormals : public HaveNormals
{
	void GenNormals(std::vector<GLfloat> vertexes, std::vector<GLfloat>& normals, std::vector<GLuint> indexes, GLuint NBO) override;
};

struct Body
{
	glm::vec3 size;
	void InitBuffer(GLuint &VBO, GLuint &VAO, GLuint &EBO);
	virtual void CreateBody(std::vector<GLfloat> &vertexes, std::vector<GLuint> &indexes) = 0;
};
struct Plank : public Body
{
	Plank(GLfloat oWidth, GLfloat oHeight);
	void CreateBody(std::vector<GLfloat> &vertexes, std::vector<GLuint> &indexes) override;
};

struct Cube : public Body
{
	Cube(GLfloat oWidth, GLfloat oHeight, GLfloat oLength);
	void CreateBody(std::vector<GLfloat> &vertexes, std::vector<GLuint> &indexes) override;
};

struct Sphere : public Body
{
	GLfloat hSections;
	GLfloat vSections;
	Sphere(GLfloat oSize, GLfloat horizontalSections, GLfloat verticalSections);
	void CreateBody(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes) override;
};

struct Cylinder : public Body
{
	GLfloat vSections;
	Cylinder(GLfloat oWidth, GLfloat oHeight, GLfloat verticalSections);
	void CreateBody(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes) override;
};

struct Cone : public Body
{
	GLfloat vSections;
	Cone(GLfloat oWidth, GLfloat oHeight, GLfloat verticalSections);
	void CreateBody(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes) override;
};
class GLObject
{
protected:


	glm::mat4x4 modelMatrix;
	//std::vector<GLObject*> objects;
	Shader& shader;
public:

	static glm::mat4x4 ProjectionMatrix;

	GLObject(Shader& oShader, glm::mat4x4 oMatrix);
	virtual void Draw() = 0;
	virtual void Translate(glm::vec3 pos);
	virtual void Rotate(GLfloat angle, glm::vec3 vec);
	void Scale(glm::vec3 scale);
};

class SimpleObject : public GLObject
{
	GLuint NBO;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	glm::vec4 color;
	Normals& NormalsBO;
	Body& body;
	int elementsCount;
public:
	SimpleObject(Shader& oShader, glm::mat4x4 oMatrix, Body& oBody, Normals& oNBO, glm::vec4 oColor = glm::vec4(1.0f));

	void SetColor(glm::vec4 oColor);
	glm::vec3 GetSize();
	void Draw() override;
protected:
	void GenBuffers(std::vector<GLfloat> vertexes, std::vector<GLfloat> normals, std::vector<GLuint> indexes);
};