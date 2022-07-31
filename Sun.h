#pragma once
#include <glad/glad.h>
#include "Update.h"
#include "Render.h"
#include "Math3D.h"
#include "Shader.h"

class Sun : public UpdateItem, public RenderItem
{
	Vector3D position;
	Vector3D worldPosition;
	GLfloat currentAngle;
	GLfloat angleSpeed;
	GLfloat size = 5.5;
	int attributeWorldPosition;
	int worldSize;
	int distance;
	Vector3D rotateSide;
	Vector3D color;
	GLfloat* vertex;
	GLuint VBO;
	GLuint* vertexIndex;
	GLuint EBO;
	Shader* shader;
public:
	Sun(GLfloat sunSize, int sunDistance, int wSize, GLfloat sunAngle, GLfloat sunSpeed, Shader* sunShader, Vector3D sunColor = { 1,1,1 }, Vector3D rotationSides = { 1,0,0 });
	void FindPosition();
	void Rotate();
	void Update();
	void Render();
	void StopRender();
	void ContinueRender();
	Vector3D GetPosition();
	Vector3D GetColor();
};