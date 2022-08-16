#include "PerlinNoise.h"
GLfloat PerlinNoise::Noise(GLfloat x, GLfloat y, int size, int octaves, GLfloat persistence)
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
	return result / max;
}
float PerlinNoise::QunticCurve(float point)
{
	return point * point * point * (point * (point * 6 - 15) + 10);
}
GLfloat PerlinNoise::Noise(GLfloat x, GLfloat y, int size)
{
	int right = (int)(x / size);
	int top = (int)(y / size);
	GLfloat pointX = x / size - right;
	GLfloat pointY = y / size - top;
	Vector2D topLeftGradient = GetGradientVector((right + 1) * size, top * size);
	Vector2D topRightGradient = GetGradientVector(right * size, top * size);
	Vector2D bottomLeftGradient = GetGradientVector((right + 1) * size, (top + 1) * size);
	Vector2D bottomRightGradient = GetGradientVector(right * size, (top + 1) * size);

	Vector2D vectorFromTopLeft = { pointX - 1, pointY };
	Vector2D vectorFromTopRight = { pointX, pointY };
	Vector2D vectorFromBottomLeft = { pointX - 1, pointY - 1 };
	Vector2D vectorFromBottomRight = { pointX, pointY - 1 };

	GLfloat topRightPoint = FindInnerProduct2D(vectorFromTopLeft, topLeftGradient);
	GLfloat topLeftPoint = FindInnerProduct2D(vectorFromTopRight, topRightGradient);
	GLfloat bottomRightPoint = FindInnerProduct2D(vectorFromBottomLeft, bottomLeftGradient);
	GLfloat bottomLeftPoint = FindInnerProduct2D(vectorFromBottomRight, bottomRightGradient);

	GLfloat topX = Interpolation(topLeftPoint, topRightPoint, QunticCurve(pointX));
	GLfloat bottomX = Interpolation(bottomLeftPoint, bottomRightPoint, QunticCurve(pointX));
	GLfloat currentDot = Interpolation(topX, bottomX, QunticCurve(pointY));

	return currentDot;
}
GLfloat PerlinNoise::Interpolation(GLfloat first, GLfloat second, GLfloat distance)
{
	return first + distance * (second - first);
}
void PerlinNoise::SetSeed(unsigned num)
{
	seed = num;
	srand(seed);
	for (int i = 0; i < 100; i++)
	{
		table[i] = rand();
	}
}
Vector2D PerlinNoise::GetGradientVector(int x, int y)
{
	int num = (table[x % 100] * x % 17 * 9 + table[y % 100] * y % 13 * 19) % 4;
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