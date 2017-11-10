// ジオメトリシェーダ
#include "Particle.hlsli"

// 四角形の頂点数
static const uint vnum = 4;

// 中心点からのオフセット
static const float4 offset_array[vnum] =
{
	float4(-0.5f, -0.5f, 0, 0),	// 左下
	float4(+0.5f, -0.5f, 0, 0),	// 右下
	float4(-0.5f, +0.5f, 0, 0),	// 左上
	float4(+0.5f, +0.5f, 0, 0)	// 右上
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
	point GSInput input[1],
	inout TriangleStream< PSInput > output
)
{
	//for (uint j = 0; j < 100; j++)
	{
		PSInput element;

		float4 offset;
		// 回転角
		float rot = input[0].other.y;

		//for (uint i = 0; i < 3; i++)
		//{			
		//	element.pos = input[i].pos + float4(j, 0, 0, 0);
		//	element.pos = mul(element.pos, g_WVP);
		//	//element.pos += float4(1.0f * j, 0, 0, 0);
		//	element.color = input[i].color;
		//	element.uv = input[i].uv;
		//	output.Append(element);
		//}

		// 4点分
		for (uint i = 0; i < vnum; i++)
		{
			// 指定角度分回転
			offset.x = offset_array[i].x *  cos(rot) + offset_array[i].y * sin(rot);
			offset.y = offset_array[i].x * -sin(rot) + offset_array[i].y * cos(rot);
			offset.z = 0;
			offset.w = 0;
			// ビルボード行列による回転
			offset = mul(offset, g_Billboard);
			element.pos = input[0].pos + offset * input[0].other.x;
			// 座標変換（ワールド座標→２Ｄ座標）
			element.pos = mul(element.pos, g_WVP);
			element.color = input[0].color;
			element.uv = uv_array[i];
			output.Append(element);
		}

		//// 2点目
		//element.pos = input[0].pos + float4(+0.5f, -0.5f, 0, 0);
		//element.pos = mul(element.pos, g_WVP);
		//element.color = input[0].color;
		//element.uv = input[0].uv;
		//output.Append(element);

		//// 3点目
		//element.pos = input[0].pos + float4(-0.5f, +0.5f, 0, 0);
		//element.pos = mul(element.pos, g_WVP);
		//element.color = input[0].color;
		//element.uv = input[0].uv;
		//output.Append(element);

		//// 4点目
		//element.pos = input[0].pos + float4(0.5f, 0.5f, 0, 0);
		//element.pos = mul(element.pos, g_WVP);
		//element.color = input[0].color;
		//element.uv = input[0].uv;
		//output.Append(element);

		output.RestartStrip();
	}
}