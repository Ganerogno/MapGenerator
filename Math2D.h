#pragma once
#include "Math3D.h"
struct Vector2D
{
	GLfloat x;
	GLfloat y;
	Vector2D& operator =(Vector2D other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	Vector2D& operator +=(Vector2D other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2D& operator -=(Vector2D other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2D& operator *=(GLfloat c)
	{
		x *= c;
		y *= c;
		return *this;
	}
	Vector2D& operator /=(GLfloat c)
	{
		x /= c;
		y /= c;
		return *this;
	}
};
Vector2D CreateVector2D(Vector2D startP, Vector2D endP);
GLfloat FindInnerProduct2D(Vector2D first, Vector2D second);