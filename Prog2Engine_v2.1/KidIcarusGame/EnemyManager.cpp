#include "pch.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(Rectf viewPort)
{
	m_pSnakes.push_back(new Snake(215,2332));
	m_pSnakes.push_back(new Snake(265, 2332));
	m_pSnakes.push_back(new Snake(315, 2332));
	m_pSnakes.push_back(new Snake(355, 2332));

	m_pSnakes.push_back(new Snake(155, 2830));
	m_pSnakes.push_back(new Snake(220, 2830));
	m_pSnakes.push_back(new Snake(320, 2930));
	m_pSnakes.push_back(new Snake(380,2930));

	m_pSnakes.push_back(new Snake(450,3325));
	m_pSnakes.push_back(new Snake(355,3325));
	m_pSnakes.push_back(new Snake(205,3425));
	m_pSnakes.push_back(new Snake(280,3425));

	m_pSnakes.push_back(new Snake(440,3730));
	m_pSnakes.push_back(new Snake(360,3730));
	m_pSnakes.push_back(new Snake(210,3830));
	m_pSnakes.push_back(new Snake(280,3830));

	m_pEyeghosts.push_back(new EyeGhost(1, 4000));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 4000));
	m_pEyeghosts.push_back(new EyeGhost(1, 4100));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 4100));

	m_pEyeghosts.push_back(new EyeGhost(1, 4500));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 4500));
	m_pEyeghosts.push_back(new EyeGhost(1, 4600));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 4600));

	m_pEyeghosts.push_back(new EyeGhost(1, 5250));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 5250));

	m_pEyeghosts.push_back(new EyeGhost(1, 6000));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 6000));
	m_pEyeghosts.push_back(new EyeGhost(1, 6200));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 6200));

	m_pSnakes.push_back(new Snake(500, 6060));
	m_pSnakes.push_back(new Snake(580, 6060));

	m_pSnakes.push_back(new Snake(220, 6460));
	m_pSnakes.push_back(new Snake(300, 6460));

	m_pEyeghosts.push_back(new EyeGhost(1, 6600));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 6600));
	m_pEyeghosts.push_back(new EyeGhost(1, 7000));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 7000));



	m_pSnakes.push_back(new Snake(25, 8700));
	m_pSnakes.push_back(new Snake(90, 8700));
	m_pSnakes.push_back(new Snake(250, 8800));
	m_pSnakes.push_back(new Snake(320, 8910));


	m_pEyeghosts.push_back(new EyeGhost(1, 9650));
	m_pEyeghosts.push_back(new EyeGhost(viewPort.width - 60, 9650));

	m_pSnakes.push_back(new Snake(60, 9695));
	m_pSnakes.push_back(new Snake(120, 9695));
	m_pSnakes.push_back(new Snake(180, 9695));
	m_pSnakes.push_back(new Snake(240, 9695));
	m_pSnakes.push_back(new Snake(300, 9695));
	m_pSnakes.push_back(new Snake(360, 9695));





	//m_pEyeghosts.push_back(new EyeGhost());
}

EnemyManager::~EnemyManager()
{
	for (Snake* Snakes: m_pSnakes)
	{
		delete Snakes;
		Snakes = nullptr;
	}
	
	for (EyeGhost* Ghosts: m_pEyeghosts)
	{
		delete Ghosts;
		Ghosts = nullptr;
	}
}

void EnemyManager::UpdateSnakes(float elapsedSec, const Rectf& viewport, const Rectf& MovingViewPort)
{
	for (int i = 0; i < m_pSnakes.size(); i++)
	{
		m_pSnakes[i]->Update(elapsedSec, viewport, MovingViewPort);
	}
}

void EnemyManager::UpdateGhosts(float elapsedSec, const Rectf& viewport, const Rectf& MovingViewPort, Player* pPlayer)
{
	for (EyeGhost* ghost : m_pEyeghosts)
	{
		ghost->Update(elapsedSec, viewport, MovingViewPort, pPlayer);
	}
}

void EnemyManager::DrawSnakes(const Rectf& viewport)
{
	for (int i = 0; i < m_pSnakes.size(); i++)
	{
		m_pSnakes[i]->Draw(viewport);
	}
}

void EnemyManager::DrawEyeGhosts()
{
	for (EyeGhost* ghost : m_pEyeghosts)
	{
		ghost->Draw();
	}
}

std::vector<Snake*> EnemyManager::GetSnakes()
{
	return m_pSnakes;
}

std::vector<EyeGhost*> EnemyManager::GetGhosts()
{
	return m_pEyeghosts;
}

void EnemyManager::SetSnakes(std::vector<Snake*> Snakes)
{
	m_pSnakes = Snakes;
}

void EnemyManager::SetGhosts(std::vector<EyeGhost*> Ghosts)
{
	m_pEyeghosts = Ghosts;
}




