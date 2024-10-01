#pragma once
#include "BaseGame.h"

#include "Player.h"
#include "Snake.h"

#include "World.h"
#include "Camera.h"

#include "SVGParser.h"

#include "EnemyManager.h"
#include "CollisionManager.h"
#include "AudioManager.h"
#include "ItemManager.h"



class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;



	Player* m_pPlayer;
	World* m_pWorld;
	Camera* m_pCamera;

	std::vector<std::vector<Point2f>> m_SolidVertices;
	std::vector<std::vector<Point2f>> m_PassThroughVertices;
	std::vector<std::vector<Point2f>> m_DoorVertices;


	EnemyManager* m_pEnemyManager;
	CollisionManager* m_pCollisionManager;
	AudioManager* m_pAudioManager;
	ItemManager* m_pItemManager;
};