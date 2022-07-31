#include "Water.h"


Water::Water(int worldSize, int sc, Shader* waterShader, Camera* pCamera)
{
	scale = sc;
	size = worldSize * scale;
	time = 0;
	surface = new GLfloat * [size];
	for (int i = 0; i < size; i++)
	{
		surface[i] = new GLfloat[size]{};
	}
	shader = waterShader;
	camera = pCamera;
}

Water::Water(const Water& other)
{
	scale = other.scale;
	size = other.size;
	time = other.time;
	surface = new GLfloat * [size];
	for (int i = 0; i < size; i++)
	{
		surface[i] = new GLfloat[size]{};
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			surface[i][j] = other.surface[i][j];
		}
	}
	shader = other.shader;
	camera = other.camera;
}
Water::~Water()
{
	for (int i = 0; i < size; i++)
	{
		delete surface[i];
	}
	delete surface;
}

void Water::Update()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			surface[i][j] = PerlinNoise::Noise(i + time, j, size);
		}
	}
	time++;
}
void Water::Render()
{
	shader->Use();
	glBegin(GL_QUADS);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			glVertex3f(i/scale, j / scale, hight + surface[i][j]);
			glVertex3f((i + 1) / scale, j / scale, hight + surface[i + 1][j]);
			glVertex3f((i + 1) / scale, (j + 1) / scale, hight + surface[i + 1][j + 1]);
			glVertex3f(i / scale, (j + 1) / scale, hight + surface[i][j + 1]);
		}
	}
	glEnd();
	shader->UseBaseShader();
}
void Water::StopRender()
{
	canRender = false;
	StopUpdate();
}
void Water::ContinueRender()
{
	canRender = true;
	ContinueUpdate();
}