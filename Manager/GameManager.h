#pragma once
#include "../Engine/SceneManager.h"

namespace GameManager
{
	//�V�[���}�l�[�W���[�̃|�C���^�Z�b�g
	void SetpSceneManager(SceneManager* scene);

	//�V�[���}�l�[�W���[�̃|�C���^�Q�b�g
	SceneManager* GetpSceneManager();

	//�Z�b�^�[�Q�b�^�[
	void SetScore(int score);

	int GetScore();
};