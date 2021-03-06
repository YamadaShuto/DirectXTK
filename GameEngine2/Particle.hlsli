//--------------------------------------------------------------------------------------
// Constant buffer
//--------------------------------------------------------------------------------------
cbuffer global
{
	row_major matrix g_VP; //ワールドから射影までの変換行列
	row_major matrix g_Billboard; //ビルボード行列
};

//-----------------------------------------------------------------------------------------
// テクスチャとサンプラー
//-----------------------------------------------------------------------------------------
Texture2D g_texture: register(t0);
SamplerState g_sampler : register(s0);

//--------------------------------------------------------------------------------------
// ジオメトリシェーダへの出力
//--------------------------------------------------------------------------------------
struct VSOutput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 other : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// ピクセルシェーダへの出力
//--------------------------------------------------------------------------------------
struct GSOutput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};