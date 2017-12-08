#include "ParticleEffect.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;

ParticleEffect::ParticleEffect()
	:m_frame(0),m_position(0,0,0),
	m_velocity(0,0,0),m_accel(0,0,0),
	m_alive_frame(0),m_color(0,0,0,0),
	m_rotation(0),m_scale(0)
{
}

void ParticleEffect::Update()
{
	if (m_frame <= m_alive_frame)
	{
		m_is_alive = false;
	}
	//フレーム数のカウント
	m_alive_frame++;
	//進行度を正規化
	//float value;
	//value = start + t * (end - start);
	//value;
	float frame = (float)m_alive_frame / m_frame;
	//加速度の適応
	m_velocity += m_accel;
	//移動
	m_position += m_velocity;
	//角度を線形補完
	m_rotation = m_start_rotation + frame * (m_end_rotation - m_start_rotation);
	//スケールを線形補完	
	m_scale = m_start_scale + frame * (m_end_scale - m_start_scale);
	//色の線形補完
	m_color.x = m_start_color.x + frame * (m_start_color.x - m_end_color.x);
	m_color.y = m_start_color.y + frame * (m_start_color.y - m_end_color.y);
	m_color.z = m_start_color.z + frame * (m_start_color.z - m_end_color.z);
	m_color.w = m_start_color.w + frame * (m_start_color.w - m_end_color.w);
	/*
	//角度を線形補完
	m_rotation = (m_end_rotation - m_start_rotation) / frame;
	m_rotation += m_start_rotation;
	m_rotation = XMConvertToRadians(m_rotation);
	//スケールの線形補完
	m_scale = (m_end_scale - m_start_scale) / frame;
	m_scale += m_start_scale;
	//色の線形補完
	m_color.x = (m_end_color.x - m_start_color.x) / frame;
	m_color.y = (m_end_color.y - m_start_color.y) / frame;
	m_color.z = (m_end_color.z - m_start_color.z) / frame;
	m_color.w = (m_end_color.w - m_start_color.w) / frame;
	m_color.x += m_start_color.x;
	m_color.y += m_start_color.y;
	m_color.z += m_start_color.z;
	m_color.w += m_start_color.w;
	*/
}
