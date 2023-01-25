#include "GLObject.h"


void HaveNormals::InitBuffer(GLuint &NBO)
{
	glGenBuffers(1, &NBO);
}
void HaveNormals::GenNormals(std::vector<GLfloat> vertexes, std::vector<GLfloat>& normals, std::vector<GLuint> indexes, GLuint NBO)
{
	normals.resize(vertexes.size());
	for (int i = 0; i < indexes.size(); i += 6)
	{
		glm::vec3 tempVec = glm::triangleNormal(
			glm::vec3(vertexes[indexes[i] * 3], vertexes[indexes[i] * 3 + 1], vertexes[indexes[i] * 3 + 2]),
			glm::vec3(vertexes[indexes[i + 1] * 3], vertexes[indexes[i + 1] * 3 + 1], vertexes[indexes[i + 1] * 3 + 2]),
			glm::vec3(vertexes[indexes[i + 2] * 3], vertexes[indexes[i + 2] * 3 + 1], vertexes[indexes[i + 2] * 3 + 2]));
		normals[indexes[i] * 3] += tempVec.x;
		normals[indexes[i] * 3 + 1] += tempVec.y;
		normals[indexes[i] * 3 + 2] += tempVec.z;

		normals[indexes[i + 1] * 3] += tempVec.x;
		normals[indexes[i + 1] * 3 + 1] += tempVec.y;
		normals[indexes[i + 1] * 3 + 2] += tempVec.z;

		normals[indexes[i + 2] * 3] += tempVec.x;
		normals[indexes[i + 2] * 3 + 1] += tempVec.y;
		normals[indexes[i + 2] * 3 + 2] += tempVec.z;

		normals[indexes[i + 5] * 3] += tempVec.x;
		normals[indexes[i + 5] * 3 + 1] += tempVec.y;
		normals[indexes[i + 5] * 3 + 2] += tempVec.z;

	}
	for (int i = 0; i < normals.size(); i +=3)
	{
		glm::vec3 tempVec = glm::normalize(glm::vec3(normals[i], normals[i + 1], normals[i + 2]));
		normals[i] = tempVec.x;
		normals[i + 1] = tempVec.y;
		normals[i + 2] = tempVec.z;
	}
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	glDisableVertexAttribArray(1);
}
void HaveNormals::EnableAttribute()
{
	glEnableVertexAttribArray(1);
}
void HaveNormals::DisableAttribute()
{
	glDisableVertexAttribArray(1);
}
void CentrallNormals::GenNormals(std::vector<GLfloat> vertexes, std::vector<GLfloat>& normals, std::vector<GLuint> indexes, GLuint NBO)
{
	for (int i = 0; i < vertexes.size(); i += 3)
	{
		glm::vec3 tempVec = glm::normalize(glm::vec3(vertexes[i], vertexes[i + 1], vertexes[i + 2]));
		normals.push_back(tempVec.x);
		normals.push_back(tempVec.y);
		normals.push_back(tempVec.z);
	}
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	glDisableVertexAttribArray(1);
}
void Body::InitBuffer(GLuint& VBO, GLuint& VAO, GLuint& EBO)
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
}

Plank::Plank(GLfloat oWidth, GLfloat oHeight)
{
	size = glm::vec3(oWidth, oHeight, 0);
}
void Plank::CreateBody(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes)
{
	vertexes.push_back(-size.x / 2);
	vertexes.push_back(-size.y / 2);
	vertexes.push_back(0);

	vertexes.push_back(size.x / 2);
	vertexes.push_back(-size.y / 2);
	vertexes.push_back(0);

	vertexes.push_back(size.x / 2);
	vertexes.push_back(size.y / 2);
	vertexes.push_back(0);

	vertexes.push_back(-size.x / 2);
	vertexes.push_back(size.y / 2);
	vertexes.push_back(0);

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(0);
	indexes.push_back(3);
}

Cube::Cube(GLfloat oWidth, GLfloat oHeight, GLfloat oLength)
{
	size = glm::vec3(oWidth, oHeight, oLength);
}
void Cube::CreateBody(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes)
{
	vertexes.push_back(-size.x / 2);
	vertexes.push_back(-size.y / 2);
	vertexes.push_back(-size.z / 2);

	vertexes.push_back(size.x / 2);
	vertexes.push_back(-size.y / 2);
	vertexes.push_back(-size.z / 2);

	vertexes.push_back(size.x / 2);
	vertexes.push_back(size.y / 2);
	vertexes.push_back(-size.z / 2);

	vertexes.push_back(-size.x / 2);
	vertexes.push_back(size.y / 2);
	vertexes.push_back(-size.z / 2);

	vertexes.push_back(-size.x / 2);
	vertexes.push_back(-size.y / 2);
	vertexes.push_back(size.z / 2);

	vertexes.push_back(size.x / 2);
	vertexes.push_back(-size.y / 2);
	vertexes.push_back(size.z / 2);

	vertexes.push_back(size.x / 2);
	vertexes.push_back(size.y / 2);
	vertexes.push_back(size.z / 2);

	vertexes.push_back(-size.x / 2);
	vertexes.push_back(size.y / 2);
	vertexes.push_back(size.z / 2);

	indexes.push_back(1);
	indexes.push_back(0);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(0);
	indexes.push_back(3);
	
	indexes.push_back(5);
	indexes.push_back(6);
	indexes.push_back(4);
	indexes.push_back(4);
	indexes.push_back(6);
	indexes.push_back(7);
	////
	indexes.push_back(0);
	indexes.push_back(4); 
	indexes.push_back(3);
	indexes.push_back(3);
	indexes.push_back(4);
	indexes.push_back(7);
	////
	indexes.push_back(1);
	indexes.push_back(2); 
	indexes.push_back(5);
	indexes.push_back(5);
	indexes.push_back(2);
	indexes.push_back(6);
	//////
	//////
	indexes.push_back(1);
	indexes.push_back(5);
	indexes.push_back(0);
	indexes.push_back(0);
	indexes.push_back(5);
	indexes.push_back(4);
	
	indexes.push_back(3);
	indexes.push_back(7);
	indexes.push_back(2);
	indexes.push_back(2);
	indexes.push_back(7);
	indexes.push_back(6);
}
Sphere::Sphere(GLfloat oSize, GLfloat horizontalSections, GLfloat verticalSections)
{
	size = glm::vec3(oSize, oSize, oSize);
	hSections = horizontalSections;
	vSections = verticalSections;
}
void Sphere::CreateBody(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes)
{
	for (int i = 0; i <= hSections; i++)
	{
		for (int j = 0; j <= vSections; j++)
		{
			vertexes.push_back(size.x / 2 * sin(M_PI * j / vSections) * cos( 2 *M_PI * i / hSections));
			vertexes.push_back(size.y / 2 * sin(M_PI * j / vSections) * sin( 2 *M_PI * i / hSections));
			vertexes.push_back(size.z / 2 * cos(M_PI * j / vSections));
		}
	}


	//for (int j = 1; j < vSections; j++)
	//{
	//	indexes.push_back(0);
	//	indexes.push_back(j);
	//	indexes.push_back(j + 1);
	//}
	//indexes.push_back(0);
	//indexes.push_back(vSections + 1);
	//indexes.push_back(1);
	for (int i = 0; i < hSections; i++)
	{
		for (int j = 0; j < vSections; j++)
		{
			indexes.push_back(i * (hSections + 1) + j + 1);
			indexes.push_back((i + 1) * (hSections + 1) + j + 1);
			indexes.push_back(i * (hSections + 1) + j);
			indexes.push_back(i * (hSections + 1) + j);
			indexes.push_back((i + 1) * (hSections + 1) + j + 1);
			indexes.push_back((i + 1) * (hSections + 1) + j);
		}
	}

}
Cylinder::Cylinder(GLfloat oWidth, GLfloat oHeight, GLfloat verticalSections)
{
	size = glm::vec3(oWidth, oHeight, oWidth);
	vSections = verticalSections;
}
void Cylinder::CreateBody(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes)
{
	vertexes.push_back(0);
	vertexes.push_back(size.y / 2);
	vertexes.push_back(0);
	for (int i = 0; i < vSections; i++)
	{
		vertexes.push_back(size.x / 2 * cos(2 * M_PI * i / vSections));
		vertexes.push_back(size.y / 2);
		vertexes.push_back(size.z / 2 * sin(2 * M_PI * i / vSections));
	}
	vertexes.push_back(0);
	vertexes.push_back(-size.y / 2);
	vertexes.push_back(0);
	for (int i = 0; i < vSections; i++)
	{
		vertexes.push_back(size.x / 2 * cos(2 * M_PI * i / vSections));
		vertexes.push_back(-size.y / 2);
		vertexes.push_back(size.z / 2 * sin(2 * M_PI * i / vSections));
	}

	for (int i = 1; i < vSections; i++)
	{
		indexes.push_back(0);
		indexes.push_back(i + 1);
		indexes.push_back(i);
	}
	
	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(vSections);
	
	for (int i = vSections + 2; i < 2 * vSections + 1; i++)
	{
		indexes.push_back(vSections + 1);
		indexes.push_back(i);
		indexes.push_back(i + 1);
	}
	
	indexes.push_back(vSections + 1);
	indexes.push_back(2 * vSections + 1);
	indexes.push_back(vSections + 2);

	for (int i = 1; i < vSections; i++)
	{
		indexes.push_back(i);
		indexes.push_back(i + 1);
		indexes.push_back(i + 1 + vSections);
		indexes.push_back(i + 1 + vSections);
		indexes.push_back(i + 1);
		indexes.push_back(i + 2 + vSections);
	}
	indexes.push_back(1);
	indexes.push_back(vSections);
	indexes.push_back(vSections + 2);
	indexes.push_back(vSections + 2);
	indexes.push_back(2 * vSections + 1);
	indexes.push_back(vSections);
	//for (int i = vSections + 2; i < 2 * vSections + 2; i++)
	//{
	//	indexes.push_back(vSections + 1);
	//	indexes.push_back(i);
	//	indexes.push_back(i + 1);
	//}
	//indexes.push_back(vSections + 1);
	//indexes.push_back(2 * vSections + 2);
	//indexes.push_back(vSections + 2);
	//
	//for (int i = 1; i < vSections + 1; i++)
	//{
	//	indexes.push_back(i);
	//	indexes.push_back(i + 1);
	//	indexes.push_back(i + vSections + 1);
	//	indexes.push_back(i + vSections + 1);
	//	indexes.push_back(i + 1);
	//	indexes.push_back(i + vSections + 2);
	//}
}

Cone::Cone(GLfloat oWidth, GLfloat oHeight, GLfloat verticalSections)
{
	size = glm::vec3(oWidth, oHeight, oWidth);
	vSections = verticalSections;
}
void Cone::CreateBody(std::vector<GLfloat>& vertexes, std::vector<GLuint>& indexes)
{
	vertexes.push_back(0);
	vertexes.push_back(-size.y / 2);
	vertexes.push_back(0);
	for (int i = 0; i < vSections; i++)
	{
		vertexes.push_back(size.x / 2 * cos(2 * M_PI * i / vSections));
		vertexes.push_back(-size.y / 2);
		vertexes.push_back(size.z / 2 * sin(2 * M_PI * i / vSections));
	}
	vertexes.push_back(0);
	vertexes.push_back(size.y / 2);
	vertexes.push_back(0);

	for (int i = 1; i < vSections; i++)
	{
		indexes.push_back(0);
		indexes.push_back(i + 1);
		indexes.push_back(i);
	}

	indexes.push_back(0);
	indexes.push_back(1);
	indexes.push_back(vSections);

	for (int i = 1; i < vSections; i++)
	{
		indexes.push_back(vSections + 1);
		indexes.push_back(i + 1);
		indexes.push_back(i);
	}

	indexes.push_back(vSections + 1);
	indexes.push_back(vSections);
	indexes.push_back(1);

	for (int i = 1; i < vSections; i++)
	{
		indexes.push_back(i);
		indexes.push_back(i + 1);
		indexes.push_back(i + 1 + vSections);
		indexes.push_back(i + 1 + vSections);
		indexes.push_back(i + 1);
		indexes.push_back(i + 2 + vSections);
	}
	indexes.push_back(1);
	indexes.push_back(vSections);
	indexes.push_back(vSections + 2);
	indexes.push_back(vSections + 2);
	indexes.push_back(2 * vSections + 1);
	indexes.push_back(vSections);
	//for (int i = vSections + 2; i < 2 * vSections + 2; i++)
	//{
	//	indexes.push_back(vSections + 1);
	//	indexes.push_back(i);
	//	indexes.push_back(i + 1);
	//}
	//indexes.push_back(vSections + 1);
	//indexes.push_back(2 * vSections + 2);
	//indexes.push_back(vSections + 2);
	//
	//for (int i = 1; i < vSections + 1; i++)
	//{
	//	indexes.push_back(i);
	//	indexes.push_back(i + 1);
	//	indexes.push_back(i + vSections + 1);
	//	indexes.push_back(i + vSections + 1);
	//	indexes.push_back(i + 1);
	//	indexes.push_back(i + vSections + 2);
	//}
}
GLObject::GLObject(Shader& oShader, glm::mat4x4 oMatrix) : shader(oShader), modelMatrix(oMatrix)
{

}

void GLObject::Translate(glm::vec3 pos)
{
	modelMatrix = glm::translate(modelMatrix, pos);
}
void GLObject::Rotate(GLfloat angle, glm::vec3 vec)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), vec);
}
void GLObject::Scale(glm::vec3 scale)
{
	modelMatrix = glm::scale(modelMatrix, scale);
}

SimpleObject::SimpleObject(Shader& oShader, glm::mat4x4 oMatrix, Body& oBody, Normals& oNBO, glm::vec4 oColor) : GLObject(oShader, oMatrix), body(oBody), NormalsBO(oNBO), color(oColor)
{
	elementsCount = 0;
	std::vector<GLfloat> vertexes;
	std::vector<GLfloat> normals;
	std::vector<GLuint> indexes;
	body.InitBuffer(VBO, VAO, EBO);
	body.CreateBody(vertexes, indexes);
	NormalsBO.InitBuffer(NBO);
	GenBuffers(vertexes, normals, indexes);
}
void SimpleObject::SetColor(glm::vec4 oColor)
{
	color = oColor;
}
glm::vec3 SimpleObject::GetSize()
{
	return body.size;
}
void SimpleObject::GenBuffers(std::vector<GLfloat> vertexes, std::vector<GLfloat> normals, std::vector<GLuint> indexes)
{

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(GLfloat), &vertexes[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), &indexes[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

	NormalsBO.GenNormals(vertexes, normals, indexes, NBO);


	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	elementsCount = indexes.size();
}
void SimpleObject::Draw()
{
	shader.Use();
	glPolygonMode(GL_FRONT, GL_LINE);
	GLint modelLoc = glGetUniformLocation(shader.GetProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	GLint viewLoc = glGetUniformLocation(shader.GetProgram(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(Camera::GetMatrix()));
	GLint projectionLoc = glGetUniformLocation(shader.GetProgram(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	GLint objColor = glGetUniformLocation(shader.GetProgram(), "objectColor");
	glUniform4fv(objColor, 1, glm::value_ptr(color));

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	NormalsBO.EnableAttribute();
	glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	NormalsBO.DisableAttribute();
	shader.UseBaseShader();
}