//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture: register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[
Texture2D g_textureNormal : register(t1);   //�m�[�}���e�N�X�`���[


//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	g_matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matNormalTrans;	// �@���̕ϊ��s��i��]�s��Ɗg��̋t�s��j
	float4x4	g_matWorld;			// ���[���h�ϊ��s��
	float4x4	g_mWLP;				//���[���h�E�h���C�g�r���[�h�E�v���W�F�N�V�����̍��� 
	float4x4	g_mWLPT;			//���[���h�E�h���C�g�r���[�h�E�v���W�F�N�V�����EUV �s��̍��� 
	float4		g_vecLightDir;		// ���C�g�̕����x�N�g��
	float4		g_vecDiffuse;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4		g_vecAmbient;		// �A���r�G���g�J���[�i�e�̐F�j
	float4		g_vecSpeculer;		// �X�y�L�����[�J���[�i�n�C���C�g�̐F�j
	float4		g_vecCameraPosition;// ���_�i�J�����̈ʒu�j
	float		g_shuniness;		// �n�C���C�g�̋����i�e�J����j
	float		g_alpha;			//�����x
	float		g_scroll;
	bool		g_isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//�ʒu
	float2 uv	  : TEXCOORD1;		//UV���W
	float4 light  : TEXCOORD2;		//���C�g�̕���
	float4 V      : TEXCOORD3;		//���_����J�����Ɍ������x�N�g��
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD, float4 tangent : TANGENT)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, g_matWVP);

	//UV�u���W
	outData.uv = uv;	//���̂܂܃s�N�Z���V�F�[�_�[��

	//�@��
	normal.w = 0;
	normal = mul(normal, g_matNormalTrans);
	normal = normalize(normal);

	//�^���W�F���g
	tangent.w = 0;
	tangent = mul(tangent, g_matNormalTrans);
	tangent = normalize(tangent);

	//�o�C�m�[�}��
	float3 binormal = cross(normal, tangent);
	binormal = normalize(binormal);

	//���_����J�����Ɍ������x�N�g��(���K��)
	float4 eye = normalize(mul(pos, g_matWorld) - g_vecCameraPosition);
	outData.V.x = dot(eye, tangent);
	outData.V.y = dot(eye, binormal);
	outData.V.z = dot(eye, normal);
	outData.V.w = 0;

	float4 light = float4(1, 0, 1, 0);
	light = normalize(light);
	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	//���K�����Ă���
	inData.light = normalize(inData.light);
	float alpha = 0;

	float2 uv1 = inData.uv;
	uv1.x += g_scroll;
	float4 normal1 = g_textureNormal.Sample(g_sampler, uv1) * 2 - 1;

	float2 uv2 = inData.uv;
	uv2.x -= g_scroll * 0.3;
	float4 normal2 = g_textureNormal.Sample(g_sampler, uv2) * 2 - 1;

	float4 normal = normal1 + normal2;
	normal.w = 0;
	normal = normalize(normal);

	float4 shade = dot(inData.light, normal);
	shade = clamp(shade, 0, 1);

	float4 diffuse;
	//�e�N�X�`���L��
	if (g_isTexture)
	{
		//�e�N�X�`���̐F
		diffuse = g_texture.Sample(g_sampler, inData.uv);
		alpha = g_texture.Sample(g_sampler, inData.uv).a;
	}
	else
	{
		//�}�e���A���̐F
		diffuse = g_vecDiffuse;
	}

	//�����i�A���r�G���g�j
	//�����Maya���Ŏw�肵�A�O���[�o���ϐ��Ŏ󂯎�������̂����̂܂�
	float4 ambient = float4(1, 1, 1, 1);

	//���ʔ��ˌ��i�X�y�L�����[�j
	float4 speculer = g_vecSpeculer;

	float4 R = reflect(inData.light, normal);		//�����˃x�N�g��
	//speculer = pow(clamp(dot(R, inData.V), 0, 1), 5);

	//�ŏI�I�ȐF
	float4 color = diffuse * shade + diffuse * ambient + speculer;
	color.a = alpha;

	return color;
}