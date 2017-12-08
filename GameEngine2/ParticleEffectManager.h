
#pragma once

#include <vector>

#include <windows.h>
#include <wrl/client.h>

#include <d3d11_1.h>

#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <list>
#include <map>

#include "MyLibrary.h"
#include "ParticleEffect.h"

// Class for managing  particles
class ParticleEffectManager
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;

	static const int PARTICLE_NUM_MAX;
	// Definition of Input Layer Out
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	// Constans Buffer
	struct Constants
	{
		// World View projection synthesis matrix
		DirectX::SimpleMath::Matrix WVP;
		// BillBoard matrix
		DirectX::SimpleMath::Matrix BillBoard;	
	};
	// 	Acquiring instance of singleton
	static ParticleEffectManager* getInstance();
	// Initialize processing
	void Initialize();
	// Load a texture
	void LoadTexture(int number,const wchar_t* filename);
	//	Disposal processing
	void Dispose();
	// Update processing
	void Update();
	// Drawing processing
	void Draw();
	// Particle registration processing
	void Entry(int number,int frame,
		Vector3 position, Vector3 velocity, Vector3 accel,
		float start_rotation, float end_rotation,
		float start_scale, float end_scale,
		DirectX::SimpleMath::Color start_color, DirectX::SimpleMath::Color end_color);

	// setter
	void SetCamera(MyLibrary::Camera* camera) { m_camera = camera; }

private:
	static ParticleEffectManager instance;
	class ParticleEffect
	{
	public:
		// Constructor
		ParticleEffect() 
		{
			m_frame = 0;
			m_extinction_frame = 0;
		}
		// Update processing
		bool Update();
		// Group number
		int m_number;
		// Current frame
		int m_frame;
		// Extinction frames
		int m_extinction_frame;
		// Position to display
		Vector3 m_position;
		// Moving speed
		Vector3 m_velocity;
		// Acceleration
		Vector3 m_accel;
		// Current rotation angle
		float m_rotation;
		// Start rotaion angle
		float m_start_rotation;
		// End rotaion angle
		float m_end_rotation;
		// Current scale size
		float m_scale;
		// Start scale size
		float m_start_scale;
		// End scale size
		float m_end_scale;
		// Current color
		DirectX::SimpleMath::Color m_color;
		// Start color
		DirectX::SimpleMath::Color m_start_color;
		// End color
		DirectX::SimpleMath::Color m_end_color;
	};
	// Vertex shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertex_shader;
	// Geometry shader
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometry_shader;
	// Pixel shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixel_shader;
	// Constant buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constant_buffer;
	// Primitive batch
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitive_batch;
	// Input layout
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_input_layout;
	// Class of particle
	std::vector<DirectX::VertexPositionColorTexture> m_vertices;
	std::vector<ParticleEffect> m_particles;
	// General purpose drawing setting 
	std::unique_ptr<DirectX::CommonStates> m_common_states;
	// Texture
	struct Texture
	{
		int number;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	};
	std::vector<Texture> m_texture;
	// Texture Sampler
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;
	// Camera
	MyLibrary::Camera* m_camera;
	// Gravitational acceleration
	Vector3 m_gravity;
};
