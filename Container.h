#pragma once
enum Position: int
{
	end,
	menu,
	world
};
template <class T>
class Container
{
	T* item;
	Position pos;
public:
	Container(T* pItem, Position itemPos)
	{
		item = pItem;
		pos = itemPos;
	}
	T* GetItem()
	{
		return item;
	}
	Position GetPosition()
	{
		return pos;
	}
};