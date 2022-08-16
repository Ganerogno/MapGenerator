#pragma once
#include <vector>
#include "Camera.h"
#include "Render.h"
#include "Update.h"
#include "Math3D.h"
#include "PerlinNoise.h"
#include "Water.h"
#include "Sun.h"

GLfloat FindZ(GLfloat x, GLfloat y);

class Chunk
{
public:
	static const int size;
	static int octaves;
	static GLfloat** coordinates;
	Vector3D** color;
	GLuint vertexVBO;
	GLuint colorVBO;
	GLuint indexEBO;
	Chunk();
	Chunk(const Chunk& other);
	~Chunk();
	void FillChunk();
	void DrawChunk();
};


class World : public RenderItem
{
	Chunk floor;
	Camera* camera;
	Water* water;
	Sun* sun;
public:
	World(Camera* pCamera, Water* pWater, Sun* pSun);
	void Render() override;
	void StopRender() override;
	void ContinueRender() override;
	Camera* GetCamera();
	void ReBuild();
};