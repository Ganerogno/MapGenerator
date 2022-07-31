#pragma once
#include <deque>
#include<glad/glad.h>
#include <algorithm>

class RenderItem
{
protected:
	bool mustDeleted;
	bool canRender;
public:
	RenderItem();
	bool GetCanRender();
	bool GetMustDeleted();
	virtual void StopRender();
	virtual void ContinueRender();
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