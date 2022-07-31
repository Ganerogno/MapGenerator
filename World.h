#pragma once
#include <vector>
#include "Render.h"
#include "Math3D.h"
#include "PerlinNoise.h"
#include "Water.h"
#include "Camera.h"
#include "Sun.h"

class Chunk
{
public:
	static const int size;
	static int octaves;
	GLfloat** coordinates;
	Vector3D** color;
	GLuint vertexVBO;
	GLuint colorVBO;
	GLuint indexEBO;
	Chunk();
	Chunk(const Chunk& other);
	~Chunk();
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
};