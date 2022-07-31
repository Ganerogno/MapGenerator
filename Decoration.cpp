#include "Decoration.h"
Decoration::Decoration(Vector3D move, Vector3D polygonColor, GLfloat* dotsArr, int dotsNum)
{
	movement = move;
	if (!movement.z)
		movement.z = 0;
	color = polygonColor;
	polygon = dotsArr;
	polygonVertexNum = dotsNum;
	angle = 0;
	angleSpeed = 0.5f;
	speed = 0.5f;
	canUpdate = true;
}
Vector3D Decoration::FindCenter()
{
	Vector3D cent = { 0,0,0 };
	for (int i = 0; i < polygonVertexNum; i += 3)
	{
		cent.x += polygon[i];
		cent.y += polygon[i + 1];
	}
	cent *= 3;
	cent /= polygonVertexNum;
	return cent;
}
void Decoration::CollisionCheck()
{
	bool touched = false;
	for (int i = 0; i < polygonVertexNum; i += 3)
	{
		if (polygon[i] > 1.0f && movement.x > 0 || polygon[i] < -1.0f && movement.x < 0)
		{
			movement.x *= -1;
			touched = true;
			break;
		}
	}
	for (int i = 1; i < polygonVertexNum; i += 3)
	{
		if (polygon[i] > 1.0f && movement.y > 0 || polygon[i] < -1.0f && movement.y < 0)
		{
			movement.y *= -1;
			touched = true;
			break;
		}
	}
	if (touched)
	{
		angleSpeed = -angleSpeed;
	}
}
void Decoration::Rotate()
{
	center = FindCenter();
	for (int i = 0; i < polygonVertexNum; i += 3)
	{
		rotatedVectors[i / 3] = { polygon[i] - center.x, polygon[i + 1] - center.y, 0 };
	}
	angle += angleSpeed;
	if (angle > M_PI)
		angle -= M_PI * 2;
	if (angle < -M_PI)
		angle += M_PI * 2;

	for (int i = 0; i < 5; i++)
	{
		turnZ(rotatedVectors[i], angleSpeed * std::chrono::duration<double>( Updater::deltaTime).count());
	}
}
void Decoration::MoveDecoration()
{
	CollisionCheck();
	Normalize(movement);
	movement *= speed;
	movement *= std::chrono::duration<double>(Updater::deltaTime).count();
	Rotate();
	for (int i = 0; i < polygonVertexNum; i++)
	{
		if (!(i % 3))
		{
			polygon[i] += movement.x + center.x + rotatedVectors[i / 3].x - polygon[i];
		}
		if (i % 3 == 1)
		{
			polygon[i] += movement.y + center.y + rotatedVectors[i / 3].y - polygon[i];
		}
	}
}
void Decoration::DrawDecoration()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(color.x, color.y, color.z);
	for (int i = 0; i < polygonVertexNum; i += 3)
	{
		glVertex3f(polygon[i], polygon[i + 1], polygon[i + 2]);
	}
	glEnd();
	glBegin(GL_POINTS);
	glVertex3f(center.x, center.y, center.z);
	glEnd();
}
void Decoration::Update()
{
	MoveDecoration();
}