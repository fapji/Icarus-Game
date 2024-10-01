#pragma once

class Camera
{
public:

	Camera(float ScreenWidth, float ScreenHeight, Point2f playerPos);
	void Aim(const Point2f& trackCenter);
	void Reset();

	const Rectf GetMovingViewport();

	void SetMovingViewport(Rectf movingViewport);

private:
	float m_ScreenWidth;
	float m_ScreenHeight;
	Point2f m_cameraBottomLeft;

	Rectf m_MovingViewport;
	float m_CameraShiftAmount;
};

