#include "pch.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
	m_HpItem = new HpFlask(Point2f(410, 7100));
}

ItemManager::~ItemManager()
{
	for (Item* item : m_ScoreItems) {
		delete item;
	}
	delete m_HpItem;
	m_HpItem = nullptr;
}

void ItemManager::AddItem(Item* item)
{
	m_ScoreItems.emplace_back(item);
}

void ItemManager::RemoveScoreItem(int vectorPos)
{
	delete m_ScoreItems.at(vectorPos);
	m_ScoreItems.at(vectorPos) = nullptr;
}

void ItemManager::RemoveHpItem()
{
	delete m_HpItem;
	m_HpItem = nullptr;
}

void ItemManager::Draw()
{
	for (Item* item : m_ScoreItems) {
		if (item != nullptr)
		{
			item->Draw();
		}
	}
	if (m_HpItem != nullptr)
	{
		m_HpItem->Draw();
	}
}

std::vector<Item*> ItemManager::GetScoreItems()
{
	return m_ScoreItems;
}

HpFlask* ItemManager::GetHpItem()
{
	return m_HpItem;
}
