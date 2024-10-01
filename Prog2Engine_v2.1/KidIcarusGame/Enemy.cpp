#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(std::string ImagePath, Rectf PosAndSize, int TextureColumnAmount, int TextureRowAmount)
	: m_TextureColls{ TextureColumnAmount }, m_TextureRows{ TextureRowAmount }, m_SpawningBounds{ PosAndSize }
{
	m_pEnemyTexture = new Texture(ImagePath);

	m_FrameSizeColls = m_pEnemyTexture->GetWidth() / (float)m_TextureColls;
	m_FrameSizeRows = m_pEnemyTexture->GetHeight() / (float)m_TextureRows;

	m_Bounds = Rectf(PosAndSize);
	m_TextureCurrentFrame = Rectf(0, 0, m_FrameSizeColls, m_FrameSizeRows);

	m_Velocity = Vector2f(0, 0);
	m_IsLookingRight = true;
	m_IsActivated = false;

	m_IsDead = false;
	m_RespawnCounter = 0;
}

Enemy::~Enemy()
{
	delete m_pEnemyTexture;
	m_pEnemyTexture = nullptr;
}

void Enemy::Kill()
{
	m_IsDead = true;
	m_RespawnCounter = 0;
	m_Bounds = Rectf();
}

Rectf Enemy::GetBounds()
{
	return m_Bounds;
}

Vector2f Enemy::GetVelocity()
{
	return m_Velocity;
}

bool Enemy::GetLookingRight()
{
	return m_IsLookingRight;
}

bool Enemy::GetIsActivated()
{
	return m_IsActivated;
}

void Enemy::SetPosition(Point2f Position)
{
	m_Bounds.left = Position.x;
	m_Bounds.bottom = Position.y;
}

void Enemy::SetVeloctity(Vector2f Velocity)
{
	m_Velocity = Velocity;
}

void Enemy::SetLookingRight(bool LookingRight)
{
	m_IsLookingRight = LookingRight;
}

void Enemy::Activate(Rectf MovingViewPort)
{
	if (m_Bounds.bottom + m_Bounds.height > MovingViewPort.bottom && m_Bounds.bottom < MovingViewPort.bottom + MovingViewPort.height)
	{
		m_IsActivated = true;
	}
	else
	{
		m_IsActivated = false;
	}
}
