#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <vector>
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
#include "EnemyWaves.h"
#include "Shape.h"
#include "Enemy.h"
#include "RenderPoint.h"
#include "Texture.h"
#include "HardUpdate.h"

std::chrono::steady_clock::duration Updater::deltaTime = std::chrono::milliseconds(16);
std::chrono::steady_clock::duration HardUpdater::deltaTime = std::chrono::milliseconds(200);
std::chrono::steady_clock::duration Camera::attackDeltaTime = std::chrono::milliseconds(100);
std::chrono::steady_clock::duration Enemy::attackDeltaTime = std::chrono::milliseconds(500);
bool Camera::keyboardKeys[91]{};
bool Camera::leftMouseButton = false;
bool Camera::dead = false;
bool Menu::drawMenu = true;
GLfloat Button::symbolWidth[256]{};
//Texture Menu::text = Texture((char*)"../Materials/Text.png");
const int Chunk::size = 200;
int Chunk::octaves = 4;
unsigned int PerlinNoise::seed;
int PerlinNoise::table[100]{};
GLfloat PerlinNoise::scale = 100;
GLfloat Water::hight = -5;
GLfloat** Chunk::coordinates = nullptr;
GLfloat Alive::gravitation = 8;
bool closeGame = false;
bool newGame = false;
bool Menu::continueGame = false;
//GLfloat Texture::textureCoordinates[8] = { 0,1, 1,1, 1,0, 0,0 };
void ContinueGame()
{
    Menu::drawMenu = false;
}
void NewGame()
{
    Menu::drawMenu = false;
    newGame = true;
    Menu::continueGame = true;
}
void CloseGame()
{
    closeGame = true;
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    //    glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        Menu::drawMenu = true;
    }
    if (key <= GLFW_KEY_Z)
    {
        if (action != GLFW_RELEASE)
            Camera::keyboardKeys[key] = true;
        else
            Camera::keyboardKeys[key] = false;
    }
}
void mouseCallback(GLFWwindow* window, int key, int action, int mode)
{
    if (key == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action != GLFW_RELEASE)
            Camera::leftMouseButton = true;
        else
            Camera::leftMouseButton = false;
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetMouseButtonCallback(window, mouseCallback);
    //glfwSetCursorPosCallback(window, mouseCallBack);
    glfwSetWindowPos(window, 40, 30);
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
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_COLOR_MATERIAL);
    glfwSwapInterval(1);
    srand(time(0));
    PerlinNoise::SetSeed(rand());
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    for (int i = 0; i < 256; i++)
    {
        Button::symbolWidth[i] = 1;
    }

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
    bool firstStart = true;
    std::chrono::steady_clock::time_point startTime;
    GLFWwindow* window = nullptr;

    if (!Init(window))
        return -1;
    if (!Setting())
        return -1;
    Texture text("Text.png");
    Button::FindSymbolWidth(&text);
    Button buttons[3]{ Button("Продолжить игру", &text, ContinueGame), Button("Новая игра", &text, NewGame) , Button("Выход", &text, CloseGame)};
    //Button buttons[1]{ Button("a", &text) };
    buttons[0].Colored({ 0.2f,0.5f,0.1f }, { 0.5f,0.1f,0.5f }, { 0.1f,1,0.1f });
    GLfloat polygon1[15]{ 0.0f, 0.0f, 0.0f,  0.2f,0.2f, 0.0f,  0.4f,0.0f,0.0f, 0.4f,-0.3f, 0.0f, 0.0f,-0.3f, 0.0f };
    Decoration decor({ -0.2f,0.1f,0 }, { 1,1,1 }, polygon1, 15);
    Updater updater;
    updater.Add(&decor);
    Render render;
    Menu startMenu(buttons, 3, &decor, window);
    updater.Add(&startMenu);
    startMenu.Colored({ 0.3f,0.3f,0.3f }, { 0.8f,0.1f,0.5f }, { 0.5f,0.5f,0.1f }, { 0.1f,0.1f,0.1f });

    Camera camera(true, 4, { 30,30,10 }, 0, 45, 100, 3.5f, 100, 20, window);
    updater.Add(&camera);
    Button timerText("0", &text);
    Button endGameText("Игра окончена", &text);
    UI ui(&camera, { 0,0,0 }, 3, &timerText, &endGameText);

    Shape shape({ 4,4,4 });
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
    RenderPoint startPoint(startRenderWorld, &world);
    RenderPoint endPoint(endRenderWorld, &world);

    render.Add(&startMenu);
    render.Add(&startPoint);
    render.Add(&world);
    render.Add(&endPoint);
    render.Add(&ui);
    render.SaveChanges();
    render.AddPoint(&startPoint, Position::world);
    world.StopRender();
    camera.StopRender();
    srand(time(0));
    std::thread updateThread([&canUpdate, &updater] {
        while (canUpdate)
        {
            updater.startTime = std::chrono::steady_clock::now();
            updater.Update();
            std::this_thread::sleep_until(updater.startTime + Updater::deltaTime);
        }
        });
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    updateThread.detach();
    HardUpdater hUpdater;
    EnemyWaves waves(&updater, &render, &camera, &shape);
    waves.StopHUpdate();
    hUpdater.Add(&waves);
    std::thread hUpdateThread([&canUpdate, &hUpdater] {
        while (canUpdate)
        {
            hUpdater.startTime = std::chrono::steady_clock::now();
            hUpdater.HUpdate();
            std::this_thread::sleep_until(hUpdater.startTime + HardUpdater::deltaTime);
        }
        });
    hUpdateThread.detach();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    int count = 1;
    while (!glfwWindowShouldClose(window))
    {
        if (newGame)
        {
            if (!firstStart)
            {
                camera.dead = false;
                camera.GetCurrentHP() = camera.GetHealthPoint();
                camera.ContinueRender();
                world.ContinueRender();
                world.ReBuild();
                waves.Restart();
            }
            firstStart = false;
        }
        newGame = false;
        startTime = std::chrono::steady_clock::now();
        if (Camera::leftMouseButton && !Menu::drawMenu)
        {
            GLubyte pixels[3]{};
            glReadPixels(500, 500, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            if (pixels[0] && !pixels[1] && !pixels[2])
            {
                if (waves.GetSize() && camera.GetAttackTime() + Camera::attackDeltaTime < std::chrono::steady_clock::now())
                {
                    waves.GetEnemy(pixels[0]).TakeDamage(camera.GetDamage());
                }
            }
        }
        if (!Menu::drawMenu && startMenu.GetCanRender())
        {
            glDepthMask(GL_LESS);
            startMenu.StopRender();
            world.ContinueRender();
            glfwSetCursorPos(window, camera.GetBazeCoordinate().x, camera.GetBazeCoordinate().y);
            camera.SetBazeCoordinate();
            camera.ContinueRender();
            waves.ContinueHUpdate();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
        if (Menu::drawMenu && !startMenu.GetCanRender())
        {
            glClear(GL_DEPTH_BUFFER_BIT);
            glDepthMask(GL_FALSE);
            startMenu.ContinueRender();
            world.StopRender();
            camera.StopRender();
            waves.StopHUpdate();
            glfwSetCursorPos(window, camera.GetBazeCoordinate().x, camera.GetBazeCoordinate().y);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        if (camera.GetCursorUpdate())
        {
            while (!camera.GetCursorUpdate())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            glfwSetCursorPos(window, camera.GetBazeCoordinate().x, camera.GetBazeCoordinate().y);
            camera.SetCursorUpdate(false);
        }
        Draw(window, render);
        glfwPollEvents();
        if (closeGame)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        if (std::chrono::steady_clock::now() < startTime + Updater::deltaTime)
        {
            std::this_thread::sleep_until(startTime + Updater::deltaTime);
        }
    }
    canUpdate = false;
    glfwTerminate();
    return 0;
}