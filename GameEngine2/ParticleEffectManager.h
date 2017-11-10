#pragma once

#include <vector>

#include <windows.h>
#include <wrl/client.h>

#include <d3d11_1.h>

#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

#include "MyLibrary.h"

/// <summary>
/// �p�[�e�B�N�����Ǘ�����N���X
/// </summary>
class ParticleEffectManager
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;

	static const int PARTICLE_NUM_MAX;
	// ���̓��C�A�E�g�̒�`.
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	// �_�̐�
	static const int POINT_NUM;
	// �R���X�^���g�o�b�t�@
	struct Constants
	{
		DirectX::SimpleMath::Matrix WVP;	// ���[���h�r���[�v���W�F�N�V���������s��
		DirectX::SimpleMath::Matrix BillBoard;	// �r���{�[�h�s��
	};

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �p�[�e�B�N���o�^
	void Entry(Vector3 pos, Vector4 color = Vector4(1, 1, 1, 1), float angle = 0,float scale =1);

	// �A�N�Z�b�T
	void SetCamera(MyLibrary::Camera* camera) { m_Camera = camera; }

protected:
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_PrimitiveBatch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	// ���_�f�[�^�z��
	std::vector<DirectX::VertexPositionColorTexture> m_Vertices;
	// �ėp�`��ݒ�
	std::unique_ptr<DirectX::CommonStates> m_CommonStates;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture;
	//�e�N�X�`���[�T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	// �J����
	MyLibrary::Camera* m_Camera;
};
