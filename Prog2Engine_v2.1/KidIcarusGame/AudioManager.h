#pragma once
#include "SoundStream.h"
#include "SoundEffect.h"

class AudioManager
{
public:
	AudioManager();


	void PlayBackgroundMusic();
	void StopBackgroundMusic();
	void PlayGotHit();
	void PlayJump();
	void PlayShoot();
	void PlayEnemyDeath();
	void PlayItemPickUp();
	void PlayWin();
	void PlayDeath();

private:
	SoundStream m_BackGroundSound;
	SoundEffect m_GotHitSound;
	SoundEffect m_JumpSound;
	SoundEffect m_ShootSound;
	SoundEffect m_EnemyDeathSound;
	SoundEffect m_ItemPickUpSound;
	SoundEffect m_WinningSound;
	SoundEffect m_DeathSound;


};

