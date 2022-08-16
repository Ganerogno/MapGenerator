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
	Camera(bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed, GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage, GLFWwindow* glWindow)
		: Alive(gravInfluence, obHight, obStartPosition, obColor, obStartAngle, obSpeed, obAngleSpeed, obHealthPoint, obDamage)
	{
		angle = { 90, 0, obStartAngle };
		window = glWindow;
		baze = last = { 500,500 };
		glfwSetCursorPos(window, baze.x, baze.y);
		cursorUpdate= false;
		sensitivity = 0.5;
	}
	Vector2D GetBazeCoordinate()
	{
		return baze;
	}
	void SetBazeCoordinate()
	{
		last.x = baze.x;
		last.y = baze.y;
	}
	bool GetCursorUpdate()
	{
		return cursorUpdate;
	}
	void SetCursorUpdate(bool flag)
	{
		cursorUpdate = flag;
	}
	void Rotate()
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		x -= last.x;
		y -= last.y;
		y = -y;
		angle.z += x * sensitivity;
		angle.x += y * sensitivity;
		if (angle.x < 0)
			angle.x = 0;
		if (angle.x > 180)
			angle.x = 180;
		last.x += x;
		last.y -= y;
		if (last.x > 900 || last.x < 100)
			cursorUpdate = true;
		if (last.y > 900 || last.y < 100)
			cursorUpdate = true;
		if (cursorUpdate)
		{
			while (cursorUpdate)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			last.x = baze.x;
			last.y = baze.y;
		}
		
		//if(last.x)
		/*x -= last.x;
		y -= last.y;
		y = -y;
		angle.z += x;
		angle.x += y;
		/*last.x += x;
		last.y -= y;
		//mouseCallBack(window, baze.x, baze.y);
		/*if (keyboardKeys[GLFW_KEY_Q])
		{
			angle.z -= angleSpeed;
			if (angle.z < -180)
				angle.z += 360;
		}
		if (keyboardKeys[GLFW_KEY_E])
		{
			angle.z += angleSpeed;
			if (angle.z > 180)
				angle.z += -360;
		}
		if (keyboardKeys[GLFW_KEY_F])
		{
			angle.x -= angleSpeed;
			if (angle.x < -180)
				angle.x += 360;
		}
		if (keyboardKeys[GLFW_KEY_R])
		{
			angle.x += angleSpeed;
			if (angle.x > 180)
				angle.x += -360;
		}*/
	}
	void CreateMovement() override
	{
		movement = { 0,0,0 };
		Rotate();
		if (!jumping)
		{
			if (keyboardKeys[GLFW_KEY_W])
			{
				movement.x += sin(angle.z / 180 * M_PI);
				movement.y += cos(angle.z / 180 * M_PI);
			}
			if (keyboardKeys[GLFW_KEY_A])
			{
				movement.x -= sin(angle.z / 180 * M_PI + M_PI / 2);
				movement.y += cos(-angle.z / 180 * M_PI + M_PI / 2);
			}
			if (keyboardKeys[GLFW_KEY_S])
			{
				movement.x -= sin(angle.z / 180 * M_PI);
				movement.y -= cos(angle.z / 180 * M_PI);
			}
			if (keyboardKeys[GLFW_KEY_D])
			{
				movement.x += sin(angle.z / 180 * M_PI + M_PI / 2);
				movement.y -= cos(-angle.z / 180 * M_PI + M_PI / 2);
			}
			if (keyboardKeys[GLFW_KEY_SPACE])
			{
				if (gravitationInfluence)
				{
					currentForce = movement;
					currentForce *= 100;
					currentForce.z += jumpForce;
					jumping = true;
				}
				else
				{
					movement.z++;
				}
			}
		}
		if (keyboardKeys[GLFW_KEY_X])
		{
			movement.z--;
		}
		//Normalize(movement);
		//movement *= speed * 0.016;
		//position += movement;
		//std::cout << position.x << " " << position.y << std::endl;
	}
	void CheckAttack() override
	{

	}
	void Die() override
	{

	}
	void SetWavesTimer(int time)
	{
		wavesTimer = time;
	}
	int GetWavesTimer()
	{
		return wavesTimer;
	}
};