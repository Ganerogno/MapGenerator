#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include "Button.h"
#include "Menu.h"
#include "UI.h"
#include "Update.h"


static double FramesPerSecond = 60;
std::chrono::steady_clock::duration Updater::deltaTime = std::chrono::milliseconds(16);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
bool Setting(GLFWwindow* &window)
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
    glOrtho(-1, 1, -1, 1, 1, -1);
    glFrustum(-1, 1, -1, 1, 1, 10);
}
void Draw(GLFWwindow* window, Render render)
{
    glPushMatrix();
    //glRotatef(-20, 1, 0, 0);
    glTranslatef(0, 0, -3);
    render.Draw();
    glfwSwapBuffers(window);
    glPopMatrix();
}
int main(void)
{
    bool drawMenu = true;
    bool canUpdate = true;
    std::chrono::steady_clock::time_point startTime;
    GLFWwindow* window = nullptr;
    if (!Setting(window))
        return -1;
    Button buttons[5]{};
    buttons[0].Colored({ 0.2f,0.5f,0.1f }, { 0.5f,0.1f,0.5f }, { 0.1f,0.1f,0.1f });

    GLfloat polygon1[15]{ 0.0f, 0.0f, 0.0f,  0.2f,0.2f, 0.0f,  0.4f,0.0f,0.0f, 0.4f,-0.3f, 0.0f, 0.0f,-0.3f, 0.0f };
    Decoration decor({ -0.2f,0.1f,0 }, { 1,1,1 }, polygon1, 15);
    
    Updater updater;
    updater.Add(&decor);
    Render render;
    Menu startMenu(buttons, 5, &decor);
    render.Add(&startMenu);
    startMenu.Colored({ 0.3f,0.3f,0.3f }, { 0.8f,0.1f,0.5f }, { 0.5f,0.5f,0.1f }, { 0.1f,0.1f,0.1f });
    std::thread updateThread([&canUpdate, &updater] {
        while (canUpdate)
        {
            updater.startTime = std::chrono::steady_clock::now();
            updater.Update();
            std::this_thread::sleep_until(updater.startTime + Updater::deltaTime);
        }
        });
    updateThread.detach();
    while (!glfwWindowShouldClose(window))
    {
        startTime = std::chrono::steady_clock::now();

        Draw(window, render);
        glfwPollEvents();
        std::this_thread::sleep_until(startTime + Updater::deltaTime);
    }
    canUpdate = false;
    glfwTerminate();
    return 0;
}