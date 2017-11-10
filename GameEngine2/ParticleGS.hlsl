// �W�I���g���V�F�[�_
#include "Particle.hlsli"

// �l�p�`�̒��_��
static const uint vnum = 4;

// ���S�_����̃I�t�Z�b�g
static const float4 offset_array[vnum] =
{
	float4(-0.5f, -0.5f, 0, 0),	// ����
	float4(+0.5f, -0.5f, 0, 0),	// �E��
	float4(-0.5f, +0.5f, 0, 0),	// ����
	float4(+0.5f, +0.5f, 0, 0)	// �E��
};

// �e�N�X�`���t�u(���オ0,0 �E��1,1)
static const float2 uv_array[vnum] =
{
	float2(0,1), // ����
	float2(1,1), // �E��
	float2(0,0), // ����
	float2(1,0), // �E��
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
		// ��]�p
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

		// 4�_��
		for (uint i = 0; i < vnum; i++)
		{
			// �w��p�x����]
			offset.x = offset_array[i].x *  cos(rot) + offset_array[i].y * sin(rot);
			offset.y = offset_array[i].x * -sin(rot) + offset_array[i].y * cos(rot);
			offset.z = 0;
			offset.w = 0;
			// �r���{�[�h�s��ɂ���]
			offset = mul(offset, g_Billboard);
			element.pos = input[0].pos + offset * input[0].other.x;
			// ���W�ϊ��i���[���h���W���Q�c���W�j
			element.pos = mul(element.pos, g_WVP);
			element.color = input[0].color;
			element.uv = uv_array[i];
			output.Append(element);
		}

		//// 2�_��
		//element.pos = input[0].pos + float4(+0.5f, -0.5f, 0, 0);
		//element.pos = mul(element.pos, g_WVP);
		//element.color = input[0].color;
		//element.uv = input[0].uv;
		//output.Append(element);

		//// 3�_��
		//element.pos = input[0].pos + float4(-0.5f, +0.5f, 0, 0);
		//element.pos = mul(element.pos, g_WVP);
		//element.color = input[0].color;
		//element.uv = input[0].uv;
		//output.Append(element);

		//// 4�_��
		//element.pos = input[0].pos + float4(0.5f, 0.5f, 0, 0);
		//element.pos = mul(element.pos, g_WVP);
		//element.color = input[0].color;
		//element.uv = input[0].uv;
		//output.Append(element);

		output.RestartStrip();
	}
}