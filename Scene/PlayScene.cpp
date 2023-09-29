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

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	//BGM
	AudioManager::PlayBGM();
	
	//フェードイン
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

//更新
void PlayScene::Update()
{
	time_++;

	HP* pHP = (HP*)FindObject("HP");
	if (pHP->GetNowHP() <= 0)
	{
		GameManager::GetpSceneManager()->ChangeScene(SCENE_ID_RESULT);
		AudioManager::StopPlayBGM();
	}

	//10秒毎
	if (time_ % 600 == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			Instantiate<Enemy>(this);
		}
	}
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}