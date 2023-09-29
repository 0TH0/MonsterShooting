#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/UI.h"

//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	//UI�̖��O
	enum UIName
	{
		TITLE = 0,
		TUTORIAL,
		PLAY,
		MAX_UI
	};

	//�{�^��
	enum Button
	{
		BTN_TUTORIAL = 0,
		BTN_PLAY
	};

	UI* pUI_[MAX_UI];	//UI
	int btnID_;			//�{�^����id

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};