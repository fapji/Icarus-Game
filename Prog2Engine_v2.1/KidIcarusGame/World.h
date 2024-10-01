#pragma once
#include "Texture.h"
#include "utils.h"
#include <vector>

class World
{
public:

	World();
	~World();

	void Draw(std::vector<std::vector<Point2f>> SolidVertices, std::vector<std::vector<Point2f>> PassThroughVertices, std::vector<std::vector<Point2f>> DoorVertices);

	float GetWidth();
	float GetHeight();

private:

	Texture* m_pMapTexture;

	//std::vector<std::vector<Point2f>> m_Vertices;



};

