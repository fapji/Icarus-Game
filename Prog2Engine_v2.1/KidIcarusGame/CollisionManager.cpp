#include "pch.h"
#include "CollisionManager.h"
#include "SnakeDrop.h"
#include <iostream>
#include "GhostDrop.h"

CollisionManager::CollisionManager(Player* pPlayer, std::vector<Snake*> pSnakes, std::vector<EyeGhost*> pGhosts, ItemManager* pItemManager, AudioManager* pAudioManager)
{
	m_pPlayer = pPlayer;
	m_pArrow = nullptr;
	m_pSnakes = pSnakes;
	m_pEyeGhosts = pGhosts;
	m_IsPlayerTouchingGround = false;
	m_IsSnakeLookingRight = false;

	m_pItemManager = pItemManager;
	m_pAudioManager = pAudioManager;
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::AddPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;

}

void CollisionManager::AddSnakes(std::vector<Snake*> pSnakes)
{
	m_pSnakes = pSnakes;
}

void CollisionManager::CheckCollision(const std::vector<std::vector<Point2f>> SolidVertices,const std::vector<std::vector<Point2f>> PassThroughVertices, 
	const std::vector<std::vector<Point2f>> DoorVertices, Camera* pCamera)
{
	//Player
	m_PlayerBounds = m_pPlayer->GetBounds();
	m_PlayerVelocity = m_pPlayer->GetVelocity();
	m_IsPlayerTouchingGround = m_pPlayer->GetTouchingGround();

	if (m_pPlayer->GetIsShooting() == true)
	{
		m_pArrow = m_pPlayer->GetArrow();
	}


	//Door Collisions
	for (std::vector<Point2f> DoorVertex : DoorVertices)
	{
		if (utils::Raycast(DoorVertex, Point2f(m_PlayerBounds.left - 3, m_PlayerBounds.bottom + m_PlayerBounds.height / 2),
				Point2f(m_PlayerBounds.left + 3 + m_PlayerBounds.width, m_PlayerBounds.bottom + m_PlayerBounds.height / 2), m_HitInfo))
		{
			//Winning Door
			int playerY = m_pPlayer->GetPosition().y;
			if (playerY > 9990)
			{
				m_pAudioManager->StopBackgroundMusic();
				m_pPlayer->SetWinning(true);
				m_pAudioManager->PlayWin();
			}
			//Teleporting doors
			//Set 1
			//in
			if (playerY > 2500 && playerY < 2680)
			{
				m_pPlayer->SetPosition(Point2f(620, 1200));
				pCamera->SetMovingViewport(Rectf(0, m_pPlayer->GetPosition().y - 230, pCamera->GetMovingViewport().width, pCamera->GetMovingViewport().height));
				m_PlayerBounds = m_pPlayer->GetBounds();
			}
			//back
			if (playerY > 1170 && playerY < 1300)
			{
				m_pPlayer->SetPosition(Point2f(600, 2530));
				pCamera->SetMovingViewport(Rectf(0, m_pPlayer->GetPosition().y - 200, pCamera->GetMovingViewport().width, pCamera->GetMovingViewport().height));
				m_PlayerBounds = m_pPlayer->GetBounds();
			}

			//Set 2
			//in
			if (playerY > 6300 && playerY < 6500)
			{
				m_pPlayer->SetPosition(Point2f(615, 480));
				pCamera->SetMovingViewport(Rectf(0, m_pPlayer->GetPosition().y - 250, pCamera->GetMovingViewport().width, pCamera->GetMovingViewport().height));
				m_PlayerBounds = m_pPlayer->GetBounds();
			}
			//back
			if (playerY > 450 && playerY < 600)
			{
				m_pPlayer->SetPosition(Point2f(75, 6360));
				pCamera->SetMovingViewport(Rectf(0, m_pPlayer->GetPosition().y - 250, pCamera->GetMovingViewport().width, pCamera->GetMovingViewport().height));
				m_PlayerBounds = m_pPlayer->GetBounds();
			}
		}
	}


	//Solid Collision
	bool DidTouchY{ false };
	for (std::vector<Point2f> SolidVertices : SolidVertices)
	{

		//y
		if (utils::Raycast(SolidVertices, Point2f(m_PlayerBounds.left, m_PlayerBounds.bottom + m_PlayerBounds.height + 5),
			Point2f(m_PlayerBounds.left, m_PlayerBounds.bottom - 3), m_HitInfo)
			|| utils::Raycast(SolidVertices, Point2f(m_PlayerBounds.left + m_PlayerBounds.width, m_PlayerBounds.bottom + m_PlayerBounds.height + 5),
				Point2f(m_PlayerBounds.left + m_PlayerBounds.width, m_PlayerBounds.bottom - 3), m_HitInfo))
		{
			DidTouchY = true;
			if (m_PlayerBounds.bottom + m_PlayerBounds.height - 10 <= m_HitInfo.intersectPoint.y)
			{
				m_PlayerBounds.bottom = m_HitInfo.intersectPoint.y - m_PlayerBounds.height - 5;
				m_PlayerVelocity.y = 0;
			}
			else if (m_PlayerBounds.bottom + 10 > m_HitInfo.intersectPoint.y && !m_IsPlayerTouchingGround)
			{
				m_IsPlayerTouchingGround = true;
				m_PlayerBounds.bottom = m_HitInfo.intersectPoint.y + 2;
				m_PlayerVelocity.y = 0;
			}
		}
		else if (!DidTouchY)
		{
			m_IsPlayerTouchingGround = false;
		}


		//x
		if (utils::Raycast(SolidVertices, Point2f(m_PlayerBounds.left - 3, m_PlayerBounds.bottom + m_PlayerBounds.height),
			Point2f(m_PlayerBounds.left + 3 + m_PlayerBounds.width, m_PlayerBounds.bottom + m_PlayerBounds.height), m_HitInfo) ||
			utils::Raycast(SolidVertices, Point2f(m_PlayerBounds.left - 3, m_PlayerBounds.bottom),
				Point2f(m_PlayerBounds.left + 3 + m_PlayerBounds.width, m_PlayerBounds.bottom), m_HitInfo) ||
			utils::Raycast(SolidVertices, Point2f(m_PlayerBounds.left - 3, m_PlayerBounds.bottom + m_PlayerBounds.height / 2),
				Point2f(m_PlayerBounds.left + 3 + m_PlayerBounds.width, m_PlayerBounds.bottom + m_PlayerBounds.height / 2), m_HitInfo))
		{
			if (m_HitInfo.intersectPoint.x < m_PlayerBounds.left + 10)
			{
				m_PlayerBounds.left = m_HitInfo.intersectPoint.x + 4;
				m_PlayerVelocity.x = 0;
			}
			else if (m_HitInfo.intersectPoint.x > m_PlayerBounds.left + m_PlayerBounds.width - 10)
			{
				m_PlayerBounds.left = m_HitInfo.intersectPoint.x - m_PlayerBounds.width - 4;
				m_PlayerVelocity.x = 0;
			}
		}
	}

	//Pass Through Collision
	for (std::vector<Point2f> PassThroughVertices : PassThroughVertices)
	{
		if (utils::Raycast(PassThroughVertices, Point2f(m_PlayerBounds.left, m_PlayerBounds.bottom + m_PlayerBounds.height + 5),
			Point2f(m_PlayerBounds.left, m_PlayerBounds.bottom - 3), m_HitInfo)
			|| utils::Raycast(PassThroughVertices, Point2f(m_PlayerBounds.left + m_PlayerBounds.width, m_PlayerBounds.bottom + m_PlayerBounds.height + 5),
				Point2f(m_PlayerBounds.left + m_PlayerBounds.width, m_PlayerBounds.bottom - 3), m_HitInfo))
		{
			if (m_PlayerBounds.bottom + 10 > m_HitInfo.intersectPoint.y && !m_IsPlayerTouchingGround)
			{
				m_IsPlayerTouchingGround = true;
				m_PlayerBounds.bottom = m_HitInfo.intersectPoint.y + 2;
				m_PlayerVelocity.y = 0;
			}
		}
	}
	
	m_pPlayer->SetPosition(m_PlayerBounds.left, m_PlayerBounds.bottom);
	m_pPlayer->SetVelocity(m_PlayerVelocity);
	m_pPlayer->SetTouchingGround(m_IsPlayerTouchingGround);


	//Snakes
	//Wall Collision
	for (Snake* snakes : m_pSnakes)
	{
		if (snakes->GetIsActivated())
		{
			m_SnakeBounds = snakes->GetBounds();
			m_IsSnakeLookingRight = snakes->GetLookingRight();

			//Solid Collision
			for (std::vector<Point2f> SolidVertices : SolidVertices)
			{

				//y
				if (utils::Raycast(SolidVertices, Point2f(m_SnakeBounds.left, m_SnakeBounds.bottom + m_SnakeBounds.height + 5),
					Point2f(m_SnakeBounds.left, m_SnakeBounds.bottom - 3), m_HitInfo)
					|| utils::Raycast(SolidVertices, Point2f(m_SnakeBounds.left + m_SnakeBounds.width, m_SnakeBounds.bottom + m_SnakeBounds.height + 5),
						Point2f(m_SnakeBounds.left + m_SnakeBounds.width, m_SnakeBounds.bottom - 3), m_HitInfo))
				{
					if (m_SnakeBounds.bottom + m_SnakeBounds.height - 10 <= m_HitInfo.intersectPoint.y)
					{
						m_SnakeBounds.bottom = m_HitInfo.intersectPoint.y - m_SnakeBounds.height - 5;
					}
					else if (m_SnakeBounds.bottom + 10 > m_HitInfo.intersectPoint.y)
					{
						m_SnakeBounds.bottom = m_HitInfo.intersectPoint.y + 2;
					}
				}

				//x
				if (utils::Raycast(SolidVertices, Point2f(m_SnakeBounds.left - 3, m_SnakeBounds.bottom + m_SnakeBounds.height),
					Point2f(m_SnakeBounds.left + 3 + m_SnakeBounds.width, m_SnakeBounds.bottom + m_SnakeBounds.height), m_HitInfo) ||
					utils::Raycast(SolidVertices, Point2f(m_SnakeBounds.left - 3, m_SnakeBounds.bottom),
						Point2f(m_SnakeBounds.left + 3 + m_SnakeBounds.width, m_SnakeBounds.bottom), m_HitInfo) ||
					utils::Raycast(SolidVertices, Point2f(m_SnakeBounds.left - 3, m_SnakeBounds.bottom + m_SnakeBounds.height / 2),
						Point2f(m_SnakeBounds.left + 3 + m_SnakeBounds.width, m_SnakeBounds.bottom + m_SnakeBounds.height / 2), m_HitInfo))
				{
					if (m_HitInfo.intersectPoint.x < m_SnakeBounds.left + 10)
					{
						m_SnakeBounds.left = m_HitInfo.intersectPoint.x + 4;
						m_IsSnakeLookingRight = true;
						snakes->SetTextureXpos(0);
					}
					else if (m_HitInfo.intersectPoint.x > m_SnakeBounds.left + m_SnakeBounds.width - 10)
					{
						m_SnakeBounds.left = m_HitInfo.intersectPoint.x - m_SnakeBounds.width - 4;
						m_IsSnakeLookingRight = false;
						snakes->SetTextureXpos(2);
					}
				}

			}

			//Pass Through Collision
			for (std::vector<Point2f> PassThroughVertices : PassThroughVertices)
			{

				//y
				if (utils::Raycast(PassThroughVertices, Point2f(m_SnakeBounds.left, m_SnakeBounds.bottom + m_SnakeBounds.height + 5),
					Point2f(m_SnakeBounds.left, m_SnakeBounds.bottom - 3), m_HitInfo)
					|| utils::Raycast(PassThroughVertices, Point2f(m_SnakeBounds.left + m_SnakeBounds.width, m_SnakeBounds.bottom + m_SnakeBounds.height + 5),
						Point2f(m_SnakeBounds.left + m_SnakeBounds.width, m_SnakeBounds.bottom - 3), m_HitInfo))
				{
					if (m_SnakeBounds.bottom + 10 > m_HitInfo.intersectPoint.y)
					{
						m_SnakeBounds.bottom = m_HitInfo.intersectPoint.y + 2;
					}
				}

			}




			snakes->SetPosition(Point2f(m_SnakeBounds.left, m_SnakeBounds.bottom));
			snakes->SetLookingRight(m_IsSnakeLookingRight);



			//Check if Snake Hit By arrow
			if (m_pPlayer->GetIsShooting() == true)
			{
				if (utils::IsOverlapping(m_pArrow->GetBounds(), m_SnakeBounds))
				{
					Point2f snakePos{ m_SnakeBounds.left + m_SnakeBounds.width / 2,m_SnakeBounds.bottom + m_SnakeBounds.height / 2 };
					SnakeDrop* drop = new SnakeDrop(snakePos);
					m_pItemManager->AddItem(drop);
					snakes->Kill();
					m_pPlayer->ResetArrow();
					m_pAudioManager->PlayEnemyDeath();

				}
			}


			//Check if Player Hits Enemy Snake
			if (utils::IsOverlapping(m_PlayerBounds, m_SnakeBounds))
			{
				m_pPlayer->TakeDamage();
			}
		}
	}
	
	//Ghosts
	for (EyeGhost* ghost : m_pEyeGhosts)
	{
		m_GhostBounds = ghost->GetBounds();


		if (m_pPlayer->GetIsShooting() == true)
		{
			if (utils::IsOverlapping(m_pArrow->GetBounds(), m_GhostBounds))
			{
				Point2f ghostPos{ m_GhostBounds.left + m_GhostBounds.width / 2,m_GhostBounds.bottom + m_GhostBounds.height / 2 };
				GhostDrop* drop = new GhostDrop(ghostPos);
				m_pItemManager->AddItem(drop);
				ghost->Kill();
				m_pPlayer->ResetArrow();
				m_pAudioManager->PlayEnemyDeath();
			}
		}


		//Check if Player Hits Enemy Snake
		if (utils::IsOverlapping(m_PlayerBounds, m_GhostBounds))
		{
			m_pPlayer->TakeDamage();
		}
	}
	


	//Check If Player Hits an Item
	for (int i = 0; i < m_pItemManager->GetScoreItems().size(); i++)
	{
		if (m_pItemManager->GetScoreItems().at(i) != nullptr)
		{
			if (utils::IsOverlapping(m_PlayerBounds, m_pItemManager->GetScoreItems().at(i)->GetBounds()))
			{
				m_pItemManager->RemoveScoreItem(i);
				m_pPlayer->IncrementScore();
				m_pAudioManager->PlayItemPickUp();
			}
		}
	}
	if (m_pItemManager->GetHpItem() != nullptr)
	{
		if (utils::IsOverlapping(m_PlayerBounds, m_pItemManager->GetHpItem()->GetBounds()))
		{
			m_pItemManager->RemoveHpItem();
			m_pPlayer->SetHp(7);
			m_pAudioManager->PlayItemPickUp();
		}
	}
}
