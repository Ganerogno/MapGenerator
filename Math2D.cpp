#include "Math2D.h"
Vector2D CreateVector2D(Vector2D startP, Vector2D endP)
{
	return { endP.x - startP.x, endP.y - startP.y };
}
GLfloat FindInnerProduct2D(Vector2D first, Vector2D second)
{
	return first.x * second.x + first.y * second.y;
}