#pragma once
#include <string>

//�t�F�[�h�̏�Ԃ̗񋓌^
enum FadeStatus
{
	NONE,			 //�������Ȃ�
	DRAW,			 //�摜�����\��
	FADE_CIRCLE_IN,  //�~�̃t�F�[�h�C��
	FADE_CIRCLE_OUT, //�~�̃t�F�[�h�A�E�g
	FADE_NORMAL_IN,  //�ʏ�̃t�F�[�h�C��
	FADE_NORMAL_OUT, //�ʏ�̃t�F�[�h�A�E�g
};

//�t�F�[�h���s���Ƃ��Ɏg��
namespace Fade
{
	//������
	void Initialize();

	//�`��
	void Draw();

	//���ʂ̉摜��\��
	void NormalDraw();

	//��Ԃɂ���ČĂԊ֐�������
	void FadeDraw();
	
	//�t�F�[�h�C���`��
	void FadeInCircleDraw();

	//�t�F�[�h�A�E�g�`��
	void FadeOutCircleDraw();

	//�t�F�[�h�C���`��
	void FadeInNormalDraw();

	//�t�F�[�h�A�E�g�`��
	void FadeOutNormalDraw();

	//��Ԃ��Z�b�g
	void SetFadeStatus(int status, std::string filename = "");

	//���݂̏�Ԃ��擾
	int GetFadeStatus();

	//�ʏ�̃t�F�[�h����������Ȃ����ǂ���
	bool isNormalFadeNotTransparency();
}

