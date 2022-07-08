#pragma once
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Math3D.h"
#include "Update.h"
class Decoration : public UpdateItem
{
	Vector3D movement;
	Vector3D position;
	Vector3D color;
	Vector3D center;
	GLfloat angle;
	GLfloat angleSpeed;
	GLfloat* polygon;
	GLfloat speed;
	Vector3D rotatedVectors[5]{};//Сделать указатель для n-го кол-ва векторов
	int polygonVertexNum;
	void Update() override;
public:
	Decoration(Vector3D move, Vector3D polygonColor, GLfloat* dotsArr, int dotsNum);
	Vector3D FindCenter();
	void CollisionCheck();
	void Rotate();
	void MoveDecoration();
	void DrawDecoration();
};