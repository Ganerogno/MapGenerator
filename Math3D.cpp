#include "Math3D.h"

GLfloat CreateModul(Vector3D vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}
void Normalize(Vector3D& vector)
{
	vector /= CreateModul(vector);
}
void turnZ(Vector3D& vector, GLfloat ang)
{
	GLfloat x = vector.x;
	vector.x = x * cos(ang) - vector.y * sin(ang);
	vector.y = x * sin(ang) + vector.y * cos(ang);
}
void turnX(Vector3D& vector, GLfloat ang)
{
	GLfloat y = vector.y;
	vector.y = y * cos(ang) + vector.z * sin(ang);
	vector.z = -y * sin(ang) + vector.z * cos(ang);
}
void turnY(Vector3D& vector, GLfloat ang)
{
	GLfloat x = vector.x;
	vector.x = x * cos(ang) + vector.z * sin(ang);
	vector.z = -x * sin(ang) + vector.z * cos(ang);
}
GLfloat Dot(Vector3D first, Vector3D second)
{
	return first.x * second.x + first.y * second.y + first.z * second.z;
}
Vector3D CreateNormal(Vector3D first, Vector3D second)
{
	Vector3D normal;

	normal.x = first.y * second.z - first.z * second.y;
	normal.y = first.z * second.x - first.x * second.z;
	normal.z = first.x * second.y - first.y * second.x;
	return normal;
}
GLfloat FindAngle(Vector3D first, Vector3D second)
{
	GLfloat cos = Dot(first, second) / (CreateModul(first) * CreateModul(second));
	GLfloat sin = CreateModul(CreateNormal(first, second)) / (CreateModul(first) * CreateModul(second));
	return atan2f(sin, cos);
}Vector3D CreateVector3D(Vector3D startP, Vector3D endP)
{
	return { endP.x - startP.x, endP.y - startP.y, endP.z - startP.z };
}
Vector3D Cross(Vector3D first, Vector3D second)
{
	return { first.y * second.z - first.z * second.y, first.z * second.x - first.x * second.z, first.x * second.y - first.y * second.x};
}