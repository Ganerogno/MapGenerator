#include "Sun.h"

Sun::Sun(GLfloat sunSize, int sunDistance, int wSize, GLfloat sunAngle, GLfloat sunSpeed, Shader* sunShader, Vector3D sunColor, Vector3D rotationSides)
{
	size = sunSize;
	distance = sunDistance;
	worldSize = wSize;
	currentAngle = sunAngle;
	angleSpeed = sunSpeed;
	rotateSide = rotationSides;
	if (!CreateModul(rotateSide))
		rotateSide = { 1,0,0 };
	else
		Normalize(rotateSide);
	FindPosition();
	shader = sunShader;
	color = sunColor;
;
	GLfloat* vertex = new GLfloat[24]
	{
		size, size, size,   size, -size, size,   -size, -size, size,   -size, size, size,
		size, size, -size,   size, -size, -size,   -size, -size, -size,   -size, size, -size
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
	worldPosition = position;
	worldPosition.x += worldSize;
	worldPosition.y += worldSize;
	attributeWorldPosition = glGetAttribLocation(shader->GetProgram(), "worldPosition");
	delete vertex;
	delete vertexIndex;
}
void Sun::FindPosition()
{
	position = rotateSide;
	position *= -distance;
	position.z = 0;
}
void Sun::Rotate()
{
	currentAngle += angleSpeed * 0.016;
	if (currentAngle > M_PI)
		currentAngle -= M_PI * 2;
	if (currentAngle < -M_PI)
		currentAngle += M_PI * 2;
	turnX(position, rotateSide.y * angleSpeed * 0.016);
	turnY(position, rotateSide.x * angleSpeed * 0.016);
	turnZ(position, rotateSide.z * angleSpeed * 0.016);
}
void Sun::Update()
{
	Rotate();
	worldPosition = position;
	worldPosition.x += worldSize;
	worldPosition.y += worldSize;
}
void Sun::Render()
{
	shader->Use();
	glPushMatrix();

	glVertexAttrib3f(attributeWorldPosition, worldPosition.x, worldPosition.y, worldPosition.z);
	glColor3f(color.x, color.y, color.z);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
	shader->UseBaseShader();
}
void Sun::StopRender()
{
	canRender = false;
	StopUpdate();
}
void Sun::ContinueRender()
{
	canRender = true;
	ContinueUpdate();
}
Vector3D Sun::GetPosition()
{
	return position;
}
Vector3D Sun::GetColor()
{
	return color;
}