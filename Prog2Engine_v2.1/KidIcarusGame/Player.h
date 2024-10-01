#pragma once
#include "Texture.h"
#include "utils.h"
#include "Arrow.h"
class AudioManager;

class Player
{
public:
	enum State
	{
		isNeutral,
		isLeft,
		isRight,
		isLookingUp,
		isCrouching,
		isJumping
	};

	Player(AudioManager* pAudioManager);
	~Player();

	void Update(float elapsedSec,const Rectf& viewport, const Rectf& MovingViewport);

	void StartMoving(const SDL_KeyboardEvent& e);
	void StartShooting(const SDL_KeyboardEvent& e);
	void StopMoving(const SDL_KeyboardEvent& e);

	const void Draw(const Rectf& viewport, const Rectf& movingViewport);
	
	void IncrementScore();

	void ResetArrow();
	void TakeDamage();

	void SetPosition(Point2f newPos);
	void SetPosition(float left, float bottom);

	void SetVelocity(Vector2f velocity);

	void SetTouchingGround(bool IsTouchingGround);

	void SetHp(int hp);

	void SetWinning(bool isWining);

	Point2f GetPosition();
	float GetWidth();
	float GetHeight();
	Rectf GetBounds();
	bool GetIsShooting();
	Arrow* GetArrow();

	Vector2f GetVelocity();

	bool GetTouchingGround();

	State GetState();

	bool GetDying();
	bool GetDead();

protected:
	Texture* m_pPlayerTexture;
	Arrow* m_pArrow;

	Rectf m_Bounds;
	Rectf m_BoundsThroughWall;
	Rectf m_PlayerTextureCurrentFrame;



	const int m_TextureColls;
	const int m_TextureRows;
	int m_FrameSizeColls;
	int	m_FrameSizeRows;


	
	Vector2f m_Velocity;
	Vector2f m_ArrowVelocity{ 0 ,0 };
	float m_ArrowCounter{ 0 };

	const int m_MaxHp;
	int m_Hp;
	Texture* m_pHpHeart;
	Rectf m_HpHeartBounds;
	Rectf m_HpHeartCurrentFrame;

	Rectf m_HpSquare;
	float m_DamageInvulCounter;

	State m_PlayerState{isNeutral};
	bool m_IsLookingRight{ true };
	bool m_TouchingGround{ false };
	bool m_IsShooting{ false };
	bool m_IsTakingDamage{ false };
	bool m_ShowingPlayer{ true };
	float m_DamagedCounter{};
	
private:
	void Animate(float elapsedSec);
	float m_TextureTimer;
	int m_TextureXpos;
	int m_TextureYpos;

	int m_Score;

	void Die();
	
	Texture* m_pDeathMessage;
	bool m_IsDying;
	bool m_HasDeathsoundBeenPlayed;

	Texture* m_pWinScreenMessage;
	bool m_IsWinning;

	float m_DeathScreenCounter;
	bool m_IsDead;


	AudioManager* m_pAudioManager;

	Color4f m_StringTextureColor;
	std::vector<Texture*> m_pNumberTextures;
	std::vector<int> m_ScoreChars;

};

