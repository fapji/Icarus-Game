#pragma once
#include "Enemy.h"
class EyeGhost : public Enemy
{
public:
	EyeGhost(Point2f StartingPos);
	EyeGhost(float XPos, float YPos);
	~EyeGhost();

	void Update(float elapsedSec, const Rectf& viewport, Rectf MovingViewPort, Player* pPlayer);
	void Draw();

private:
	float m_StalkTimer;
	bool m_TargetHasBeenSet;
};

