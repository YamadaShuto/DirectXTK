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

	//プロパティの書き方
	//__declspec(property(get = GetFrame, put = SetFrame)) float Frame;
private:
	//生存フレーム数
	int m_frame;
	//生存したフレーム
	int m_alive_frame;
	//表示位置
	Vector3 m_position;
	//速度
	Vector3 m_velocity;
	//加速度
	Vector3 m_accel;
	//現在の回転角
	float m_rotation;
	//開始時の回転角
	float m_start_rotation;
	//終了時の回転角
	float m_end_rotation;
	//現在の大きさ
	float m_scale;
	//開始時の大きさ
	float m_start_scale;
	//終了時の大きさ
	float m_end_scale;
	//現在の色
	DirectX::XMFLOAT4 m_color;
	//開始時の色
	DirectX::XMFLOAT4 m_start_color;
	//終了時の色
	DirectX::XMFLOAT4 m_end_color;
	//生きているか
	bool m_is_alive;
};
