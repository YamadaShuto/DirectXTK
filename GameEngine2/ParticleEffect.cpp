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
	//�t���[�����̃J�E���g
	m_alive_frame++;
	//�i�s�x�𐳋K��
	//float value;
	//value = start + t * (end - start);
	//value;
	float frame = (float)m_alive_frame / m_frame;
	//�����x�̓K��
	m_velocity += m_accel;
	//�ړ�
	m_position += m_velocity;
	//�p�x����`�⊮
	m_rotation = m_start_rotation + frame * (m_end_rotation - m_start_rotation);
	//�X�P�[������`�⊮	
	m_scale = m_start_scale + frame * (m_end_scale - m_start_scale);
	//�F�̐��`�⊮
	m_color.x = m_start_color.x + frame * (m_start_color.x - m_end_color.x);
	m_color.y = m_start_color.y + frame * (m_start_color.y - m_end_color.y);
	m_color.z = m_start_color.z + frame * (m_start_color.z - m_end_color.z);
	m_color.w = m_start_color.w + frame * (m_start_color.w - m_end_color.w);
	/*
	//�p�x����`�⊮
	m_rotation = (m_end_rotation - m_start_rotation) / frame;
	m_rotation += m_start_rotation;
	m_rotation = XMConvertToRadians(m_rotation);
	//�X�P�[���̐��`�⊮
	m_scale = (m_end_scale - m_start_scale) / frame;
	m_scale += m_start_scale;
	//�F�̐��`�⊮
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
