#include "ExplosionEmitter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace MyLibrary;

ExplosionEmitter::ExplosionEmitter(Vector3 position)
{
	m_position = position;
	m_param = 0;
	m_now_time = 0;
}

void ExplosionEmitter::Update()
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

	// Fire
	for (int i = 0; i < 5; i++)
	{
		float angle = RandomRange(180, 180);
		float x, y, z;
		x = cosf(angle);
		y = 0;
		z = sinf(angle);
		// Start rotation angle
		float startAngle = RandomRange(0, 360);
		particle_manager->Entry(
			0,
			// lifetime
			RandomRange(60, 120),
			// World position
			Vector3(x, y, z),
			// Speed
			Vector3(0, RandomRange(0.05f, 0.1f), 0),
			// Acceleration
			Vector3(0, 0, 0),
			// Rotaion Angle (Start , End)
			startAngle, startAngle + 180.f,
			// Scale (Start , End)
			5, 5,
			//Color (Start , End)
			Color(1, RandomRange(0.2, 0.5f), 0, 0.1f), Color(1, 0.2f, 0, 0)
		);
	}
	m_now_time++;
}