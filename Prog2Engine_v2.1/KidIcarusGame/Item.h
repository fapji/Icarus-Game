#pragma once
#include "Texture.h"


class Item
{
public:
	Item(std::string Texture, Point2f Position);
	virtual ~Item();
	virtual void Draw() const;

	Rectf GetBounds();

protected:
	Texture* m_pTexture;

	Rectf m_PosAndSize;
	Rectf m_TextureBounds;

};

