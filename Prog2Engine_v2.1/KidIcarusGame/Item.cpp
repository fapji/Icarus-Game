#include "pch.h"
#include "Item.h"

Item::Item(std::string texture, Point2f position)
{

	m_pTexture = new Texture(texture);
	m_PosAndSize = Rectf(position.x, position.y, m_pTexture->GetWidth() * 2, m_pTexture->GetHeight() * 2);
	m_TextureBounds = Rectf(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight());

}

Item::~Item()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Item::Draw() const
{
	m_pTexture->Draw(m_PosAndSize, m_TextureBounds);
}

Rectf Item::GetBounds()
{
	return m_PosAndSize;
}
