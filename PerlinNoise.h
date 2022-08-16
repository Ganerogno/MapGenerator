#pragma once
#include <iostream>
#include <glad/glad.h>
#include "Math2D.h"

class PerlinNoise
{
public:
	static unsigned seed;
	static int table[];
	static GLfloat scale;
	static GLfloat Noise(GLfloat x, GLfloat y, int size, int octaves, GLfloat persistence);
	static float QunticCurve(float point);
	static GLfloat Noise(GLfloat x, GLfloat y, int size);
	static GLfloat Interpolation(GLfloat first, GLfloat second, GLfloat distance);
	static void SetSeed(unsigned num);
	static Vector2D GetGradientVector(int x, int y);
};