#include "ResultScene.h"
#include "../Stage/Water.h"
#include "../Stage/Ground.h"
#include "../Stage/Sky.h"
#include "../Engine/Input.h"
#include "../Manager/GameManager.h"
#include "../Manager/AudioManager.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
    : GameObject(parent, "ResultScene"),btnID_(0)
{
}

//初期化
void ResultScene::Initialize()
{
	//音
	AudioManager::WinAudio();

	//ステージ
    Instantiate<Water>(this);
    Instantiate<Sky>(this);
    Instantiate<Ground>(this);

	//画像
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
	
	//位置
	pUI_[PLAY]->SetPosition(-0.5, -0.5, 0);
	pUI_[TITLE]->SetPosition(0.5, -0.5, 0);

	//スコア
	pScore_ = Instantiate<Score>(this);
	pScore_->GetUI()->SetPosition({ 0.3,-0.5,0 });
	pScore_->SetScore(GameManager::GetScore());
	pScore_->SetPosition(XMFLOAT3((float)Direct3D::screenWidth_ / 2.f
		,(float)(Direct3D::screenHeight_ / 3.f), 0));
	pScore_->SetRatio(2.f);
}

//更新
void ResultScene::Update()
{
	//決定
	if (Input::IsKeyDown(DIK_SPACE) || (Input::IsPadButtonDown(XINPUT_GAMEPAD_B)))
	{
		if (pUI_[PLAY]->GetIsSelect())
		{
			//プレイシーンへ
			GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_PLAY);
			AudioManager::BtnSelectAudio();
		}
		if (pUI_[TITLE]->GetIsSelect())
		{
			//タイトル
			GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TITLE);
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

//描画
void ResultScene::Draw()
{
}

//開放
void ResultScene::Release()
{
}