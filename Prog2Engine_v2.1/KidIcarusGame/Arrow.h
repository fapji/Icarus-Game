#pragma once
#include "Texture.h"
#include "Vector2f.h"


class Player;

class Arrow
{
public:
	Arrow(Player* pPlayer, bool LookingRight);
	~Arrow();

	void update(float elapsedSec);
	const void Draw();

	Rectf GetBounds();


private:
	Texture* m_pArrowTexture;

	int m_TextureColls{ 3 };
	int m_FrameSizeColls{};
	int m_FrameSizeRows{};


	Rectf m_Bounds;
	Rectf m_ArrowTextureCurrentFrame;
	Vector2f m_Velocity;
	float m_ArrowSpeed{ 400 };
};

