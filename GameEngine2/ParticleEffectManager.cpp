#include "ParticleEffectManager.h"

#include <WICTextureLoader.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace MyLibrary;

// �p�[�e�B�N���ő吔
const int ParticleEffectManager::PARTICLE_NUM_MAX = 20000;

// �_�̐�
const int ParticleEffectManager::POINT_NUM = 200;

const std::vector<D3D11_INPUT_ELEMENT_DESC> ParticleEffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

void ParticleEffectManager::Initialize()
{
	m_Camera = nullptr;

	DeviceResources* deviceResources = DeviceResources::GetInstance();
	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	ID3D11Device* device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// �v���~�e�B�u�o�b�`�쐬
	//  �e���_�Ɋ܂܂���񂪁A�ʒu�E�F�E�e�N�X�`��UV
	m_PrimitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context, 1, PARTICLE_NUM_MAX);

	// ���_�t�H�[�}�b�g���w�肵�ē��̓��C�A�E�g�쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		m_InputLayout.GetAddressOf());

	//�V�F�[�_�ɋ��ʃf�[�^��n���ׂ�
	//�R���X�^���g�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Constants);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(device->CreateBuffer(&cb, NULL, m_ConstantBuffer.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateBuffer Failed.", NULL, MB_OK);
		return;
	}

	m_CommonStates = std::make_unique<CommonStates>(device);

	// �e�N�X�`���ǂݍ���
	if (FAILED(CreateWICTextureFromFile(device, L"Resources/Textures/asuna.png", nullptr,
		m_Texture.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"ParticleTest Failed.", NULL, MB_OK);
		return;
	}

	// �e�N�X�`���T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	if (FAILED(device->CreateSamplerState(&SamDesc, m_Sampler.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateSamplerState Failed.", NULL, MB_OK);
		return;
	}
}

void ParticleEffectManager::Update()
{
	//for (auto& vertex : m_Vertices)
	//{
	//	vertex.position.x += 0.01f;
	//}

	//for (auto& vertex : m_Vertices)
	//{
	//	vertex.color.x -= 0.01f;
	//	vertex.color.y -= 0.01f;
	//	vertex.color.z -= 0.01f;
	//}

	//static float param = 0;
	//param += 0.1f;

	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	vertex.textureCoordinate.x = sinf(param - i*XM_2PI / POINT_NUM) + 1.0f;
	//	vertex.textureCoordinate.y += 0.1f;
	//	i++;
	//}
	//static float param = 0;
	//param += 0.1f;

	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	vertex.textureCoordinate.x = (sinf(param - i /*XM_2PI/POINT_NUM*/) + 1) / 8;
	//	vertex.textureCoordinate.y += 0.1f;
	//	vertex.color = Vector4(cos(param - i), 0, sin(param - i), 1); // �F
	//	i++;
	//}
}

void ParticleEffectManager::Draw()
{

	DeviceResources* deviceResources = DeviceResources::GetInstance();
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	// �r���[�A�v���W�F�N�V�����s�������
	Matrix world = Matrix::Identity;
	Matrix view = Matrix::Identity;
	Matrix proj = Matrix::Identity;

	//world = Matrix::CreateScale(3.0f);

	view = m_Camera->GetView();
	proj = m_Camera->GetProj();
	Matrix wvp = world * view * proj;

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(context->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;

		constants.WVP = wvp;
		constants.BillBoard = m_Camera->GetBillboard();
		//�f�[�^���㏑��
		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(constants));
		context->Unmap(m_ConstantBuffer.Get(), 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 0, nullptr);

	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);

	context->IASetInputLayout(m_InputLayout.Get());

	// �A���t�@�u�����h�`��
	context->OMSetBlendState(m_CommonStates->Additive(), nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@���X�V���Ȃ�
	context->OMSetDepthStencilState(m_CommonStates->DepthRead(), 0);

	// ���v���̖ʂ��A�ʏ���
	context->RSSetState(m_CommonStates->CullNone());

	// �e�N�X�`���T���v���[�ݒ�
	context->PSSetSamplers(0, 1, m_Sampler.GetAddressOf());
	//�e�N�X�`���[���V�F�[�_�[�ɓn��		
	context->PSSetShaderResources(0, 1, m_Texture.GetAddressOf());

	// ���_�f�[�^�����ׂēn���ĕ`�悷��
	m_
		->Begin();
	m_PrimitiveBatch->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, &m_Vertices[0], m_Vertices.size());
	m_PrimitiveBatch->End();

	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

void ParticleEffectManager::Entry(Vector3 pos,Vector4 color,float angle,float scale)
{
	// �P���̒��_�f�[�^
	VertexPositionColorTexture vertexData;
	vertexData.position = pos;
	vertexData.color = color; // ��
	// �X�P�[��
	vertexData.textureCoordinate.x = scale;
	// ��]�p
	vertexData.textureCoordinate.y = angle;
	m_Vertices.push_back(vertexData);
}
