#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

#include "MyLibrary.h"

/// <summary>
/// Class for managing particles
/// </summary>
class ParticleEffect
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;

	//Constructor
	ParticleEffect();
	//Update processing
	void Update();
	//	Return whether it is alive
	bool IsAlive() { return m_is_alive; }
	//setter
	void SetFrame(float frame) { m_frame = frame; }
	void SetPosition(Vector3 position) { m_position = position; }
	void SetVelocity(Vector3 velocity) { m_velocity = velocity; }
	void SetAccel(Vector3 accel) { m_accel = accel; }
	void SetStartRotation(float start_rotation) { m_start_rotation = start_rotation; }
	void SetEndRotation(float end_rotation) { m_end_rotation = end_rotation; }
	void SetStartScale(float start_scale) { m_start_scale = start_scale; }
	void SetEndScale(float end_scale) { m_end_scale = end_scale; }
	void SetStartColor(DirectX::XMFLOAT4 start_color) { m_start_color = start_color; }
	void SetEndColor(DirectX::XMFLOAT4 end_color) { m_end_color  =end_color; }

	//getter
	float GetFrame() { return m_frame; }
	Vector3 GetPosition() { return m_position; }
	Vector3 GetVelocity() { return m_velocity; }
	Vector3 GetAccel() { return m_accel; }
	float GetRotation() { return m_rotation; }
	float GetScale() { return m_scale; }
	DirectX::XMFLOAT4 GetColor() { return m_color; }

	//�v���p�e�B�̏�����
	//__declspec(property(get = GetFrame, put = SetFrame)) float Frame;
private:
	//�����t���[����
	int m_frame;
	//���������t���[��
	int m_alive_frame;
	//�\���ʒu
	Vector3 m_position;
	//���x
	Vector3 m_velocity;
	//�����x
	Vector3 m_accel;
	//���݂̉�]�p
	float m_rotation;
	//�J�n���̉�]�p
	float m_start_rotation;
	//�I�����̉�]�p
	float m_end_rotation;
	//���݂̑傫��
	float m_scale;
	//�J�n���̑傫��
	float m_start_scale;
	//�I�����̑傫��
	float m_end_scale;
	//���݂̐F
	DirectX::XMFLOAT4 m_color;
	//�J�n���̐F
	DirectX::XMFLOAT4 m_start_color;
	//�I�����̐F
	DirectX::XMFLOAT4 m_end_color;
	//�����Ă��邩
	bool m_is_alive;
};
