#pragma once
#include "Texture.h"
#include "utils.h"

#include "Player.h"

class Enemy
{

public:
Enemy(std::string ImagePath, Rectf PosAndSize, int TextureColumnAmount, int TextureRowAmount);
~Enemy();

void Kill();

Rectf GetBounds();
Vector2f GetVelocity();
bool GetLookingRight();
bool GetIsActivated();

void SetPosition(Point2f Position);
void SetVeloctity(Vector2f Velocity);
void SetLookingRight(bool LookingRight);

protected:
void Activate(Rectf MovingViewPort);
Texture* m_pEnemyTexture;

// Both Enemies Have the Same Size 
const int m_TextureColls;
const int m_TextureRows;
int m_FrameSizeColls;
int	m_FrameSizeRows;

const Rectf m_SpawningBounds;
Rectf m_Bounds;
Rectf m_TextureCurrentFrame{};

Vector2f m_Velocity;

bool m_IsLookingRight;
bool m_IsActivated;

bool m_IsDead;
float m_RespawnCounter;

};

