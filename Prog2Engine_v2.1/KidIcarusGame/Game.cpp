#include "pch.h"
#include "Game.h"
#include <iostream>
#include <iostream>
#include "SnakeDrop.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pEnemyManager = new EnemyManager(GetViewPort());
	
	m_pAudioManager = new AudioManager();
	m_pAudioManager->PlayBackgroundMusic();

	m_pItemManager = new ItemManager();

	m_pPlayer = new Player(m_pAudioManager);

	m_pCollisionManager = new CollisionManager(m_pPlayer, m_pEnemyManager->GetSnakes(),m_pEnemyManager->GetGhosts(), m_pItemManager, m_pAudioManager);
	//m_pCollisionManager->AddPlayer(m_pPlayer);
	//m_pCollisionManager->AddSnakes(m_pEnemyManager->GetSnakes());

	m_pWorld = new World();
	m_pCamera = new Camera(GetViewPort().width, GetViewPort().height, m_pPlayer->GetPosition());


	SVGParser::GetVerticesFromSvgFile("solid.svg", m_SolidVertices);
	SVGParser::GetVerticesFromSvgFile("platform.svg", m_PassThroughVertices);
	SVGParser::GetVerticesFromSvgFile("doors.svg", m_DoorVertices);
}

void Game::Cleanup( )
{
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pWorld;
	m_pWorld = nullptr;

	delete m_pAudioManager;
	m_pAudioManager = nullptr;

	delete m_pCamera;
	m_pCamera = nullptr;

	delete m_pEnemyManager;
	m_pEnemyManager = nullptr;

	delete m_pCollisionManager;
	m_pCollisionManager = nullptr;

	delete m_pItemManager;
	m_pItemManager = nullptr;
	
	m_SolidVertices.clear();
	m_PassThroughVertices.clear();
	m_DoorVertices.clear();
}

void Game::Update( float elapsedSec )
{

	m_pPlayer->Update(elapsedSec, GetViewPort(), m_pCamera->GetMovingViewport());

	m_pCollisionManager->CheckCollision(m_SolidVertices, m_PassThroughVertices, m_DoorVertices, m_pCamera);

	m_pEnemyManager->UpdateSnakes(elapsedSec, GetViewPort(), m_pCamera->GetMovingViewport());
	m_pEnemyManager->UpdateGhosts(elapsedSec, GetViewPort(), m_pCamera->GetMovingViewport(), m_pPlayer);


	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}


	if (m_pPlayer->GetDead())
	{
		Cleanup();
		Initialize();
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	m_pCamera->Aim(m_pPlayer->GetPosition());

	m_pWorld->Draw(m_SolidVertices, m_PassThroughVertices, m_DoorVertices);

	m_pEnemyManager->DrawSnakes(GetViewPort());
	m_pEnemyManager->DrawEyeGhosts();

	m_pItemManager->Draw();

	m_pPlayer->Draw(GetViewPort(), m_pCamera->GetMovingViewport());

	m_pCamera->Reset();

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->StartMoving(e);
	m_pPlayer->StartShooting(e);

	
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->StopMoving(e);


	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
