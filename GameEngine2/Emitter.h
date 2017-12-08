#pragma once

#include "ParticleEffectManager.h"
#include "MyLibrary.h"

class Emitter
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	// Load texture
	static void LoadTexture();
	// Setting extinction time
	void SetTime(int lost_time) { m_lost_time = lost_time; }
	// setter
	void SetVelocity(Vector3 velocity) { m_velocity = velocity; }
	float RandomRange(float min_value, float max_value);
protected:
	// Position
	Vector3 m_position;
	// Speed
	Vector3 m_velocity;
	// Rotation angle
	float m_param;
	// Extinction time
	int m_lost_time;
	// Current time
	int m_now_time;
};