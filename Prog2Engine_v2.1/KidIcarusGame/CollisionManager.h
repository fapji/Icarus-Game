#pragma once
#include <vector>
#include "Player.h"
#include "Arrow.h"
#include "Snake.h"
#include "EyeGhost.h"
#include "utils.h"
#include "ItemManager.h"
#include "AudioManager.h"
#include "Camera.h"

class CollisionManager
{
public:
	CollisionManager(Player* pPlayer, std::vector<Snake*> pSnakes, std::vector<EyeGhost*> pGhosts, ItemManager* pItemManager, AudioManager* pAudioManager);
	~CollisionManager();

	void AddPlayer(Player* pPlayer);
	void AddSnakes(std::vector<Snake*> pSnakes);

	void CheckCollision(const std::vector<std::vector<Point2f>> SolidVertices, const std::vector<std::vector<Point2f>> PassThroughVertices,
		const std::vector<std::vector<Point2f>> DoorVertices, Camera* pCamera);

private:
	std::vector<std::vector<Point2f>> m_Solidvertices;
	std::vector<std::vector<Point2f>> m_vertices;

	utils::HitInfo m_HitInfo;


	Player* m_pPlayer;
	Rectf m_PlayerBounds;
	Vector2f m_PlayerVelocity;
	bool m_IsPlayerTouchingGround;

	Arrow* m_pArrow;
	Rectf m_ArrowBounds;


	std::vector<Snake*> m_pSnakes;
	Rectf m_SnakeBounds;
	bool m_IsSnakeLookingRight;
	bool m_SnakeFallingStraight;
	
	std::vector<EyeGhost*> m_pEyeGhosts;
	Rectf m_GhostBounds;

	ItemManager* m_pItemManager;
	AudioManager* m_pAudioManager;
};

