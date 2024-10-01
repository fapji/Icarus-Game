#include "pch.h"
#include "Snake.h"

Snake::Snake(Point2f StartingPos)
	: Enemy("snake.png", Rectf(StartingPos.x, StartingPos.y , 0, 0), 4, 1)
{
	m_Bounds.width = m_pEnemyTexture->GetWidth();
	m_Bounds.height = m_pEnemyTexture->GetHeight() * 2;

	m_BoundsThroughWall = Rectf(0, 0, m_Bounds.width, m_Bounds.height);

	m_Velocity = Vector2f(0, 0);

	m_TextureTimer = 0;
	m_TextureXpos = 2;

	m_TouchingGround = false;
}

Snake::Snake(float XPos, float YPos)
	: Snake(Point2f(XPos, YPos))
{
	
}

Snake::~Snake()
{
	
}

void Snake::Update(float elapsedSec, const Rectf& viewport, Rectf MovingViewPort)
{
	if (m_IsDead)
	{
		m_RespawnCounter += elapsedSec;

		if (m_RespawnCounter >= 16)
		{
			m_Bounds = m_SpawningBounds;
			m_Bounds.width = m_pEnemyTexture->GetWidth();
			m_Bounds.height = m_pEnemyTexture->GetHeight() * 2;
			m_IsDead = false;
		}
	}

	Activate(MovingViewPort);
	if (m_IsActivated)
	{
		//Update Snake Speed
		m_Bounds.left += m_Velocity.x * (1 * elapsedSec);
		m_Bounds.bottom += m_Velocity.y * (1 * elapsedSec);

		//Set Snake X Speed
		if (m_IsLookingRight)
		{
			m_Velocity.x = 90;
		}
		else
		{
			m_Velocity.x = -90;
		}
		
		

		//Apply gravity (Y Speed)
		if (m_Velocity.y > -100)
		{
			m_Velocity.y -= 100 * elapsedSec;
			if (m_Velocity.y < -100)
			{
				m_Velocity.y = -100;
			}
		}

		//Check if Snake is through Wall
		//Walking Through wall update
		if (m_Bounds.left < 0)
		{
			m_BoundsThroughWall.bottom = m_Bounds.bottom;
			m_BoundsThroughWall.left = m_Bounds.left + viewport.width;
		}
		else if (m_Bounds.left + m_Bounds.width > viewport.width)
		{
			m_BoundsThroughWall.bottom = m_Bounds.bottom;
			m_BoundsThroughWall.left = m_Bounds.left - viewport.width;
		}

		if (m_Bounds.left <= 0 - m_Bounds.width)
		{
			m_Bounds.left = viewport.width - m_Bounds.width;
		}
		else if (m_Bounds.left >= viewport.width)
		{
			m_Bounds.left = 0;
		}

		Animate(elapsedSec);
	}
}


void Snake::Draw(const Rectf& viewport)
{
	if (m_IsActivated)
	{
		m_pEnemyTexture->Draw(m_Bounds, m_TextureCurrentFrame);



		if (m_Bounds.left < 0)
		{
			m_pEnemyTexture->Draw(m_BoundsThroughWall, m_TextureCurrentFrame);
		}
		if (m_Bounds.left + m_Bounds.width > viewport.width)
		{
			m_pEnemyTexture->Draw(m_BoundsThroughWall, m_TextureCurrentFrame);
		}
	}

}

void Snake::SetTextureXpos(int xPos)
{
	m_TextureXpos = xPos;
}

void Snake::Animate(float elapsedSec)
{
	m_TextureTimer += elapsedSec;
	if (m_TextureTimer > 0.15)
	{
		++m_TextureXpos;
		m_TextureTimer = 0;
	}
	if (m_IsLookingRight)
	{
		if (m_TextureXpos > 1)
		{
			m_TextureXpos = 0;
		}
		m_TextureCurrentFrame.left = m_FrameSizeColls * m_TextureXpos;
	}
	else
	{
		if (m_TextureXpos > 3)
		{
			m_TextureXpos = 2;
		}
		m_TextureCurrentFrame.left = m_FrameSizeColls * m_TextureXpos;
	}
}


