#pragma once
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Math3D.h"
class Decoration
{
	Vector3D movement;
	Vector3D position;
	Vector3D color;
	Vector3D center;
	GLfloat angle;
	GLfloat angleSpeed;
	GLfloat* polygon;
	GLfloat speed = 0.001f;
	Vector3D rotatedVectors[5]{};
	int polygonVertexNum;
public:
	Decoration(Vector3D move, Vector3D polygonColor, GLfloat* dotsArr, int dotsNum)
	{
		movement = move;
		if (!movement.z)
			movement.z = 0;
		color = polygonColor;
		polygon = dotsArr;
		polygonVertexNum = dotsNum;
		angle = 0;
		angleSpeed = 0.005f;
	}
	Vector3D FindCenter()
	{
		Vector3D cent = { 0,0,0 };
		for (int i = 0; i < polygonVertexNum; i += 3)
		{
			cent.x += polygon[i];
			cent.y += polygon[i+1];
		}
		cent *= 3;
		cent /= polygonVertexNum;
		return cent;
	}
	void CollisionCheck()
	{
		bool touched = false;
		for (int i = 0; i < polygonVertexNum; i+= 3)
		{
			if (polygon[i] > 1.0f && movement.x > 0 || polygon[i] < -1.0f && movement.x < 0)
			{
				movement.x *= -1;
				touched = true;
				break;
			}
		}
		for (int i = 1; i < polygonVertexNum; i += 3)
		{
			if (polygon[i] > 1.0f && movement.y > 0 || polygon[i] < -1.0f && movement.y < 0)
			{
				movement.y *= -1;
				touched = true;
				break;
			}
		}
		if (touched)
		{
			angleSpeed = -angleSpeed;
		}
	}
	void Rotate()
	{
		center = FindCenter();
		for (int i = 0; i < polygonVertexNum; i += 3)
		{
			rotatedVectors[i / 3] = { polygon[i] - center.x, polygon[i + 1] - center.y, 0 };
		}
		angle += angleSpeed;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		if (angle < -M_PI * 2)
			angle += M_PI * 2;
		
		for (int i = 0; i < 5; i++)
		{
			turnZ(rotatedVectors[i], angleSpeed);
		}
	}
	void MoveDecoration()
	{
		CollisionCheck();
		Normalize(movement);
		movement *= speed;
		Rotate();
		for (int i = 0; i < polygonVertexNum; i++)
		{
			if (!(i % 3))
			{
				polygon[i] += movement.x + center.x + rotatedVectors[i / 3].x - polygon[i];
			}
			if(i % 3 == 1)
			{
				polygon[i] += movement.y + center.y + rotatedVectors[i / 3].y - polygon[i];
			}
		}
	}
	void DrawDecoration()
	{
		MoveDecoration();//Перенести в другой поток
		glBegin(GL_LINE_LOOP);
		glColor3f(color.x, color.y, color.z);
		for (int i = 0; i < polygonVertexNum; i+=3)
		{
			glVertex3f(polygon[i], polygon[i + 1], polygon[i + 2]);
		}
		glEnd();
		glBegin(GL_POINTS);
		glVertex3f(center.x, center.y, center.z);
		glEnd();
	}
};