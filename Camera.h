#pragma once
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "Math3D.h"
#include "Update.h"
#include <iostream>

class Camera : public UpdateItem
{
public:
	Vector3D position;
	Vector3D movement;
	Vector3D angle;
	GLfloat growth;
	GLfloat speed;
	GLfloat angleSpeed;
	static bool keyboardKeys[];
	Camera(Vector3D startPosotion)
	{
		growth = 2;
		position = startPosotion;
		angle = { 90,0,0 };
		speed = 0.1f;
		angleSpeed = 3.5f;
	}
	void Update()
	{
		movement = { 0,0,0 };
		if (keyboardKeys[GLFW_KEY_Q])
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
		}
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
			movement.z++;
		}
		if (keyboardKeys[GLFW_KEY_X])
		{
			movement.z--;
		}
		//Normalize(movement); Нужна проверка на 0
		//movement *= speed * 0.016;
		position += movement;
		//std::cout << position.x << " " << position.y << std::endl;
	}
};