#include <GLFW/glfw3.h>
#include "Button.h"
#include "Menu.h"
#include "UI.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
    // и приложение после этого закроется
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
}
int main(void)
{
    bool drawMenu = true;
    GLFWwindow* window = nullptr;
    if (!Setting(window))
        return -1;
    Button buttons[5]{};
    buttons[0].Colored({ 0.2f,0.5f,0.1f }, { 0.5f,0.1f,0.5f }, { 0.1f,0.1f,0.1f });

    GLfloat polygon1[15]{ 0.0f, 0.0f, 0.0f,  0.2f,0.2f, 0.0f,  0.4f,0.0f,0.0f, 0.4f,-0.3f, 0.0f, 0.0f,-0.3f, 0.0f };
    Decoration decor({ 0.1f,0.2f,0 }, { 1,1,1 }, polygon1, 15);

    Menu startMenu(buttons, 5, &decor);
    startMenu.Colored({ 0.3f,0.3f,0.3f }, { 0.8f,0.1f,0.5f }, { 0.5f,0.5f,0.1f }, { 0.1f,0.1f,0.1f });
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        if (drawMenu)
        {
            startMenu.Draw();
        }
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}