#include "GameManager.h"
#include "../Engine/Fade.h"
#include "../Engine/SceneManager.h"

namespace GameManager
{
	SceneManager* pSceneManager_;
	int score_;

	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void GameManager::SetpSceneManager(SceneManager* scene) { pSceneManager_ = scene; }

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GameManager::GetpSceneManager() { return pSceneManager_; }

	void SetScore(int score) { score_ = score; };

	int GetScore() { return score_; };
}