#include "Update.h"

UpdateItem::UpdateItem()
{
	mustDeletedU = false;
	canUpdate = true;
}

bool UpdateItem::GetCanUpdate()
{
	return canUpdate;
}

bool UpdateItem::GetMustDeletedU()
{
	return mustDeletedU;
}

void UpdateItem::StopUpdate()
{
	canUpdate = false;
}
void UpdateItem::ContinueUpdate()
{
	canUpdate = true;
}
void UpdateItem::MustDeletedU()
{
	StopUpdate();
	mustDeletedU = true;
}

void Updater::Add(UpdateItem* item)
{
	buffer.push(item);
}
void Updater::Update()
{
	while (buffer.size() > 0)
	{
		items.push_back(buffer.front());
		buffer.pop();
	}
	for (std::deque<UpdateItem*>::iterator item = items.begin(); item != items.end(); ++item)
	{
		if ((*item)->GetCanUpdate())
		{
			(*item)->Update();
		}
	}
	Delete();
}
void Updater::Delete()
{
	items.erase( std::remove_if(items.begin(), items.end(), [](UpdateItem*& item)
		{
			return (*item).GetMustDeletedU();
		}), items.end());
}
int Updater::GetSize()
{
	return items.size();
}