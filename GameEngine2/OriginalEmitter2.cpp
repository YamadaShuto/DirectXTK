#include "OriginalEmitter2.h"
//GenkiDama
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace MyLibrary;

OriginalEmitter2::OriginalEmitter2(Vector3 position)
{
	m_position = position;
	m_param = 0;
	m_now_time = 0;
}

void OriginalEmitter2::Update()
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
	float scale = 1;
	float end_scale = 5;
	int tex = 0;
	int frame = 360;
	if (m_lost_time / 3 * 0.5 <= m_now_time)
	{
		scale = 4.5;
		end_scale = 2.5;
		tex = 2;
		60;
	}
	if (m_lost_time / 3 *0.5<= m_now_time)
	{
		speed.x = RandomRange(0.3f, 0.3f);
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
			tex,
			// lifetime
			RandomRange(120, 120),
			// World position
			Vector3(x, y, z),
			// Speed
			speed,
			// Acceleration
			accel,
			// Rotaion Angle (Start , End)
			startAngle, startAngle * 180,
			// Scale (Start , End)
			scale, end_scale,
			//Color (Start , End)
			Color(0.2f, 0.5f, 1.0f, 0.5f), Color(0.0f, 1.0f, 1.0f, 0)
		);
	}
	m_now_time++;
}