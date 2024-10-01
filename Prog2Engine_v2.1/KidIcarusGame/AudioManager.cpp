#include "pch.h"
#include "AudioManager.h"

AudioManager::AudioManager()
	:m_BackGroundSound{ "StageMusicOST.mp3" },m_GotHitSound{"GotHit.mp3"}, m_JumpSound{"Jump.mp3"}, m_ShootSound{"Shoot.mp3"},
	m_EnemyDeathSound{"EnemyDeath.mp3"}, m_ItemPickUpSound{"ItemPickUp.mp3"}, m_WinningSound{"WiningDoor.mp3"}, m_DeathSound{"Death.mp3"}
{
	
}


void AudioManager::PlayBackgroundMusic()
{
	m_BackGroundSound.SetVolume(50);
	m_BackGroundSound.Play(true);
}

void AudioManager::StopBackgroundMusic()
{
	m_BackGroundSound.Stop();
}

void AudioManager::PlayGotHit()
{
	m_GotHitSound.SetVolume(50);
	m_GotHitSound.Play(false);
}

void AudioManager::PlayJump()
{
	m_JumpSound.SetVolume(50);
	m_JumpSound.Play(false);
}

void AudioManager::PlayShoot()
{
	m_ShootSound.SetVolume(50);
	m_ShootSound.Play(false);
}

void AudioManager::PlayEnemyDeath()
{
	m_EnemyDeathSound.SetVolume(50);
	m_EnemyDeathSound.Play(false);
}

void AudioManager::PlayItemPickUp()
{
	m_ItemPickUpSound.SetVolume(50);
	m_ItemPickUpSound.Play(false);
}

void AudioManager::PlayWin()
{
	m_WinningSound.SetVolume(10);
	m_WinningSound.Play(false);
}

void AudioManager::PlayDeath()
{
	m_DeathSound.SetVolume(50);
	m_DeathSound.Play(false);
}



