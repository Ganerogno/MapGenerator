#include "HardUpdate.h"

HUpdateItem::HUpdateItem()
{
	mustDeletedHU = false;
	canHardUpdate = true;
}

bool HUpdateItem::GetCanHUpdate()
{
	return canHardUpdate;
}

bool HUpdateItem::GetMustDeleted()
{
	return mustDeletedHU;
}

void HUpdateItem::StopHUpdate()
{
	canHardUpdate = false;
}
void HUpdateItem::ContinueHUpdate()
{
	canHardUpdate = true;
}
void HUpdateItem::MustDeletedHU()
{
	StopHUpdate();
	mustDeletedHU = true;
}

void HardUpdater::Add(HUpdateItem* item)
{
	items.push_back(item);
}

void HardUpdater::HUpdate()
{
	for (std::deque<HUpdateItem*>::iterator item = items.begin(); item != items.end(); ++item)
	{
		if ((*item)->GetCanHUpdate())
		{
			(*item)->HUpdate();
		}
	}
	Delete();
}
void HardUpdater::Delete()
{
	items.erase(std::remove_if(items.begin(), items.end(), [](HUpdateItem*& item)
		{
			return (*item).GetMustDeleted();
		}), items.end());
}