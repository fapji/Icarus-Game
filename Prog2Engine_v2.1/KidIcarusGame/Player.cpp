#include "pch.h"
#include "Player.h"
#include "AudioManager.h"
#include <iostream>

Player::Player(AudioManager* pAudioManager)
	: m_TextureColls{ 12 }, m_TextureRows{ 3 }, m_MaxHp{ 7 }, m_pAudioManager{ pAudioManager }
{																												  
	m_pPlayerTexture = new Texture("Player Animations.png");
	m_pArrow = nullptr;


	m_FrameSizeColls = m_pPlayerTexture->GetWidth() / (float)m_TextureColls;
	m_FrameSizeRows = m_pPlayerTexture->GetHeight() / (float)m_TextureRows;


	m_Bounds = Rectf(150, 1850, (float)m_FrameSizeColls * 2, (float)m_FrameSizeRows * 2);
	m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls*14, m_FrameSizeRows*0, m_FrameSizeColls, m_FrameSizeRows);

	m_BoundsThroughWall = Rectf(0, 0, m_Bounds.width, m_Bounds.height);

	m_Velocity = Vector2f(0, -50);


	m_pHpHeart = new Texture("Heart.png");
	m_HpHeartBounds = Rectf(0, 0, m_pHpHeart->GetWidth() * 2, m_pHpHeart->GetHeight() * 2);
	m_HpHeartCurrentFrame = Rectf(0, 0, m_pHpHeart->GetWidth(), m_pHpHeart->GetHeight());
	m_HpSquare = Rectf(0, 0, 10, 10);
	m_Hp = 7;
	m_DamageInvulCounter = 0;
	
	m_Score = 0;

	m_StringTextureColor = Color4f(1, 1, 1, 1);

	m_pDeathMessage = new Texture("Im Finished!", "Lithos-Black Black.ttf", 25, m_StringTextureColor);
	m_pWinScreenMessage = new Texture("Congratulations You Won!", "Lithos-Black Black.ttf", 25, m_StringTextureColor);

	m_DeathScreenCounter = 0;
	m_IsDying = false;
	m_IsWinning = false;
	m_IsDead = false;

	for (size_t i = 0; i < 10; i++)
	{
		m_pNumberTextures.push_back(new Texture(std::to_string(i), "Lithos-Black Black.ttf", 20, m_StringTextureColor));
	}
	m_ScoreChars = std::vector<int>();


	m_TextureTimer = 0; 
	m_TextureXpos = 0;
	m_TextureYpos = 0;

	m_HasDeathsoundBeenPlayed = false;
}

Player::~Player()
{
	delete m_pPlayerTexture;
	m_pPlayerTexture = nullptr;

	delete m_pHpHeart;
	m_pHpHeart = nullptr;

	delete m_pDeathMessage;
	m_pDeathMessage = nullptr;

	delete m_pWinScreenMessage;
	m_pWinScreenMessage = nullptr;

	for (Texture* textures : m_pNumberTextures)
	{
		delete textures;
		textures = nullptr;
	}
}

void Player::Update(float elapsedSec, const Rectf& viewport, const Rectf& MovingViewport)
{
	//std::cout << "X:  " << m_Bounds.left << " Y:  " << m_Bounds.bottom << "\n";
	//Getting Hit Updates
	if (m_IsTakingDamage)
	{
		m_DamageInvulCounter += elapsedSec;
		if (m_DamageInvulCounter >= 2)
		{
			m_IsTakingDamage = false;
			m_DamageInvulCounter = 0;
		}

		m_DamagedCounter += elapsedSec;
		if (m_DamagedCounter >= 0.2)
		{
			m_DamagedCounter = 0;
			if (m_ShowingPlayer)
			{
				m_ShowingPlayer = false;
			}
			else if (!m_ShowingPlayer)
			{
				m_ShowingPlayer = true;
			}
		}
	}
	if (!m_IsTakingDamage && !m_ShowingPlayer)
	{
		m_ShowingPlayer = true;
		m_DamagedCounter = 0;
	}


	//Excucute Movement
	m_Bounds.left += m_Velocity.x * (2 * elapsedSec);
	m_Bounds.bottom += m_Velocity.y * (1.5 * elapsedSec);

	//Animate character
	Animate(elapsedSec);

	//Walking Through wall update
	if (m_Bounds.left < 0)
	{
		m_BoundsThroughWall.bottom = m_Bounds.bottom;
		m_BoundsThroughWall.left = m_Bounds.left + viewport.width;
	}
	if (m_Bounds.left + m_Bounds.width > viewport.width)
	{
		m_BoundsThroughWall.bottom = m_Bounds.bottom;
		m_BoundsThroughWall.left = m_Bounds.left - viewport.width;
	}


	if (m_Bounds.left <= 0 - m_Bounds.width)
	{
		m_Bounds.left = viewport.width - m_Bounds.width;
	}
	if (m_Bounds.left >= viewport.width)
	{
		m_Bounds.left = 0;
	}

	if (m_IsShooting)
	{
		m_ArrowCounter += elapsedSec;
		m_pArrow->update(elapsedSec);
	}
	if (m_ArrowCounter > 0.5 )
	{
		ResetArrow();
		/*delete m_pArrow;
		m_pArrow = nullptr;
		m_IsShooting = false;*/
	}

	if (m_Velocity. y > -200)
	{
		m_Velocity.y -= 200 * elapsedSec;
		if (m_Velocity.y < -200)
		{
			m_Velocity.y = -200;
		}
	}

	//Set Y Position of Hp 
	m_HpSquare.bottom = MovingViewport.bottom + viewport.height / 10 * 9;

	//Set X and Y Of Hp Heart
	m_HpHeartBounds.left = viewport.width / 10;
	m_HpHeartBounds.bottom = MovingViewport.bottom + viewport.height / 10 * 9.25;

	//Check death conditions
	if (m_Bounds.bottom +m_Bounds.height < MovingViewport.bottom)
	{
		m_IsDying = true;
		if (!m_HasDeathsoundBeenPlayed)
		{
			m_pAudioManager->StopBackgroundMusic();
			m_pAudioManager->PlayDeath();
			m_HasDeathsoundBeenPlayed = true;
		}
	}

	if (m_Hp <= 0)
	{
		m_IsDying = true;
		if (!m_HasDeathsoundBeenPlayed)
		{
			m_pAudioManager->StopBackgroundMusic();
			m_pAudioManager->PlayDeath();
			m_HasDeathsoundBeenPlayed = true;
		}
	}

	if (m_IsDying || m_IsWinning)
	{
		m_DeathScreenCounter += elapsedSec;
	}

	if (m_DeathScreenCounter >= 3)
	{
		m_IsDying = false;
		m_IsWinning = false;
		m_IsDead = true;
	}

	//Score display
	const std::string score = std::to_string(m_Score);
	m_ScoreChars.clear();
	if (score.length() < 3)
	{
		const int preZero = 3 - score.length();
		for (size_t i = 0; i < preZero; i++)
		{
			m_ScoreChars.push_back(0);
		}
	}
	for (size_t i = 0; i < score.length(); i++)
	{
		m_ScoreChars.push_back((int)(score[i] - '0'));
	}
	
}


void Player::Animate(float elapsedSec)
{
	//Set currentframe on spritesheet
	switch (m_PlayerState)
	{
	case Player::isNeutral:
		if (m_IsLookingRight)
		{
			if (!m_TouchingGround)
			{
				if (m_IsShooting)
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 4, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
				}
				else
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 4, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
				}
			}
			else
			{
				if (m_IsShooting)
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 0, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
				}
				else
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 0, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
				}
			}
		}
		else
		{
			if (!m_TouchingGround)
			{
				if (m_IsShooting)
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 10, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
				}
				else
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 10, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
				}
			}
			else
			{
				if (m_IsShooting)
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 6, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
				}
				else
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 6, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
				}
			}
		}
		break;

	case Player::isLeft:
		m_Velocity.x = -100;

		m_IsLookingRight = false;
		m_TextureTimer += elapsedSec;

		if (m_TextureTimer >= 0.12)
		{
			++m_TextureXpos;
			m_TextureTimer = 0;
		}
		if (m_TextureXpos > 9)
		{
			m_TextureXpos = 6;
		}

		if (m_TouchingGround)
		{
			if (m_IsShooting)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * m_TextureXpos, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
			}
			else
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * m_TextureXpos, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
			}
		}
		// Jumping
		else
		{
			if (m_IsShooting)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 10, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
			}
			else
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 10, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);

			}
		}
		break;

	case Player::isRight:
		m_Velocity.x = 100;

		m_IsLookingRight = true;
		m_TextureTimer += elapsedSec;

		if (m_TextureTimer >= 0.12)
		{
			++m_TextureXpos;
			m_TextureTimer = 0;
		}
		if (m_TextureXpos > 3)
		{
			m_TextureXpos = 0;
		}

		if (m_TouchingGround)
		{
			if (m_IsShooting)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * m_TextureXpos, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);

			}
			else
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * m_TextureXpos, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
			}
		}
		else
		{
			if (m_IsShooting)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 4, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
			}
			else
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 4, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
			}
		}
		break;

	case Player::isLookingUp:
		if (m_TouchingGround)
		{
			m_Velocity.x = 0;
			if (m_IsLookingRight)
			{
				if (m_IsShooting)
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 5, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
				}
				else
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 5, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
				}
			}
			else if (!m_IsLookingRight)
			{
				if (m_IsShooting)
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 11, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
				}
				else
				{
					m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 11, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
				}
			}
		}
		break;

	case Player::isJumping:
		if (m_IsLookingRight)
		{
			if (m_IsShooting)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 4, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);
			}
			else
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 4, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
			}
		}
		else
		{
			if (m_IsShooting)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 10, m_FrameSizeRows * 1, m_FrameSizeColls, m_FrameSizeRows);

			}
			else
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 10, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);

			}
		}
		break;

	case Player::isCrouching:
		if (m_TouchingGround)
		{
			m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 0, m_FrameSizeRows * 2, m_FrameSizeColls, m_FrameSizeRows);
		}
		break;

	default:
		break;
	}
}

void Player::StartMoving(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		m_Velocity.y = 100;
		break;
	case SDLK_SPACE:
  		if (m_TouchingGround)
		{
			m_Velocity.y = 220;
			m_TouchingGround = false;
			m_PlayerState = isJumping;
			m_pAudioManager->PlayJump();
		}
		break;
	case SDLK_a:
		if (m_PlayerState != isLeft)
		{
			m_TextureXpos = 6;
		}
		m_PlayerState = isLeft;
		break;

	case SDLK_d:
		if (m_PlayerState != isRight)
		{
			m_TextureXpos = 0;
		}
		m_PlayerState = isRight;
		break;
	case SDLK_w:
		m_PlayerState = isLookingUp;
		break;
	case SDLK_s:
		m_PlayerState = isCrouching;
		//crouch
		break;
	default:
		break;
	}
}

void Player::StartShooting(const SDL_KeyboardEvent& e)
{

	switch (e.keysym.sym)
	{
	case SDLK_j:
		if (!m_IsShooting)
		{
			m_IsShooting = true;
			m_ArrowCounter = 0;
			m_pArrow = new Arrow(this, m_IsLookingRight);
			m_pAudioManager->PlayShoot();
		}
	default:
		break;
	}
}

void Player::StopMoving(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_a:
		m_PlayerState = isNeutral;

		m_Velocity.x = 0;
		break;

	case SDLK_d:
		m_PlayerState = isNeutral;

		m_Velocity.x = 0;
		break;
	case SDLK_s:
		m_PlayerState = isNeutral;
		if (m_TouchingGround)
		{
			if (m_IsLookingRight)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 0.f, m_FrameSizeRows * 0.f, m_FrameSizeColls, m_FrameSizeRows);
			}
			else if (!m_IsLookingRight)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 6.f, m_FrameSizeRows * 0.f, m_FrameSizeColls, m_FrameSizeRows);
			}
		}
		break;
	case SDLK_w:
		m_PlayerState = isNeutral;
		if (m_TouchingGround)
		{
			if (m_IsLookingRight)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 0.f, m_FrameSizeRows * 0.f, m_FrameSizeColls, m_FrameSizeRows);
			}
			else if (!m_IsLookingRight)
			{
				m_PlayerTextureCurrentFrame = Rectf(m_FrameSizeColls * 6.f, m_FrameSizeRows * 0.f, m_FrameSizeColls, m_FrameSizeRows);
			}
		}
		break;
	default:
		break;
	}
}

const void Player::Draw(const Rectf& viewport, const Rectf& movingViewport)
{
	//Player draw
	if (m_ShowingPlayer)
	{
		m_pPlayerTexture->Draw(m_Bounds, m_PlayerTextureCurrentFrame);
	}

	// Arrow Draw
	if (m_IsShooting)
	{
		m_pArrow->Draw();
	}

	//through wall draw
	if (m_Bounds.left < 0)
	{
		m_pPlayerTexture->Draw(m_BoundsThroughWall, m_PlayerTextureCurrentFrame);
	}
	if (m_Bounds.left + m_Bounds.width > viewport.width)
	{
		m_pPlayerTexture->Draw(m_BoundsThroughWall, m_PlayerTextureCurrentFrame);
	}
	

	if (m_IsTakingDamage)
	{
		utils::SetColor(Color4f(255, 0, 0, 1));
	}

	//Draw Hp 
	m_pHpHeart->Draw(m_HpHeartBounds, m_HpHeartCurrentFrame);

	for (int i = 0; i < m_MaxHp; i++)
	{
		if (i < m_Hp)
		{
			utils::SetColor(Color4f(0, 255, 0, 0.8));
		}
		else
		{
			utils::SetColor(Color4f(255, 0, 0, 0.8));
		}
		m_HpSquare.left = viewport.width / 10 + 10 * i;
		utils::FillRect(m_HpSquare);
	}

	//Display Score
	for (int i = 0; i < m_ScoreChars.size(); i++)
	{
		m_pNumberTextures[m_ScoreChars[i]]->Draw(Point2f(movingViewport.width / 10 + i * 20 + 20, movingViewport.bottom + viewport.height / 10 * 9.2));
	}


	//hitboxes
	////y
	//utils::SetColor(m_StringTextureColor);
	//utils::DrawLine(	Point2f(m_Bounds.left , m_Bounds.bottom + m_Bounds.height),
	//					Point2f(m_Bounds.left , m_Bounds.bottom ));

	//utils::DrawLine(	Point2f(m_Bounds.left + m_Bounds.width,		m_Bounds.bottom + m_Bounds.height),
	//					Point2f(m_Bounds.left + m_Bounds.width,		m_Bounds.bottom));

	////x
	//utils::DrawLine(	Point2f(m_Bounds.left ,					m_Bounds.bottom + m_Bounds.height),
	//					Point2f(m_Bounds.left + m_Bounds.width , m_Bounds.bottom + m_Bounds.height));
	//
	//utils::DrawLine(	Point2f(m_Bounds.left ,					m_Bounds.bottom),
	//					Point2f(m_Bounds.left + m_Bounds.width , m_Bounds.bottom));

	////lol
	//utils::DrawLine(Point2f(m_Bounds.left , m_Bounds.bottom + m_Bounds.height / 2), 
	//				Point2f(m_Bounds.left + m_Bounds.width , m_Bounds.bottom + m_Bounds.height / 2));

	//// Veloctity vector visualized
	//utils::DrawLine(Point2f(m_Bounds.left, m_Bounds.bottom), Point2f(m_Bounds.left + m_Velocity.x, m_Bounds.bottom + m_Velocity.y));


	

	//Draw Dying Screen
	if (m_IsDying)
	{
		utils::SetColor(Color4f(0, 0, 0, 1));
		utils::FillRect(movingViewport);
		m_pDeathMessage->Draw(Point2f(viewport.width / 2 - 200, movingViewport.bottom + movingViewport.height / 2));
	}
	
	//Draw Win screen
	if (m_IsWinning)
	{
		utils::SetColor(Color4f(0, 0, 0, 1));
		utils::FillRect(movingViewport);
		m_pWinScreenMessage->Draw(Point2f(viewport.width / 2 - 200, movingViewport.bottom + movingViewport.height / 2));
	}
}

void Player::IncrementScore()
{
	++m_Score;
}

void Player::ResetArrow()
{
	delete m_pArrow;
	m_pArrow = nullptr;
	m_IsShooting = false;
}

void Player::TakeDamage()
{
	if (!m_IsTakingDamage)
	{
		m_IsTakingDamage = true;
		--m_Hp;
		m_pAudioManager->PlayGotHit();
	}
}

void Player::SetPosition(Point2f newPos)
{
	m_Bounds.left = newPos.x;
	m_Bounds.bottom = newPos.y;
}

void Player::SetPosition(float left, float bottom)
{
	SetPosition(Point2f(left, bottom));
}

void Player::SetVelocity(Vector2f velocity)
{
	m_Velocity = velocity;
}

void Player::SetTouchingGround(bool IsTouchingGround)
{
	m_TouchingGround = IsTouchingGround;
}

void Player::SetHp(int hp)
{
	m_Hp = hp;
}

void Player::SetWinning(bool isWining)
{
	m_IsWinning = isWining;
}

Point2f Player::GetPosition()
{
	return Point2f(m_Bounds.left, m_Bounds.bottom);
}

float Player::GetWidth()
{
	return m_FrameSizeColls;
}

float Player::GetHeight()
{
	return m_FrameSizeRows;
}

Rectf Player::GetBounds()
{
	return m_Bounds;
}

bool Player::GetIsShooting()
{
	return m_IsShooting;
}

Arrow* Player::GetArrow()
{
	return m_pArrow;
}

Vector2f Player::GetVelocity()
{
	return m_Velocity;
}

bool Player::GetTouchingGround()
{
	return m_TouchingGround;
}

Player::State Player::GetState()
{
	return m_PlayerState;
}

bool Player::GetDying()
{
	return m_IsDying;
}

bool Player::GetDead()
{
	return m_IsDead;
}

void Player::Die()
{
	m_IsDying = true;
}
