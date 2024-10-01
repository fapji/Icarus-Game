#pragma once
#include "Snake.h"
#include "EyeGhost.h"

class EnemyManager
{
public:
	EnemyManager(Rectf viewPort);
	~EnemyManager();

	void UpdateSnakes(float elapsedSec, const Rectf& viewport,const Rectf& MovingViewPort);
	void UpdateGhosts(float elapsedSec, const Rectf& viewport, const Rectf& MovingViewPort, Player* pPlayer);
	void DrawSnakes(const Rectf& viewport);
	void DrawEyeGhosts();

	std::vector<Snake*> GetSnakes();
	std::vector<EyeGhost*> GetGhosts();

	void SetSnakes(std::vector<Snake*> Snakes);
	void SetGhosts(std::vector<EyeGhost*> Ghosts);



private:
	std::vector<Snake*> m_pSnakes;
	std::vector<EyeGhost*> m_pEyeghosts;


};

