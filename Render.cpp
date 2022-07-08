#pragma once
#include "Render.h"

RenderItem::RenderItem()
{
	canRender = true;
	mustDeleted = false;
}

bool RenderItem::GetCanRender()
{
	return canRender;
}

bool RenderItem::GetMustDeleted()
{
	return mustDeleted;
}

void RenderItem::StopRender()
{
	canRender = false;
}

void RenderItem::MustDeleted()
{
	StopRender();
	mustDeleted = true;
}

void Render::Add(RenderItem* item)
{
	items.push_back(item);
}

void Render::Draw()
{
	for (std::deque<RenderItem*>::iterator item = items.begin(); item != items.end(); ++item)
	{
		if ((*item)->GetCanRender())
		{
			(*item)->Render();
		}
	}
}
void Render::Delete()
{
	for (std::deque<RenderItem*>::iterator item = items.begin(); item != items.end(); ++item)
	{
		if ((*item)->GetMustDeleted())
		{
			items.erase(item);
		}
	}
}