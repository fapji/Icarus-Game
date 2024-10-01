#include "pch.h"
#include "EyeGhost.h"

EyeGhost::EyeGhost(Point2f StartingPos)
	: Enemy("Ghost.png", Rectf(StartingPos.x, StartingPos.y, 0, 0), 2, 1)
{
	m_Bounds.width = m_pEnemyTexture->GetWidth()*1.5;
	m_Bounds.height = m_pEnemyTexture->GetHeight() * 3;

	m_StalkTimer = (float)(rand() % 3 + 4);
	m_TargetHasBeenSet = false;
}


EyeGhost::EyeGhost(float XPos, float YPos)
	:EyeGhost(Point2f(XPos, YPos))
{

}

EyeGhost::~EyeGhost()
{

}

void EyeGhost::Update(float elapsedSec, const Rectf& viewport, Rectf MovingViewPort, Player* pPlayer)
{
	if (m_IsDead)
	{
		m_RespawnCounter += elapsedSec;

		if (m_RespawnCounter >= 10)
		{
			m_Bounds = m_SpawningBounds;
			m_Bounds.width = m_pEnemyTexture->GetWidth()*1.5;
			m_Bounds.height = m_pEnemyTexture->GetHeight() * 3;
			m_IsDead = false;
			m_StalkTimer = (float)(rand() % 3 + 4);
			m_TargetHasBeenSet = false;
		}
	}

	Activate(MovingViewPort);
	if (m_IsActivated)
	{
		//Observe before attacking
		if (m_StalkTimer >0)
		{
			m_StalkTimer -= elapsedSec;
		}
		if (m_StalkTimer <= 0)
		{
			if (!m_TargetHasBeenSet)
			{
				m_Velocity = Vector2f(Point2f(m_Bounds.left, m_Bounds.bottom), Point2f(pPlayer->GetPosition().x, pPlayer->GetPosition().y + (float)(rand() % 101)));
				m_Velocity = m_Velocity.Normalized();
				m_Velocity *= 200;
				
				m_TargetHasBeenSet = true;
			}

			//Set position
			m_Bounds.left += m_Velocity.x * elapsedSec;
			m_Bounds.bottom += m_Velocity.y * elapsedSec;

			//Check if hitting screen boundry
			if (m_Bounds.left < 0)
			{
				m_Bounds.left = 1;
				m_StalkTimer = (float)(rand() % 4 + 2);
				m_TargetHasBeenSet = false;
			}
			if (m_Bounds.left > viewport.width - m_Bounds.width)
			{
				m_Bounds.left = viewport.width - m_Bounds.width - 1;
				m_StalkTimer = (float)(rand() % 4 + 2);
				m_TargetHasBeenSet = false;
			}

			//Set Image
			if (m_Velocity.x > 0)
			{
				m_TextureCurrentFrame.left = m_FrameSizeColls;
			}
			else
			{
				m_TextureCurrentFrame.left = 0;
			}
		}
	}
}

void EyeGhost::Draw()
{
	if (m_IsActivated)
	{
		m_pEnemyTexture->Draw(m_Bounds, m_TextureCurrentFrame);
	}
}
