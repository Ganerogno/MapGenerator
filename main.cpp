#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include "Button.h"
#include "Menu.h"
#include "UI.h"
#include "Shader.h"
#include "Water.h"
#include "Update.h"
#include "Camera.h"
#include "World.h"
#include "PerlinNoise.h"
#include "Sun.h"

std::chrono::steady_clock::duration Updater::deltaTime = std::chrono::milliseconds(16);
bool Camera::keyboardKeys[91]{};
bool Menu::drawMenu = true;
const int Chunk::size = 200;
int Chunk::octaves = 4;
unsigned int PerlinNoise::seed;
int PerlinNoise::table[100]{};
GLfloat PerlinNoise::scale = 100;
GLfloat Water::hight = -3;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    //    glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        Menu::drawMenu = !Menu::drawMenu;
    }
    if (Menu::drawMenu)
    {
        if ((key == GLFW_KEY_W || key == GLFW_KEY_S) && action == GLFW_REPEAT)
        {
            Camera::keyboardKeys[key] = true;
        }
        if (key == GLFW_KEY_ENTER)
        {

        }
    }
    else
    {
        if (key <= GLFW_KEY_Z)
        {
            if(action != GLFW_RELEASE)
                Camera::keyboardKeys[key] = true;
            else
                Camera::keyboardKeys[key] = false;
        }
    }
}
bool Init(GLFWwindow* &window)
{
    if (!glfwInit())
        return false;

    window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }
    glfwSetKeyCallback(window, keyCallback);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    return true;
}
bool Setting()
{
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, -1);
    glFrustum(-1, 1, -1, 1, 1, 400);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_COLOR_MATERIAL);
    glfwSwapInterval(1);
    PerlinNoise::SetSeed(23);



    return true;
}
void Draw(GLFWwindow* window, Render render)
{
    render.Draw();
    glfwSwapBuffers(window);
}
int main(void)
{
    bool canUpdate = true;
    std::chrono::steady_clock::time_point startTime;
    GLFWwindow* window = nullptr;

    if (!Init(window))
        return -1;
    if (!Setting())
        return -1;

    Button buttons[5]{};
    buttons[0].Colored({ 0.2f,0.5f,0.1f }, { 0.5f,0.1f,0.5f }, { 0.1f,0.1f,0.1f });

    GLfloat polygon1[15]{ 0.0f, 0.0f, 0.0f,  0.2f,0.2f, 0.0f,  0.4f,0.0f,0.0f, 0.4f,-0.3f, 0.0f, 0.0f,-0.3f, 0.0f };
    Decoration decor({ -0.2f,0.1f,0 }, { 1,1,1 }, polygon1, 15);
    
    Updater updater;
    updater.Add(&decor);
    Render render;
    Menu startMenu(buttons, 5, &decor);
    startMenu.Colored({ 0.3f,0.3f,0.3f }, { 0.8f,0.1f,0.5f }, { 0.5f,0.5f,0.1f }, { 0.1f,0.1f,0.1f });

    Camera camera({ 30,30,10 });
    updater.Add(&camera);
    Shader sunShader;
    sunShader.AddShader("Sun.vert", GL_VERTEX_SHADER);
    sunShader.AddShader("Sun.frag", GL_FRAGMENT_SHADER);
    sunShader.CreateProgram();
    Sun sun(5.5, 200, Chunk::size / 2, 0, 0.5, &sunShader, { 1,1,0 }, { 5,1,0 });

    updater.Add(&sun);
    Shader waterShader;
    waterShader.AddShader("Water.vert", GL_VERTEX_SHADER);
    waterShader.AddShader("Water.frag", GL_FRAGMENT_SHADER);
    waterShader.CreateProgram();
    Water water(Chunk::size, 2, &waterShader, &camera);
    updater.Add(&water);
    World world(&camera, &water, &sun);


    render.Add(&startMenu);
    render.Add(&world);
    world.StopRender();
    std::thread updateThread([&canUpdate, &updater] {
        while (canUpdate)
        {
            updater.startTime = std::chrono::steady_clock::now();
            updater.Update();
            std::this_thread::sleep_until(updater.startTime + Updater::deltaTime);
        }
        });
    updateThread.detach();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    while (!glfwWindowShouldClose(window))
    {
        startTime = std::chrono::steady_clock::now();
        if (!Menu::drawMenu && startMenu.GetCanRender())
        {
            glDepthMask(GL_LESS);
            startMenu.StopRender();
            world.ContinueRender();
        }
        if (Menu::drawMenu && !startMenu.GetCanRender())
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            glDepthMask(GL_FALSE);
            startMenu.ContinueRender();
            world.StopRender();
        }

        Draw(window, render);
        glfwPollEvents();
        std::this_thread::sleep_until(startTime + Updater::deltaTime);
    }
    canUpdate = false;
    glfwTerminate();
    return 0;
}