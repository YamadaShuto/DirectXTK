#include "ParticleEffectManager.h"

#include <WICTextureLoader.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace MyLibrary;

// Maximum number of particle
const int ParticleEffectManager::PARTICLE_NUM_MAX = 10000;


const std::vector<D3D11_INPUT_ELEMENT_DESC> ParticleEffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

ParticleEffectManager * ParticleEffectManager::getInstance()
{
	static ParticleEffectManager instance;
	return &instance;
}

void ParticleEffectManager::Initialize()
{
	DeviceResources* deviceResources = DeviceResources::GetInstance();
	// Load complied shader file
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	ID3D11Device* device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	// Create vertex shader
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertex_shader.ReleaseAndGetAddressOf())))
	{
		// Error processing
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	// Create geometry shader
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometry_shader.ReleaseAndGetAddressOf())))
	{
		// Error
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// Create pixel shader
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixel_shader.ReleaseAndGetAddressOf())))
	{
		// Error processing
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	// Create primitive batch
	// Information contained in each vertex : Position , Color , TextureUV
	m_primitive_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context, 1, PARTICLE_NUM_MAX);

	// Specifi vertex format and create input layout
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		m_input_layout.GetAddressOf());

	// For passing common data to shaders
	// Create constant buffer
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Constants);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(device->CreateBuffer(&cb, NULL, m_constant_buffer.ReleaseAndGetAddressOf())))
	{
		// Error processing
		MessageBox(0, L"CreateBuffer Failed.", NULL, MB_OK);
		return;
	}
	// Create texture sampler
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	if (FAILED(device->CreateSamplerState(&SamDesc, m_sampler.ReleaseAndGetAddressOf())))
	{
		// Error processing
		MessageBox(0, L"CreateSamplerState Failed.", NULL, MB_OK);
		return;
	}
}

void ParticleEffectManager::LoadTexture(int number , const wchar_t * filename)
{
	ID3D11Device* device = DeviceResources::GetInstance()->GetD3DDevice();
	Texture texture;
	texture.number = number;
	// Load texture
	if (FAILED(CreateWICTextureFromFile(device, filename, nullptr, texture.texture.ReleaseAndGetAddressOf())))
	{
		// Error processing
		MessageBox(0, L"Texture Load Failed", NULL, MB_OK);
		return;
	}
	m_texture.push_back(texture);
}

void ParticleEffectManager::Dispose()
{
	m_vertices.clear();
	m_particles.clear();
	m_texture.clear();
}

void ParticleEffectManager::Update()
{
	// Manage lifetime
	m_vertices.clear();
	for (auto it = m_particles.begin(); it != m_particles.end();)
	{
		if (it->Update())
		{
			it->Update();
			VertexPositionColorTexture vertex;
			vertex.position = it->m_position;
			vertex.color = it->m_color;
			vertex.textureCoordinate.x = it->m_rotation;
			vertex.textureCoordinate.y = it->m_scale;
			m_vertices.push_back(vertex);
			it++;
		}
		else
		{
			// Erase the particles that have reached the end of lives
			it = m_particles.erase(it);
		}
	}
	m_particles[0].m_position = Vector3(1,1,1);
	m_particles[1].m_position;
}

void ParticleEffectManager::Draw()
{
	ID3D11DeviceContext* context = DeviceResources::GetInstance()->GetD3DDeviceContext();
	CommonStates*	common_states = DeviceResources::GetInstance()->GetCommonStates();

	// Create view and projection matrix
	Matrix view = Matrix::Identity;
	Matrix proj = Matrix::Identity;

	view = m_camera->GetView();
	proj = m_camera->GetProj();
	Matrix wvp = view * proj;

	// Pass data to the constant buffer of the shader
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(context->Map(m_constant_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;

		constants.WVP = wvp;
		constants.BillBoard = m_camera->GetBillboard();
		// Overwriting data
		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(constants));
		context->Unmap(m_constant_buffer.Get(), 0);
	}
	// Which shader should use this constant buffer
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, m_constant_buffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 0, nullptr);

	context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
	context->GSSetShader(m_geometry_shader.Get(), nullptr, 0);
	context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);

	context->IASetInputLayout(m_input_layout.Get());

	// Don`t update the depth buffer
	context->OMSetDepthStencilState(common_states->DepthRead(), 0);
	// Erase hidden surface in clockwise direction
	context->RSSetState(common_states->CullNone());
	// Alpha blending drawing
	context->OMSetBlendState(common_states->Additive(), nullptr, 0xFFFFFFFF);
	// Setting texture sampler
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

	std::vector<DirectX::VertexPositionColorTexture> vertexs;
	for (auto it = m_texture.begin(); it != m_texture.end(); it++)
	{
		int i = 0;
		for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
		{
			if (it->number == itr->m_number)
			{
				vertexs.push_back(m_vertices[i]);
			}
			i++;
		}
		if (vertexs.size() > 0)
		{
			// Pass texture to shader		
			context->PSSetShaderResources(0, 1, it->texture.GetAddressOf());
			// Pass all vertex data and drawing
			m_primitive_batch->Begin();
			m_primitive_batch->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &vertexs[0], vertexs.size());
			m_primitive_batch->End();
		}
		vertexs.clear();
	}
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

void ParticleEffectManager::Entry(int number,int frame,
	Vector3 position, Vector3 velocity, Vector3 accel,
	float start_rotation, float end_rotation,
	float start_scale, float end_scale,
	DirectX::SimpleMath::Color start_color, DirectX::SimpleMath::Color end_color)
{
	// One minute vertex data
	ParticleEffect effect;
	effect.m_number = number;
	effect.m_extinction_frame = frame;
	effect.m_position = position;
	effect.m_velocity = velocity;
	effect.m_accel = accel;
	effect.m_start_rotation = start_rotation;
	effect.m_end_rotation = end_rotation;
	effect.m_start_scale = start_scale;
	effect.m_end_scale = end_scale;
	effect.m_start_color = start_color;
	effect.m_end_color = end_color;
	
	m_particles.push_back(std::move(effect));
}

bool ParticleEffectManager::ParticleEffect::Update()
{
	// Count elapsed frames
	m_frame++;
	if (m_frame > m_extinction_frame) return false;
	// Normalize progress
	float frame = (float)m_extinction_frame / m_frame;
	// Add acceleration to speed
	m_velocity += m_accel;
	// Moving by speed
	m_position += m_velocity;
	// Lerping angles
	m_rotation = (m_end_rotation - m_start_rotation) / frame;
	m_rotation += m_start_rotation;
	m_rotation = XMConvertToRadians(m_rotation);
	// Lerping scales
	m_scale = (m_end_scale - m_start_scale) / frame;
	m_scale += m_start_scale;
	// Lerping colors
	m_color = (m_end_color - m_start_color) / frame;
	m_color += m_start_color;
	return true;
}