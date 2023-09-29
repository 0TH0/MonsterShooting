#include "GameManager.h"
#include "../Engine/Fade.h"
#include "../Engine/SceneManager.h"

namespace GameManager
{
	SceneManager* pSceneManager_;
	int score_;

	//シーンマネージャーのポインタセット
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//シーンマネージャーのポインタゲット
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

	void SetScore(int score) { score_ = score; };

	int GetScore() { return score_; };
}