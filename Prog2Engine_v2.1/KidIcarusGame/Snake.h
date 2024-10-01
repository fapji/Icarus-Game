#pragma once

#include "Enemy.h"

class Snake : public Enemy
{
public:
	Snake(Point2f StartingPos);
	Snake(float XPos, float YPos);
	~Snake();

	
	void Update(float elapsedSec, const Rectf& viewport, Rectf MovingViewPort);
	void Draw(const Rectf& viewport);

	
	void SetTextureXpos(int xPos);

	
private:
	void Animate(float elapsedSec);
	float m_TextureTimer;
	int m_TextureXpos;


	Rectf m_BoundsThroughWall;
	bool m_TouchingGround;
};

