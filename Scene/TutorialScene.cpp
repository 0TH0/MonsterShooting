#include "TutorialScene.h"
#include "../Manager/GameManager.h"
#include "../Manager/AudioManager.h"
#include "../Engine/UI.h"
#include "../Engine/Input.h"

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{
}

//初期化
void TutorialScene::Initialize()
{
	UI* pUI = Instantiate<UI>(this);
	pUI->Load("Image/Tutorial.png");

	AudioManager::TitleBGM();
}

//更新
void TutorialScene::Update()
{
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_SPACE))
    {
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TITLE);
		AudioManager::BtnSelectAudio();
		AudioManager::StopTitleBGM();
    }
}

//描画
void TutorialScene::Draw()
{
}

//開放
void TutorialScene::Release()
{
}