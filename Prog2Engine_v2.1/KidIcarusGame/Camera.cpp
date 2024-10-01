#include "pch.h"
#include "Camera.h"
#include "Matrix2x3.h"

#include <iostream>


Camera::Camera(float ScreenWidth, float ScreenHeight, Point2f playerPos)
	:m_ScreenWidth{ ScreenWidth }, m_ScreenHeight{ ScreenHeight }
{
	m_cameraBottomLeft = Point2f(ScreenWidth, ScreenHeight);
	m_MovingViewport = Rectf(0, playerPos.y-150, ScreenWidth, ScreenHeight);
	m_CameraShiftAmount = 3;
}

void Camera::Aim(const Point2f& playerPos)
{

	if ((m_MovingViewport.bottom + m_ScreenHeight / 3)  < playerPos.y)
	{
		m_MovingViewport.bottom += m_CameraShiftAmount;
	}

	glPushMatrix();
	{
		glTranslatef(0, -m_MovingViewport.bottom, 0);
	}

}

void Camera::Reset()
{
	glPopMatrix();
}

const Rectf Camera::GetMovingViewport()
{
	return m_MovingViewport;
}

void Camera::SetMovingViewport(Rectf movingViewport)
{
	m_MovingViewport = movingViewport;
}
