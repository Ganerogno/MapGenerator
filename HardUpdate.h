#pragma once
#include <algorithm>
#include <deque>
#include <chrono>

class HUpdateItem
{
protected:
	bool mustDeletedHU;
	bool canHardUpdate;
public:
	HUpdateItem();
	bool GetCanHUpdate();
	bool GetMustDeleted();
	virtual void StopHUpdate();
	virtual void ContinueHUpdate();
	void MustDeletedHU();
	virtual void HUpdate() = 0;
};
class HardUpdater
{
	std::deque<HUpdateItem*> items;
public:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::duration static deltaTime;
	void Add(HUpdateItem* item);
	void HUpdate();
	void Delete();
};