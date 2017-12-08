/// <summary>
/// パーティクル用ピクセルシェーダ
/// </summary>
#include "Particle.hlsli"

float4 main(GSOutput input) : SV_TARGET
{
	float4 color = g_texture.Sample(g_sampler, input.uv) * input.color;

	return color;
}