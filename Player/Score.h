#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"
#include "../Engine/UI.h"

//Score���Ǘ�����N���X
class Score : public GameObject
{
	Text* pText_;//�e�L�X�g
	UI* pUI_;	//�X�R�AUI
	int score_;	//�X�R�A
	float ratio_;	//�{��
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Score(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�Z�b�^�[�Q�b�^�[
	void SetScore(int point) { score_ = point; };
	int GetScore() { return score_; };
	void SetRatio(float ratio) { ratio_ = ratio; };
	float GetRatio() { return ratio_; };
	void PlusScore() { score_++; };
	void MinScore() { score_--; };
	UI* GetUI() { return pUI_; };
};