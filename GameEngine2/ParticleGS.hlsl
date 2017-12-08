// �W�I���g���V�F�[�_
#include "Particle.hlsli"

// �l�p�`�̒��_��
static const uint vnum = 4;

// ���S�_����̃I�t�Z�b�g
static const float4 offset_array[vnum] =
{
	float4(-0.5f, -0.5f, 0, 0),	// ����
	float4( 0.5f, -0.5f, 0, 0),	// �E��
	float4(-0.5f,  0.5f, 0, 0),	// ����
	float4( 0.5f,  0.5f, 0, 0)	// �E��
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
	point VSOutput input[1],
	inout TriangleStream< GSOutput > output
)
{
	{
        GSOutput element = (GSOutput)0;

		float4 offset;

		// 1�_�̍��W����4�_���쐬
		for (uint i = 0; i < vnum; i++)
		{
            offset = offset_array[i];
            offset.x = offset_array[i].x * cos(input[0].other.x) + offset_array[i].y * +sin(input[0].other.x);
            offset.y = offset_array[i].x * -sin(input[0].other.x) + offset_array[i].y * +cos(input[0].other.x);
			// �Z���^�[����̂��炵�����r���{�[�h��
			offset = mul(offset * input[0].other.y, g_Billboard);
			// �r���[�v���W�F�N�V�����ϊ�
			element.pos = mul(input[0].pos + offset, g_VP);
			element.color = input[0].color;
			element.uv = uv_array[i];
			output.Append(element);
		}

        //���݂̃X�g���b�v���I��
		output.RestartStrip();
	}
}