#pragma once
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <math.h>
#include "Math2D.h"
struct Vector3D
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	Vector3D& operator =(Vector3D other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	Vector3D& operator +=(Vector3D other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vector3D& operator -=(Vector3D other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vector3D& operator *=(GLfloat c)
	{
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}
	Vector3D& operator /=(GLfloat c)
	{
		x /= c;
		y /= c;
		z /= c;
		return *this;
	}
};
GLfloat CreateModul(Vector3D vector);
void Normalize(Vector3D& vector);
void turnZ(Vector3D& vector, GLfloat ang);
void turnX(Vector3D& vector, GLfloat ang);
void turnY(Vector3D& vector, GLfloat ang);
GLfloat Dot(Vector3D first, Vector3D second);
Vector3D CreateNormal(Vector3D first, Vector3D second);
GLfloat FindAngle(Vector3D first, Vector3D second);
Vector3D CreateVector3D(Vector3D startP, Vector3D endP);
Vector3D Cross(Vector3D first, Vector3D second);
