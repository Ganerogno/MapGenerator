#include "World.h"
Chunk::Chunk()
{
	int count;
	color = new Vector3D * [Chunk::size - 1];
	for (int i = 0; i < Chunk::size - 1; i++)
	{
		color[i] = new Vector3D[Chunk::size - 1]{};
	}

	coordinates = new float* [Chunk::size];
	for (int i = 0; i < Chunk::size; i++)
	{
		coordinates[i] = new float[Chunk::size]{};
	}

	for (int i = 0; i < Chunk::size; i++)
	{
		for (int j = 0; j < Chunk::size; j++)
		{
			coordinates[i][j] += PerlinNoise::Noise(i, j, Chunk::size, 8, 0.5);
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
			if (coordinates[i][j] < -0.6 * 20)
			{
				color[i][j].x = 0.2;
				color[i][j].y = 0.1;
				color[i][j].z = 0.8;
			}
			color[i][j].x += (rand() % 10) / 50.;
			color[i][j].y += (rand() % 10) / 50.;
			color[i][j].z += (rand() % 10) / 50.;
		}
	}
}

Chunk::Chunk(const Chunk& other)
{
	coordinates = new float* [Chunk::size];
	color = other.color;
	for (int i = 0; i < Chunk::size; i++)
	{
		coordinates[i] = new float[Chunk::size]{};
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

World::World(Camera* pCamera)
{
	camera = pCamera;
	floor.push_back(std::deque<Chunk>());
	floor[0].push_back(Chunk());
}
void World::Render()
{
	glClearColor(0.1f, 0.2f, 0.6f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(-camera->angle.x, 1, 0, 0);
	glRotatef(camera->angle.z, 0, 0, 1);
	glTranslatef(-camera->position.x, -camera->position.y, -(camera->position.z + camera->growth));
	for (int i = 0; i < floor.size(); i++)
	{
		for (int j = 0; j < floor[i].size(); j++)
		{
			floor[i][j].DrawChunk();
		}
	}
	glPopMatrix();
}
void World::StopRender()
{
	canRender = false;
}