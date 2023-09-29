#include "TitleScene.h"
#include "../Manager/AudioManager.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"
#include "../Manager/GameManager.h"
#include "../Enemy/Enemy.h"
#include "../Stage/Water.h"
#include "../Stage/Ground.h"
#include "../Stage/Sky.h"
#include "../Engine/UI.h"
#include "../Engine/Camera.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), btnID_(0)
{
}

//初期化
void TitleScene::Initialize()
{
	//BGM
	AudioManager::TitleBGM();

	Instantiate<Water>(this);
	Instantiate<Sky>(this);
	Instantiate<Ground>(this);

	Enemy* pEnemy = Instantiate<Enemy>(this);
	pEnemy->SetPosition(0, 0, 10);

	Enemy* pEnemy2 = Instantiate<Enemy>(this);
	pEnemy2->SetPosition(0, 0, -10);

	//画像
	std::string filename[] = {
		"Image/Title.png",
		"Image/tutorialBt.png",
		"Image/playBt.png",
	};

	for (int i = TITLE; i < MAX_UI; i++)
	{
		std::string fn = filename[i];
		pUI_[i] = Instantiate<UI>(this);
		pUI_[i]->Load(fn);
	}

	//位置
	pUI_[TITLE]->SetPosition(0, 0, 0);
	pUI_[PLAY]->SetPosition(0.5, -0.5, 0);
	pUI_[TUTORIAL]->SetPosition(-0.5, -0.5, 0);

	//カメラ
	Camera::SetPosition(XMFLOAT3(20, 3, 0));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
}

//更新
void TitleScene::Update()
{
	//決定
	if (Input::IsKeyDown(DIK_SPACE) || (Input::IsPadButtonDown(XINPUT_GAMEPAD_B)))
	{
		if (pUI_[TUTORIAL]->GetIsSelect())
		{
			GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TUTORIAL);
			AudioManager::StopTitleBGM();
			AudioManager::BtnSelectAudio();
		}
		if (pUI_[PLAY]->GetIsSelect())
		{
			//プレイシーンへ
			GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_PLAY);
			AudioManager::StopTitleBGM();
			AudioManager::BtnSelectAudio();
		}
	}

	//選択
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

	if (btnID_ == (int)BTN_TUTORIAL)
	{
		pUI_[TUTORIAL]->SetIsSelect(true);
		pUI_[PLAY]->SetIsSelect(false);
	}
	if (btnID_ == (int)BTN_PLAY)
	{
		pUI_[PLAY]->SetIsSelect(true);
		pUI_[TUTORIAL]->SetIsSelect(false);
	}
}

//描画
void TitleScene::Draw()
{
}

//開放
void TitleScene::Release()
{
}