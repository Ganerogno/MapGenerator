#pragma once
#include <deque>
#include <vector>
#include "Render.h"
#include "Math3D.h"
#include "PerlinNoise.h"
#include "Camera.h"

class Chunk
{
public:
	static int size;
	static int octaves;
	float** coordinates;
	Vector3D** color;
	Chunk();
	Chunk(const Chunk& other);
	~Chunk();
	void DrawChunk();
};


class World : public RenderItem
{
	std::deque<std::deque<Chunk>> floor;
	Camera* camera;
public:
	World(Camera* pCamera);
	void Render() override;
	void StopRender() override;
};