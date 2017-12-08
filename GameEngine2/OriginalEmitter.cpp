#include "OriginalEmitter.h"
//GenkiDama
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace MyLibrary;

OriginalEmitter::OriginalEmitter(Vector3 position)
{
	m_position = position;
	m_param = 0;
	m_now_time = 0;
}

void OriginalEmitter::Update()
{
	if (m_lost_time <= m_now_time)return;
	ParticleEffectManager* particle_manager = ParticleEffectManager::getInstance();

	// Moving by speed
	m_position += m_velocity;
	// Circular motion
	Vector3 pos;
	// Calculate shift amount
	m_param += 0.1f;
	pos.x = cosf(m_param) * 3.0f;
	pos.y = 0;
	pos.z = sinf(m_param) * 3.0f;
	// Position around the specified position
	pos = m_position + pos;
	Vector3 speed;
	speed.Zero;
	Vector3 accel;
	accel.Zero;
	float scale = 5;
	if (m_lost_time / 3 *2.5<= m_now_time)
	{
		scale = 3;
	}
	if (m_lost_time / 3 * 2.8 <= m_now_time)
	{
		speed.x = RandomRange(-0.01f, 0.01f);
		speed.y = RandomRange(-0.01f, 0.01f);
		speed.z = RandomRange(-0.01f, 0.01f);
		accel.x = RandomRange(-0.001f, 0.001f);
		accel.y = RandomRange(-0.001f, 0.001f);
		accel.z = RandomRange(-0.001f, 0.001f);
	}
	// Fire
	for (int i = 0; i < 5; i++)
	{
		float angle = RandomRange(180, 180);
		float x, y, z;
		x = cosf(angle) * 10;
		y = 0 + speed.y;
		z = sinf(angle) * 10;
		// Start rotation angle
		float startAngle = RandomRange(0, 360);
		particle_manager->Entry(
			0,
			// lifetime
			RandomRange(60, 120),
			// World position
			Vector3(x, y, z),
			// Speed
			speed,
			// Acceleration
			accel,
			// Rotaion Angle (Start , End)
			startAngle, startAngle * 180,
			// Scale (Start , End)
			scale, scale - 2,
			//Color (Start , End)
			Color(0, 0.8f, 1.0f, 0.5f), Color(0, 1.0f, 1.0f, 0)
		);
	}
	m_now_time++;
}