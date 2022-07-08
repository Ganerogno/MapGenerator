#pragma once
#include <deque>

class RenderItem
{
protected:
	bool mustDeleted;
	bool canRender;
public:
	RenderItem();
	bool GetCanRender();
	bool GetMustDeleted();
	void StopRender();
	void MustDeleted();
	virtual void Render() = 0;
};
class Render
{
	std::deque<RenderItem*> items;
public:
	void Add(RenderItem* item);
	void Draw();
	void Delete();
};