#pragma once
#include "Render.h"
#include "World.h"

enum flags : int
{
	endRenderWorld,
	startRenderWorld
};
class RenderPoint : public RenderItem
{
	int flag;
	World* world;
public:
	RenderPoint(int num, World* pWorld)
	{
		flag = num;
		world = pWorld;
	}
	void Render() override
	{
		switch (flag)
		{
		case startRenderWorld:
			glClearColor(0.1f, 0.2f, 0.6f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glPushMatrix();
			glRotatef(-world->GetCamera()->angle.x, 1, 0, 0);
			glRotatef(world->GetCamera()->angle.z, 0, 0, 1);
			glTranslatef(-world->GetCamera()->GetPosition().x, -world->GetCamera()->GetPosition().y, -(world->GetCamera()->GetPosition().z + world->GetCamera()->GetGrowth()));
			break;
		case endRenderWorld:
			glPopMatrix();
			break;
		}
	}
	bool GetCanRender() override
	{
		return world->GetCanRender();
	}
	bool GetMustDeletedR() override
	{
		return world->GetMustDeletedR();
	}
};