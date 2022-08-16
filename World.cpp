#include "World.h"

GLfloat FindZ(GLfloat x, GLfloat y)
{
	GLfloat topX = PerlinNoise::Interpolation(Chunk::coordinates[(int)x][(int)y + 1], Chunk::coordinates[(int)x + 1][(int)y + 1], x - (int)x);
	GLfloat bottomX = PerlinNoise::Interpolation(Chunk::coordinates[(int)x][(int)y], Chunk::coordinates[(int)x + 1][(int)y], x - (int)x);
	return PerlinNoise::Interpolation(topX, bottomX, y - (int)y);
}

Chunk::Chunk()
{
	int count;
	color = new Vector3D * [Chunk::size - 1];
	for (int i = 0; i < Chunk::size - 1; i++)
	{
		color[i] = new Vector3D[Chunk::size - 1]{};
	}

	coordinates = new GLfloat* [Chunk::size];
	for (int i = 0; i < Chunk::size; i++)
	{
		coordinates[i] = new GLfloat[Chunk::size]{};
	}

	for (int i = 0; i < Chunk::size; i++)
	{
		for (int j = 0; j < Chunk::size; j++)
		{
			coordinates[i][j] += PerlinNoise::Noise(i, j, Chunk::size, 8, 0.5) * PerlinNoise::scale;
		}
	}
	for (int i = 0; i < Chunk::size - 1; i++)
	{
		for (int j = 0; j < Chunk::size - 1; j++)
		{
			if (coordinates[i][j] > 0.7 * 20)
			{
				color[i][j].x = 0.8;
				color[i][j].y = 0.8;
				color[i][j].z = 0.8;
			}
			else if (coordinates[i][j] < 0.7 * 20)
			{
				color[i][j].x = 0.2;
				color[i][j].y = 0.8;
				color[i][j].z = 0.1;
			}
			if (coordinates[i][j] < Water::hight + 2)
			{
				color[i][j].x = 0.8;
				color[i][j].y = 0.8;
				color[i][j].z = 0.1;
			}
			color[i][j].x += (rand() % 10) / 50.;
			color[i][j].y += (rand() % 10) / 50.;
			color[i][j].z += (rand() % 10) / 50.;
		}
	}
}

Chunk::Chunk(const Chunk& other)
{
	coordinates = new GLfloat* [Chunk::size];
	color = other.color;
	for (int i = 0; i < Chunk::size; i++)
	{
		coordinates[i] = new GLfloat[Chunk::size]{};
	}
	for (int i = 0; i < Chunk::size; i++)
	{
		for (int j = 0; j < Chunk::size; j++)
		{
			coordinates[i][j] = other.coordinates[i][j];
		}
	}
	color = new Vector3D * [Chunk::size - 1];
	for (int i = 0; i < Chunk::size - 1; i++)
	{
		color[i] = new Vector3D[Chunk::size - 1]{};
	}
	for (int i = 0; i < Chunk::size - 1; i++)
	{
		for (int j = 0; j < Chunk::size - 1; j++)
		{
			color[i][j] = other.color[i][j];
		}
	}
}

Chunk::~Chunk()
{
	for (int i = 0; i < Chunk::size; i++)
	{
		delete coordinates[i];
	}
	delete coordinates;
	for (int i = 0; i < Chunk::size - 1; i++)
	{
		delete color[i];
	}
	delete color;
}
void Chunk::DrawChunk()
{
	for (int i = 0; i < Chunk::size - 1; i++)
	{
		for (int j = 0; j < Chunk::size - 1; j++)
		{
			glBegin(GL_QUADS);
			glColor3f(color[i][j].x, color[i][j].y, color[i][j].z);
			glVertex3f(i, j, coordinates[i][j]);
			glVertex3f(i + 1, j, coordinates[i + 1][j]);
			glVertex3f(i + 1, j + 1, coordinates[i + 1][j + 1]);
			glVertex3f(i, j + 1, coordinates[i][j + 1]);
			glEnd();
		}
	}
}

World::World(Camera* pCamera, Water* pWater, Sun* pSun)
{
	camera = pCamera;
	water = pWater;
	sun = pSun;
}
void World::Render()
{
	floor.DrawChunk();
	water->Render();
	sun->Render();
}
void World::StopRender()
{
	canRender = false;
	water->StopRender();
	sun->StopRender();
}
void World::ContinueRender()
{
	canRender = true;
	water->ContinueRender();
	sun->ContinueRender();
}
Camera* World::GetCamera()
{
	return camera;
}