#include "TutorialScene.h"
#include "../Manager/GameManager.h"
#include "../Manager/AudioManager.h"
#include "../Engine/UI.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{
}

//������
void TutorialScene::Initialize()
{
	UI* pUI = Instantiate<UI>(this);
	pUI->Load("Image/Tutorial.png");

	AudioManager::TitleBGM();
}

//�X�V
void TutorialScene::Update()
{
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_SPACE))
    {
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_TITLE);
		AudioManager::BtnSelectAudio();
		AudioManager::StopTitleBGM();
    }
}

//�`��
void TutorialScene::Draw()
{
}

//�J��
void TutorialScene::Release()
{
}