// ジオメトリシェーダ
#include "Particle.hlsli"

// 四角形の頂点数
static const uint vnum = 4;

// 中心点からのオフセット
static const float4 offset_array[vnum] =
{
	float4(-0.5f, -0.5f, 0, 0),	// 左下
	float4( 0.5f, -0.5f, 0, 0),	// 右下
	float4(-0.5f,  0.5f, 0, 0),	// 左上
	float4( 0.5f,  0.5f, 0, 0)	// 右上
};

// テクスチャＵＶ(左上が0,0 右下1,1)
static const float2 uv_array[vnum] =
{
	float2(0,1), // 左下
	float2(1,1), // 右下
	float2(0,0), // 左上
	float2(1,0), // 右上
};

[maxvertexcount(vnum)]
void main(
	point VSOutput input[1],
	inout TriangleStream< GSOutput > output
)
{
	{
        GSOutput element = (GSOutput)0;

		float4 offset;

		// 1点の座標から4点分作成
		for (uint i = 0; i < vnum; i++)
		{
            offset = offset_array[i];
            offset.x = offset_array[i].x * cos(input[0].other.x) + offset_array[i].y * +sin(input[0].other.x);
            offset.y = offset_array[i].x * -sin(input[0].other.x) + offset_array[i].y * +cos(input[0].other.x);
			// センターからのずらし分をビルボード化
			offset = mul(offset * input[0].other.y, g_Billboard);
			// ビュープロジェクション変換
			element.pos = mul(input[0].pos + offset, g_VP);
			element.color = input[0].color;
			element.uv = uv_array[i];
			output.Append(element);
		}

        //現在のストリップを終了
		output.RestartStrip();
	}
}