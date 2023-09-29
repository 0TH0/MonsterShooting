#pragma once
#include "../Engine/GameObject.h"
#include "../Player/Score.h"

//�����V�[�����Ǘ�����N���X
class ResultScene : public GameObject
{
	Score* pScore_;
	enum Button
	{
		PLAY = 0,
		TITLE,
		MAX_UI
	};

	UI* pUI_[MAX_UI];
	int btnID_;
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};