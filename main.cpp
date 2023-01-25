#include <iostream>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "Camera.h"
#include "Scene.h"

glm::mat4x4 GLObject::ProjectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
glm::mat4x4 Camera::ViewMatrix = glm::mat4x4(1.0f);
bool Camera::keys[91]{};
glm::vec3 Camera::cameraDir = glm::vec3();
GLfloat Camera::yaw = -90.0f;
GLfloat Camera::pitch = 0.0f;
GLfloat Camera::lastX = 400;
GLfloat Camera::lastY = 400;
bool Camera::firstTest = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key <= GLFW_KEY_Z)
    {
        if (action != GLFW_RELEASE)
        {
            Camera::keys[key] = true;
        }
        else
        {
            Camera::keys[key] = false;
        }
    }

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera::MoveMouse(window, xpos, ypos);
}
GLFWwindow* Init()
{
    GLFWwindow* window;

    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, mouse_callback);
    glfwSetWindowPos(window, 400, 100);
    glfwSetCursorPos(window, 400, 400);

    glEnable(GL_DEPTH_TEST);

    return window;
}
int main(int argc, char* argv[])
{

    GLFWwindow* window = Init();
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    Shader testShader((std::string)"Shaders/TestShader", true, true);
    Shader lightShader((std::string)"Shaders/LightShader", true, true);
    Shader modelShader((std::string)"Shaders/ModelShader", true, true);

    HaveNormals NBO;
    NoNormals NONBO;
    CentrallNormals CentNBO;

    Plank plank(40, 40);
    //Plank plank1(1, 1, shader, NBO, glm::rotate(glm::mat4x4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec4(1.0f, .5f, 0.0f, 1.0f));
    Cube cube(1, 1, 1);
    Sphere sphere(1.0f, 21, 21);
    Cylinder cylinder(1.0f, 1.0f, 40);
    Cone cone(1.0f, 1.0f, 20);
    Cone treeCone(2.0f, 2.0f, 20);




    SimpleObject floor(testShader, glm::mat4x4(1.0f), plank, NBO, glm::vec4(0.4f, 0.8f, 0.4f, 1.0f));
    SimpleObject wall1(testShader, glm::mat4x4(1.0f), plank, NBO, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    SimpleObject wall2(testShader, glm::mat4x4(1.0f), plank, NBO, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    SimpleObject wall3(testShader, glm::mat4x4(1.0f), plank, NBO, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    SimpleObject wall4(testShader, glm::mat4x4(1.0f), plank, NBO, glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

    wall1.Translate(glm::vec3(15.0f, 0.0f, 0.0f));
    wall2.Translate(glm::vec3(-15.0f, 0.0f, 0.0f));
    wall3.Translate(glm::vec3(0.0f, 0.0f, 15.0f));
    wall4.Translate(glm::vec3(0.0f, 0.0f, -15.0f));

    floor.Rotate(90, glm::vec3(-1.0f, 0.0f, 0.0f));
    wall1.Rotate(90, glm::vec3(0.0f, -1.0f, 0.0f));
    wall2.Rotate(90, glm::vec3(0.0f, 1.0f, 0.0f));
    wall3.Rotate(180, glm::vec3(0.0f, 1.0f, 0.0f));

    SimpleObject tree1(testShader, glm::mat4x4(1.0f), treeCone, CentNBO, glm::vec4(0.2f, 0.9f, 0.1f, 1.0f));
    SimpleObject tree2(testShader, glm::mat4x4(1.0f), treeCone, CentNBO, glm::vec4(0.3f, 0.9f, 0.1f, 1.0f));
    SimpleObject decoration1(testShader, glm::mat4x4(1.0f), cylinder, CentNBO, glm::vec4(0.9f, 0.9f, 0.1f, 1.0f));
    SimpleObject cube1(testShader, glm::mat4x4(1.0f), cube, CentNBO, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    SimpleObject cube2(testShader, glm::mat4x4(1.0f), cube, CentNBO, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    SimpleObject cube3(testShader, glm::mat4x4(1.0f), cube, CentNBO, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

    tree1.Translate(glm::vec3(-10.0f, 2.0f, -10.0f));
    tree2.Translate(glm::vec3(-10.0f, 1.0f, -10.0f));
    tree1.Scale(glm::vec3(0.8f, 0.8f, 0.8f));

    cube1.Translate(glm::vec3(0.0f, 0.5f, -7.0f));
    cube2.Translate(glm::vec3(0.0f, 1.5f, -7.0f));
    cube3.Translate(glm::vec3(0.0f, 2.5f, -7.0f));

    decoration1.Translate(glm::vec3(3.0f, 0.5f, -7.0f));


    SimpleObject testlight1(lightShader, glm::mat4x4(1.0f), cube, NONBO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    SimpleObject testlight2(lightShader, glm::mat4x4(1.0f), sphere, NONBO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    SimpleObject testlight3(lightShader, glm::mat4x4(1.0f), cone, NONBO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    Camera camera({ 5.0f,2.0f,0.0f }, { 0.0f,0.0f,-1.0f });
    Scene scene(testShader, camera);

    scene.AddObject(floor);
    scene.AddObject(wall1);
    scene.AddObject(wall2);
    scene.AddObject(wall3);
    scene.AddObject(wall4);
    scene.AddLight(testlight1, glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    scene.AddLight(testlight2, glm::vec3(10.0f, 3.0f, -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scene.AddLight(testlight3, glm::vec3(-10.0f, 3.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    scene.AddObject(tree1);
    scene.AddObject(tree2);
    scene.AddObject(cube1);
    scene.AddObject(cube2);
    scene.AddObject(cube3);
    scene.AddObject(decoration1);


    ComplexObject people1(modelShader, glm::mat4(1.0f), 0.002, 0.02);
    ComplexObject people2(modelShader, glm::mat4(1.0f), 0.002, 0.02);
    ComplexObject people3(modelShader, glm::mat4(1.0f), 0.002, 0.02);
    ComplexObject character(modelShader, glm::mat4(1.0f), 0.004, 0.15);
    people1.AddControlledObject(&character);
    people2.AddControlledObject(&character);
    people3.AddControlledObject(&character);
    TextureLoader loader1;
    TextureLoader loader2;
    SkinnedMesh mesh1(loader1);
    SkinnedMesh mesh2(loader1);
    SkinnedMesh mesh3(loader1);
    SkinnedMesh mesh4(loader1);
    SkinnedMesh mesh5(loader2);
    SkinnedMesh mesh6(loader2);
    mesh1.loadMesh("Materials/Remy/Idle.dae");
    mesh2.loadMesh("Materials/Remy/Fast Run.dae");
    mesh3.loadMesh("Materials/Remy/Walking.dae");
    mesh4.loadMesh("Materials/Remy/Defeated.dae");
    mesh5.loadMesh("Materials/Gray/Idle.dae");
    mesh6.loadMesh("Materials/Gray/Fast Run.dae");

    people1.AddAnimation(mesh1);
    people1.AddAnimation(mesh2);
    people1.AddAnimation(mesh3);
    people1.AddAnimation(mesh4);
    people1.Translate(glm::vec3(-1.0f, 0.0f, 0.0f));

    people2.AddAnimation(mesh1);
    people2.AddAnimation(mesh2);
    people2.AddAnimation(mesh3);
    people2.AddAnimation(mesh4);
    people2.Translate(glm::vec3(0.0f, 0.0f, 0.0f));

    people3.AddAnimation(mesh1);
    people3.AddAnimation(mesh2);
    people3.AddAnimation(mesh3);
    people3.AddAnimation(mesh4);
    people3.Translate(glm::vec3(1.0f, 0.0f, 0.0f));

    character.AddAnimation(mesh5);
    character.AddAnimation(mesh6);
    character.Translate(glm::vec3(0.0f, 0.0f, 3.0f));
    character.Rotate(180, glm::vec3(0.0f, 1.0f, 0.0f));

    scene.AddObject(people1);
    scene.AddObject(people2);
    scene.AddObject(people3);
    scene.AddObject(character);
    people1.Rotate(135, glm::vec3(0.0f, 1.0f, 0.0f));
    people2.Rotate(90, glm::vec3(0.0f, 1.0f, 0.0f));
    people3.Rotate(45, glm::vec3(0.0f, 1.0f, 0.0f));
    //scene.AddObject(testObj1);
    //scene.AddObject(testObj2);
    // 
    // 
    //scene.AddLight(testlight3, glm::vec3(3.0f,2.0f,0.0f), glm::vec3(0.f, 1.f, 0.f));
    //testModel.Scale(glm::vec3(0.002f, 0.002f, 0.002f));
    //scene.AddLight(glm::vec3(0.0f,3.0f,0.0f), glm::vec3(0.7f, 0.7f, 0.7f));
    //SkinnedMesh mesh(modelShader, glm::mat4x4(1.0f));
    //mesh.loadMesh("Materials/Walking/Idle.dae");
    //mesh.loadMesh("Materials/Walking/Walking.dae");
    //mesh.setAnimation(0);
    scene.GenerateLightsBuffer();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera.Update();
        scene.Draw();
        character.Move();
        //people1.Move();
        //people2.Move();
        //people3.Move();
        std::this_thread::sleep_for(std::chrono::microseconds(166));
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}