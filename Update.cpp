#include "Update.h"

UpdateItem::UpdateItem()
{
	mustDeleted = false;
	canUpdate = true;
}

bool UpdateItem::GetCanUpdate()
{
	return canUpdate;
}

bool UpdateItem::GetMustDeleted()
{
	return mustDeleted;
}

void UpdateItem::StopUpdate()
{
	canUpdate = false;
}
void UpdateItem::ContinueUpdate()
{
	canUpdate = true;
}
void UpdateItem::MustDeleted()
{
	StopUpdate();
	mustDeleted = true;
}

void Updater::Add(UpdateItem* item)
{
	items.push_back(item);
}

void Updater::Update()
{
	for (std::deque<UpdateItem*>::iterator item = items.begin(); item != items.end(); ++item)
	{
		if ((*item)->GetCanUpdate())
		{
			(*item)->Update();
		}
	}
}
void Updater::Delete()
{
	items.erase( std::remove_if(items.begin(), items.end(), [](UpdateItem*& item)
		{
			return (*item).GetCanUpdate();
		}), items.end());
}