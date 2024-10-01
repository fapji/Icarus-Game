#include "pch.h"
#include "World.h"

World::World()
{
	m_pMapTexture = new Texture("stage11bgClean.png");


	//SVGParser::GetVerticesFromSvgFile("stage_part_1_black_white_scaled.svg", m_Vertices);


}

World::~World()
{
	delete m_pMapTexture;
	m_pMapTexture = nullptr;
}

void World::Draw(std::vector<std::vector<Point2f>> SolidVertices, std::vector<std::vector<Point2f>> PassThroughVertices, std::vector<std::vector<Point2f>> DoorVertices)
{
	m_pMapTexture->Draw(Rectf(0, 0, m_pMapTexture->GetWidth(), m_pMapTexture->GetHeight()),
						Rectf(0, 0, m_pMapTexture->GetWidth(), m_pMapTexture->GetHeight()));

	//Draws All wall hitboxes
	/*utils::SetColor(Color4f(1, 1, 1, 1));

	for (std::vector<Point2f> vertices : SolidVertices)
	{
		for (int i = 0; i < vertices.size() - 1; i++)
		{
			utils::DrawLine(vertices[i], vertices[i + 1]);
		}
	}

	utils::SetColor(Color4f(255, 0, 255, 1));

	for (std::vector<Point2f> vertices : PassThroughVertices)
	{
		for (int i = 0; i < vertices.size() - 1; i++)
		{
			utils::DrawLine(vertices[i], vertices[i + 1]);
		}
	}

	utils::SetColor(Color4f(0, 0, 255, 1));
	for (std::vector<Point2f> vertices : DoorVertices)
	{
		for (int i = 0; i < vertices.size() - 1; i++)
		{
			utils::DrawLine(vertices[i], vertices[i + 1]);
		}
	}*/
}

float World::GetWidth()
{
	return m_pMapTexture->GetWidth();
}

float World::GetHeight()
{
	return m_pMapTexture->GetHeight();
}
