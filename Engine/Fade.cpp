#include "Fade.h"
#include <cmath>
#include "../Engine/SceneManager.h"
#include "../Engine/Sprite.h"

//�萔
namespace
{
	//�t�F�[�h����Ƃ��̉��Z���鋗��
	static const float FADE_ADD_DISTANCE = 10.0f;

	//�t�F�[�h����Ƃ��̉��Z���铧���x
	static const float FADE_ADD_ALPHA = 0.01f;
}

//�t�F�[�h���s���Ƃ��Ɏg��
namespace Fade
{

	///////////////////////////////�ϐ�//////////////////////////////////

	int fadeStatus_;    //�t�F�[�h�̏��
	float maxDistance_; //�~�t�F�[�h�Ŏg�p����ő勗��
	float nowDistance_; //�~�t�F�[�h�Ŏg�p���鍡�̋���

	//�~�t�F�[�h�p�̉摜(�V�[���̐���)
	Sprite* pSprite_;

	//�ʏ�t�F�C�h�p�̉摜(��)
	Sprite* pNormal_;
	Transform normal_;         //�ʏ�t�F�C�h�p�̉摜�̃g�����X�t�H�[��
	float normalAlpha_;        //�ʏ�t�F�C�h�̓����x

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void Fade::Initialize()
	{
		pSprite_ = new Sprite();
		pSprite_->Load("Image/NormalFade.png");

		//�ʏ�p�̉摜���[�h
		pNormal_ =  new Sprite();
		pNormal_->Load("Image/NormalFade.png");

		//�e�ϐ�������
		normalAlpha_ =  ZERO;
		fadeStatus_ = NONE;
		maxDistance_ =  (float)(std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		nowDistance_ =  ZERO;
	}

	//�`��
	void Fade::Draw()
	{
		//�t�F�[�h�p�̕`��
		FadeDraw();
	}

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////

	//��ԃZ�b�g
	void Fade::SetFadeStatus(int status, std::string filename)
	{
		//�����t�@�C���l�[���̋L�q������΃m�[�}���t�F�C�h�̉摜�ύX
		if(filename != "") pNormal_->Load(filename);

		//�X�e�[�^�X�X�V
		fadeStatus_ = status;

		//��Ԃɂ���ĕ�����
		switch (fadeStatus_)
		{

			//�摜�����`��
		case DRAW:

			NormalDraw();
			break;

			//�~�t�F�[�h�C��
		case FADE_CIRCLE_IN:

			nowDistance_ =  ZERO;
			break;

			//�~�t�F�[�h�A�E�g
		case FADE_CIRCLE_OUT:

			nowDistance_ =  maxDistance_;
			break;

			//�ʏ�t�F�[�h�C��
		case FADE_NORMAL_IN:

			normalAlpha_ =  ZERO;
			break;

			//�ʏ�t�F�[�h�A�E�g
		case FADE_NORMAL_OUT:

			normalAlpha_ =  1.0f;
			break;

			//����ȊO
		default:

			break;
		}
	}

	//��ԃQ�b�g
	int Fade::GetFadeStatus() { return fadeStatus_; }

	//�ʏ�̃t�F�[�h����������Ȃ����ǂ���
	bool isNormalFadeNotTransparency() { return (normalAlpha_ >= 1.0f); }

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////

	//�t�F�[�h�`��
	void Fade::FadeDraw()
	{
		//��Ԃɂ���ĕς���
		switch (fadeStatus_)
		{
			//�摜�����`��
		case DRAW:

			NormalDraw();
			break;

			//�~�t�F�[�h�C��
		case FADE_CIRCLE_IN:

			FadeInCircleDraw();
			break;

			//�~�t�F�[�h�A�E�g
		case FADE_CIRCLE_OUT:

			FadeOutCircleDraw();
			break;

			//�ʏ�t�F�[�h�C��
		case FADE_NORMAL_IN:

			FadeInNormalDraw();
			break;

			//�ʏ�t�F�[�h�A�E�g
		case FADE_NORMAL_OUT:

			FadeOutNormalDraw();
			break;

			//����ȊO
		default:

			break;
		}

	}

	//�`��
	void Fade::NormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//�`��
		pSprite_->Draw(t, rect);
	}

	//�~�t�F�[�h�C���`��
	void Fade::FadeInCircleDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//�`��
		pSprite_->Draw(t, nowDistance_, rect);
	};

	//�~�t�F�[�h�A�E�g�`��
	void Fade::FadeOutCircleDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ -= FADE_ADD_DISTANCE;

		if (nowDistance_ < ZERO)
			nowDistance_ = ZERO;

		//�`��
		pSprite_->Draw(t, nowDistance_, rect);
	};

    //�t�F�[�h�C���`��
	void Fade::FadeInNormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pNormal_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//���X�ɓ�������Ȃ�
		normalAlpha_ += FADE_ADD_ALPHA;

		//�`��
		pNormal_->Draw(t, rect, XMFLOAT4(1, 1, 1, normalAlpha_));
	}

	//�t�F�[�h�A�E�g�`��
	void Fade::FadeOutNormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pNormal_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//���X�ɓ�����
		normalAlpha_ -= FADE_ADD_ALPHA;

		//�`��
		pNormal_->Draw(t,rect, XMFLOAT4(1, 1, 1, normalAlpha_));
	}
}
