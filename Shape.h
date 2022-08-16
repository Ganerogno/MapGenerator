#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Render.h"
#include "Math3D.h"
#include "Shader.h"

class Shape
{
	Vector3D size;
	GLuint VBO;
	GLuint EBO;
public:
	Shape(Vector3D sSize)
	{
		size = sSize;
		size /= 2;
		GLfloat* vertex = new GLfloat[24]
		{
			size.x, size.y, size.z,   size.x, -size.y, size.z,   -size.x, -size.y, size.z,   -size.x, size.y, size.z,
			size.x, size.y, -size.z,   size.x, -size.y, -size.z,   -size.x, -size.y, -size.z,   -size.x, size.y, -size.z
		};
		GLuint* vertexIndex = new GLuint[24]
		{
			0,1,2,3,  4,5,6,7,  1,2,6,5,  0,3,7,4,  0,1,5,4,  2,3,7,6
		};
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, vertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 24, vertexIndex, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		delete vertex;
		delete vertexIndex;
	}
	void Draw()
	{

		//glVertexAttrib3f(attributePosition, position.x, position.y, position.z);

		glBegin(GL_QUADS);
		glVertex3f(0, 0, 1);
		glVertex3f(1, 0, 1);
		glVertex3f(1, 1, 1);
		glVertex3f(0, 1, 1);
		glEnd();
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableClientState(GL_VERTEX_ARRAY);

	}
	GLfloat GetSizeX()
	{
		return size.x;
	}
	GLfloat GetSizeY()
	{
		return size.y;
	}
	GLfloat GetSizeZ()
	{
		return size.z;
	}
};
/*
class Body
{
public:
	Shape* shape;
	Vector3D color;
	Vector3D position;
	GLfloat angle;
	
	Body(Shape* bShape, Vector3D bColor, Vector3D bPosition, GLfloat bAngle)
	{
		shape = bShape;
		color = bColor;
		position = bPosition;
		angle = bAngle;
	}
	void Draw()
	{
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(angle, 0, 0, 1);
		glColor3f(color.x, color.y, color.z);
		shape->Draw(color, position);
		glPopMatrix();
	}
	void Move(Vector3D movement)
	{

	}
};*/
