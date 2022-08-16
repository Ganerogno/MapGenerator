#pragma once
#include <algorithm>
#include <deque>
#include <queue>
#include <chrono>
#include "Container.h"

class UpdateItem
{
protected:
	bool mustDeletedU;
	bool canUpdate;
public:
	UpdateItem();
	bool GetCanUpdate();
	bool GetMustDeletedU();
	virtual void StopUpdate();
	virtual void ContinueUpdate();
	void MustDeletedU();
	virtual void Update() = 0;
};
class Updater
{
	std::queue<UpdateItem*> buffer;
	std::deque<UpdateItem*> items;
public:
	std::chrono::steady_clock::time_point startTime;
	static std::chrono::steady_clock::duration deltaTime;
	void Add(UpdateItem* item);
	void Update();
	void Delete();
	int GetSize();
};