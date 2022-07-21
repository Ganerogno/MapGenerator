#pragma once
#include <iostream>
#include <deque>
#include <chrono>

class UpdateItem
{
protected:
	bool mustDeleted;
	bool canUpdate;
public:
	UpdateItem();
	bool GetCanUpdate();
	bool GetMustDeleted();
	virtual void StopUpdate();
	virtual void ContinueUpdate();
	void MustDeleted();
	virtual void Update() = 0;
};
class Updater
{
	std::deque<UpdateItem*> items;
public:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::duration static deltaTime;
	void Add(UpdateItem* item);
	void Update();
	void Delete();
};