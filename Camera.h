#pragma once
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <thread>
#include <chrono>
#include "Math3D.h"
#include "Alive.h"
#include <iostream>


class Camera : public Alive
{
	GLFWwindow* window;
	Vector2D baze;
	Vector2D last;
	GLfloat sensitivity;
	bool cursorUpdate;
	int wavesTimer;
public:
	static std::chrono::steady_clock::duration attackDeltaTime;
	Vector3D angle;
	static bool keyboardKeys[];
	static bool leftMouseButton;
	static bool dead;
	Camera(bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed, GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage, GLFWwindow* glWindow);
	Vector2D GetBazeCoordinate();
	void SetBazeCoordinate();
	bool GetCursorUpdate();
	void SetCursorUpdate(bool flag);
	void Rotate();
	void CreateMovement() override;
	void CheckAttack() override;
	void Die() override;
	void SetWavesTimer(int time);
	int GetWavesTimer();
	Vector3D GetPosition();
};