#pragma once
#include <GLFW/glfw3.h>
#include <math.h>
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
GLfloat CreateModul(Vector3D vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.x);
}
void Normalize(Vector3D& vector)
{
	vector /= CreateModul(vector);
}