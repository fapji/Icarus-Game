#include "pch.h"
#include "Arrow.h"
#include "Player.h"

Arrow::Arrow(Player* pPlayer, bool LookingRight)
{
	m_pArrowTexture = new Texture("arrow.png");
	

	m_FrameSizeColls = m_pArrowTexture->GetWidth() / (float)m_TextureColls;
	m_FrameSizeRows = m_pArrowTexture->GetHeight();


	if (pPlayer->GetState() == Player::State::isLookingUp)
	{
		m_Velocity = Vector2f(0, m_ArrowSpeed);
		m_ArrowTextureCurrentFrame = Rectf(m_FrameSizeColls * 2, m_FrameSizeColls * 0, m_FrameSizeColls, m_FrameSizeRows);
	}
	else if (LookingRight)
	{
		m_Velocity = Vector2f(m_ArrowSpeed, 0);
		m_ArrowTextureCurrentFrame = Rectf(m_FrameSizeColls * 0, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
	}
	else if (!LookingRight)
	{
		m_Velocity = Vector2f(-m_ArrowSpeed, 0);
		m_ArrowTextureCurrentFrame = Rectf(m_FrameSizeColls, m_FrameSizeRows * 0, m_FrameSizeColls, m_FrameSizeRows);
	}
	

	


	m_Bounds = Rectf(pPlayer->GetPosition().x + pPlayer->GetWidth() / 2, 
					pPlayer->GetPosition().y + pPlayer->GetHeight() / 2, (float)m_FrameSizeColls * 2, (float)m_FrameSizeRows * 2);

}

Arrow::~Arrow()
{
	delete m_pArrowTexture;
	m_pArrowTexture = nullptr;
}

void Arrow::update(float elapsedSec)
{
	m_Bounds.left += m_Velocity.x * elapsedSec;
	m_Bounds.bottom += m_Velocity.y * elapsedSec;


}

const void Arrow::Draw()
{
	m_pArrowTexture->Draw(m_Bounds, m_ArrowTextureCurrentFrame);
}

Rectf Arrow::GetBounds()
{
	return m_Bounds;
}
