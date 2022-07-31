#pragma once
#include <iostream>
#include <glad/glad.h>


class PerlinNoise
{
public:
	static unsigned seed;
	static int table[];
	static GLfloat scale;
	static GLfloat Noise(GLfloat x, GLfloat y, int size, int octaves, GLfloat persistence)
	{
		GLfloat amplitude = 1;
		GLfloat max = 0;
		GLfloat result = 0;
		GLfloat count = 0;
		for (int count = 0; octaves > count; count++)
		{
			max += amplitude;
			result += Noise(x, y, size / (count + 1)) * amplitude;
			amplitude *= persistence;
		}
		return result/max;
	}
	static float QunticCurve(float point)
	{
		return point * point * point * (point * (point * 6 - 15) + 10);
	}
	/*
	static GLfloat Noise(GLfloat x, GLfloat y, int size)
	{
		GLfloat left = x - (int)(x / size) * size;
		GLfloat bottom = y - (int)(y / size) * size;
		Vector2D topLeftGradient = GetGradientVector(left, bottom + size);
		Vector2D topRightGradient = GetGradientVector(left + size, bottom + size);
		Vector2D bottomLeftGradient = GetGradientVector(left, bottom);
		Vector2D bottomRightGradient = GetGradientVector(left + size, bottom);

		Vector2D vectorFromTopLeft = CreateVector2D({ (GLfloat)left,(GLfloat)(bottom - size) }, { x,y });
		Vector2D vectorFromTopRight = CreateVector2D({ (GLfloat)(left - size),(GLfloat)(bottom - size) }, { x,y });
		Vector2D vectorFromBottomLeft = CreateVector2D({ (GLfloat)left,(GLfloat)bottom }, { x,y });
		Vector2D vectorFromBottomRight = CreateVector2D({ (GLfloat)(left - size),(GLfloat)bottom }, { x,y });

		GLfloat topRightPoint = FindInnerProduct2D(vectorFromTopLeft, topLeftGradient);
		GLfloat topLeftPoint = FindInnerProduct2D(vectorFromTopRight, topRightGradient);
		GLfloat bottomRightPoint = FindInnerProduct2D(vectorFromBottomLeft, bottomLeftGradient);
		GLfloat bottomLeftPoint = FindInnerProduct2D(vectorFromBottomRight, bottomRightGradient);

		GLfloat topX = Interpolation(topLeftPoint, topRightPoint, x / size);
		GLfloat bottomX = Interpolation(bottomLeftPoint, bottomRightPoint, x / size);
		GLfloat currentDot = Interpolation(topX, bottomX, y / size);

		return currentDot;
	}
	*/
	static GLfloat Noise(GLfloat x, GLfloat y, int size)
	{
		int right = (int)(x/size);
		int top = (int)(y/size);
		GLfloat pointX = x/size - right;
		GLfloat pointY = y/size - top;
		Vector2D topLeftGradient = GetGradientVector((right + 1) * size, top*size);
		Vector2D topRightGradient = GetGradientVector(right * size, top*size);
		Vector2D bottomLeftGradient = GetGradientVector((right + 1) *size, (top + 1) *size);
		Vector2D bottomRightGradient = GetGradientVector(right*size, (top + 1) *size);

		Vector2D vectorFromTopLeft = { pointX - 1, pointY };
		Vector2D vectorFromTopRight = { pointX, pointY };
		Vector2D vectorFromBottomLeft = { pointX - 1, pointY - 1};
		Vector2D vectorFromBottomRight = { pointX, pointY - 1};

		GLfloat topRightPoint = FindInnerProduct2D(vectorFromTopLeft, topLeftGradient);
		GLfloat topLeftPoint = FindInnerProduct2D(vectorFromTopRight, topRightGradient);
		GLfloat bottomRightPoint = FindInnerProduct2D(vectorFromBottomLeft, bottomLeftGradient);
		GLfloat bottomLeftPoint = FindInnerProduct2D(vectorFromBottomRight, bottomRightGradient);

		GLfloat topX = Interpolation(topLeftPoint, topRightPoint, QunticCurve(pointX));
		GLfloat bottomX = Interpolation(bottomLeftPoint, bottomRightPoint, QunticCurve(pointX));
		GLfloat currentDot = Interpolation(topX, bottomX, QunticCurve(pointY));

		return currentDot;
	}
	static GLfloat Interpolation(GLfloat first, GLfloat second, GLfloat distance)
	{
		return first + distance * (second - first);
	}
	static void SetSeed(unsigned num)
	{
		seed = num;
		srand(seed);
		for (int i = 0; i < 100; i++)
		{
			table[i] = rand();
		}
	}
	static Vector2D GetGradientVector(int x, int y)
	{
		int num = (table[x%100] * x%17 * 9 + table[y%100] * y%13 * 19)%4;
		switch (num)
		{
		case 0:
			return Vector2D{ 1,0 };
		case 1:
			return Vector2D{ -1,0 };
		case 2:
			return Vector2D{ 0,1 };
		case 3:
			return Vector2D{ 0,-1 };
		}
	}
};