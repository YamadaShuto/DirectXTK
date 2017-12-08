/// <summary>
/// パーティクル用頂点シェーダ
/// ビュープロジェクション変換はジオメトリシェーダで行うので、
/// ここではなにもせずそのまま数値を受け渡す
/// </summary>
#include "Particle.hlsli"

VSOutput main( float4 pos : POSITION, float4 color : COLOR, float2 other : TEXCOORD )
{
	VSOutput Out;

	Out.pos = pos;
	Out.color = color;
	Out.other = other;

	return Out;
}