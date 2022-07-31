#pragma once
#include <glad/glad.h>
#include "Math3D.h"
#include "PerlinNoise.h"
#include "Update.h"
#include "Render.h"
#include "Shader.h"
#include "Camera.h"

class Water : public UpdateItem, public RenderItem
{
	Shader* shader;
	int size;
	int time;
	GLfloat scale;
	GLfloat** surface;
	Camera* camera;
public:
	static GLfloat hight;
	Water(int worldSize, int sc, Shader* waterShader, Camera* pCamera);
	Water(const Water& other);
	~Water();
	void Update() override;
	void Render() override;
	void StopRender() override;
	void ContinueRender() override;
};