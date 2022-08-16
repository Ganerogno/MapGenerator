#pragma once
#include "Render.h"

RenderItem::RenderItem()
{
	canRender = true;
	mustDeletedR = false;
}

bool RenderItem::GetCanRender()
{
	return canRender;
}

bool RenderItem::GetMustDeletedR()
{
	return mustDeletedR;
}

void RenderItem::StopRender()
{
	canRender = false;
}

void RenderItem::ContinueRender()
{
	canRender = true;
}

void RenderItem::MustDeletedR()
{
	StopRender();
	mustDeletedR = true;
}
void Render::Add(RenderItem* item, Position pos)
{
	buffer.push(Container<RenderItem>(item, pos));
}
void Render::AddPoint(RenderItem* item, Position pos)
{
	points[pos - 1] = item;
}
void Render::SaveChanges()
{
	while (buffer.size() > 0)
	{
		if (!buffer.front().GetPosition()) //end
		{
			items.push_back(buffer.front().GetItem());
		}
		else
		{
			for (auto it = items.begin(); it != items.end(); ++it)
			{
				if ((*it) == points[buffer.front().GetPosition() - 1])
				{
					items.insert(it + 1, buffer.front().GetItem());
					break;
				}
			}
		}
		buffer.pop();
	}
}
void Render::Draw()
{
	SaveChanges();
	for (std::deque<RenderItem*>::iterator item = items.begin(); item != items.end(); ++item)
	{
		if ((*item)->GetCanRender())
		{
			(*item)->Render();
		}
	}
	Delete();
}
void Render::Delete()
{
	items.erase(std::remove_if(items.begin(), items.end(), [](RenderItem*& item)
		{
			return (*item).GetCanRender();
		}), items.end());
}
int Render::GetSize()
{
	return items.size();
}