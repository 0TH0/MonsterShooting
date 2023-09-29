#pragma once
#include "../Engine/SceneManager.h"

namespace GameManager
{
	//シーンマネージャーのポインタセット
	void SetpSceneManager(SceneManager* scene);

	//シーンマネージャーのポインタゲット
	SceneManager* GetpSceneManager();

	//セッターゲッター
	void SetScore(int score);

	int GetScore();
};