#include "ResultScene.h"
#include "../Stage/Water.h"
#include "../Stage/Ground.h"
#include "../Stage/Sky.h"
#include "../Engine/Input.h"
#include "../Manager/GameManager.h"
#include "../Manager/AudioManager.h"

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
    : GameObject(parent, "ResultScene"),btnID_(0)
{
}

//������
void ResultScene::Initialize()
{
	//��
	AudioManager::WinAudio();

	//�X�e�[�W
    Instantiate<Water>(this);
    Instantiate<Sky>(this);
    Instantiate<Ground>(this);

	//�摜
	std::string filename[] = {
		"Image/PlayBt.png",
		"Image/ToTitleBt.png",
	};

	for (int i = PLAY; i < MAX_UI; i++)
	{
		std::string fn = filename[i];
		pUI_[i] = Instantiate<UI>(this);
		pUI_[i]->Load(fn);
	}
	
	//�ʒu
	pUI_[PLAY]->SetPosition(-0.5, -0.5, 0);
	pUI_[TITLE]->SetPosition(0.5, -0.5, 0);

	//�X�R�A
	pScore_ = Instantiate<Score>(this);
	pScore_->GetUI()->SetPosition({ 0.3,-0.5,0 });
	pScore_->SetScore(GameManager::GetScore());
	pScore_->SetPosition(XMFLOAT3((float)Direct3D::screenWidth_ / 2.f
		,(float)(Direct3D::screenHeight_ / 3.f), 0));
	pScore_->SetRatio(2.f);
}

//�X�V
void ResultScene::Update()
{
	//����
	if (Input::IsKeyDown(DIK_SPACE) || (Input::IsPadButtonDown(XINPUT_GAMEPAD_B)))
	{
		if (pUI_[PLAY]->GetIsSelect())
		{
			//�v���C�V�[����
			GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_PLAY);
			AudioManager::BtnSelectAudio();
		}
		if (pUI_[TITLE]->GetIsSelect())
		{
			//�^�C�g��
			GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TITLE);
			AudioManager::BtnSelectAudio();
		}
	}

	//�I��
	if (Input::IsKeyDown(DIK_RIGHT) || Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		AudioManager::BtnMoveAudio();
		if (btnID_ <= 0)
		{
			btnID_++;
		}
	}
	if (Input::IsKeyDown(DIK_LEFT) || Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_LEFT))
	{
		AudioManager::BtnMoveAudio();
		if (btnID_ >= 1)
		{
			btnID_--;
		}
	}

	if (btnID_ == TITLE)
	{
		pUI_[TITLE]->SetIsSelect(true);
		pUI_[PLAY]->SetIsSelect(false);
	}
	if (btnID_ == PLAY)
	{
		pUI_[PLAY]->SetIsSelect(true);
		pUI_[TITLE]->SetIsSelect(false);
	}
}

//�`��
void ResultScene::Draw()
{
}

//�J��
void ResultScene::Release()
{
}