#include "Scene.h"


Scene::Scene(Shader &sShader, Camera& sCamera) : camera(sCamera)
{
	glGenBuffers(1, &lights);
	shader = &sShader;
}
void Scene::AddObject(GLObject& object)
{
	objects.push_back(&object);
}
void Scene::AddLight(SimpleObject&light, glm::vec3 pos, glm::vec3 color)
{
	lightPositions.push_back(pos);
	lightColors.push_back(color);
	light.Translate(pos);
	light.SetColor(glm::vec4(color,1.0f));
	AddObject(light);
}
void Scene::GenerateLightsBuffer()
{
	glBindBuffer(GL_UNIFORM_BUFFER, lights);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(int) + lightPositions.size() * sizeof(glm::vec4) + lightColors.size() * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}
void Scene::UseLights()
{
	size_t count = glGetUniformLocation(shader->GetProgram(), "count");
	glUniform1i(count, lightColors.size());
	size_t colors = glGetUniformLocation(shader->GetProgram(), "lightColors");
	glUniform3fv(colors, lightColors.size(), glm::value_ptr(lightColors[0]));
	size_t pos = glGetUniformLocation(shader->GetProgram(), "lightPositions");
	glUniform3fv(pos, lightColors.size(), glm::value_ptr(lightPositions[0]));
	GLint viewPosLoc = glGetUniformLocation(shader->GetProgram(), "viewPosition");
	glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
}
//	GLint modelLoc = glGetUniformLocation(shader->GetProgram(), "lightColors");
//	glUniform4fv(modelLoc, 2, glm::value_ptr(lightColors[0]));
/*
	glBindBuffer(GL_UNIFORM_BUFFER, lights);
	unsigned uniformBlock = glGetUniformBlockIndex(shader->GetProgram(),"lights");
	glUniformBlockBinding(shader->GetProgram(), uniformBlock, 0);
	int a = lightPositions.size();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(int), &a);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(int), 1 * sizeof(glm::vec4), glm::value_ptr(lightPositions[0]));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(int) + 1 * sizeof(glm::vec4), 1 * sizeof(glm::vec4), glm::value_ptr(lightColors[0]));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
*/
void Scene::Draw()
{
	shader->Use();
	UseLights();
	for (GLObject* i : objects)
	{
		i->Draw();
	}
	Shader::UseBaseShader();
}