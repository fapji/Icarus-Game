#pragma once
#include <vector>
#include "Item.h"
#include "HpFlask.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void AddItem(Item* item);
	void RemoveScoreItem(int vectorPos);
	void RemoveHpItem();

	void Update();
	void Draw();

	std::vector<Item*> GetScoreItems();
	HpFlask* GetHpItem();
private:
	std::vector<Item*> m_ScoreItems;
	HpFlask* m_HpItem;

};

