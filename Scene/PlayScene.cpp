#include "PlayScene.h"
#include "../Manager/GameManager.h"
#include "../Stage/Water.h"
#include "../Stage/Ground.h"
#include "../Stage/Sky.h"
#include "../Player/Tank.h"
#include "../Enemy/Enemy.h"
#include "../Engine/Fade.h"
#include "../Player/HP.h"
#include "../Player/Score.h"
#include "../Manager/AudioManager.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	//BGM
	AudioManager::PlayBGM();
	
	//�t�F�[�h�C��
	Fade::SetFadeStatus(FADE_CIRCLE_IN);
	Instantiate<Water>(this);
	Instantiate<Sky>(this);
	Instantiate<Ground>(this);
	for (int i = 0; i < 20; i++)
	{
		Instantiate<Enemy>(this);
	}
	Instantiate<Tank>(this);
	Instantiate<Score>(this);
}

//�X�V
void PlayScene::Update()
{
	time_++;

	HP* pHP = (HP*)FindObject("HP");
	if (pHP->GetNowHP() <= 0)
	{
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_RESULT);
		AudioManager::StopPlayBGM();
	}

	//10�b��
	if (time_ % 600 == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			Instantiate<Enemy>(this);
		}
	}
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}