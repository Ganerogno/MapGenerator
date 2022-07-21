#pragma once
#include <GLFW/glfw3.h>
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
void turnZ(Vector3D& vector, GLfloat angle);
GLfloat FindInnerProduct(Vector3D first, Vector3D second);
Vector3D CreateNormal(Vector3D first, Vector3D second);
GLfloat FindAngle(Vector3D first, Vector3D second);
