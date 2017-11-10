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
/// パーティクルを管理するクラス
/// </summary>
class ParticleEffectManager
{
public:
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Vector4 = DirectX::SimpleMath::Vector4;

	static const int PARTICLE_NUM_MAX;
	// 入力レイアウトの定義.
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	// 点の数
	static const int POINT_NUM;
	// コンスタントバッファ
	struct Constants
	{
		DirectX::SimpleMath::Matrix WVP;	// ワールドビュープロジェクション合成行列
		DirectX::SimpleMath::Matrix BillBoard;	// ビルボード行列
	};

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	// パーティクル登録
	void Entry(Vector3 pos, Vector4 color = Vector4(1, 1, 1, 1), float angle = 0,float scale =1);

	// アクセッサ
	void SetCamera(MyLibrary::Camera* camera) { m_Camera = camera; }

protected:
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	// コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ConstantBuffer;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_PrimitiveBatch;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	// 頂点データ配列
	std::vector<DirectX::VertexPositionColorTexture> m_Vertices;
	// 汎用描画設定
	std::unique_ptr<DirectX::CommonStates> m_CommonStates;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture;
	//テクスチャーサンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	// カメラ
	MyLibrary::Camera* m_Camera;
};
