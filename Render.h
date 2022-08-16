#pragma once
#include <deque>
#include <algorithm>
#include <queue>
#include "Container.h"

class RenderItem
{
protected:
	bool mustDeletedR;
	bool canRender;
public:
	RenderItem();
	virtual bool GetCanRender();
	virtual bool GetMustDeletedR();
	virtual void StopRender();
	virtual void ContinueRender();
	void MustDeletedR();
	virtual void Render() = 0;
};
class Render
{
	std::queue<Container<RenderItem>> buffer;
	std::deque<RenderItem*> items;
	RenderItem* points[2];
public:
	void Add(RenderItem* item, Position pos = end);
	void AddPoint(RenderItem* item, Position pos);
	void SaveChanges();
	void Draw();
	void Delete();
	int GetSize();
};