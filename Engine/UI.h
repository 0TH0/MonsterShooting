#pragma once
#include "GameObject.h"

class UI : public GameObject
{
	int hPict_;
	std::string fileName_;
	bool isSelect_;	//�I�΂�Ă��邩
	bool useCursor_;//�J�[�\�����g����
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	UI(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	virtual void Load(std::string fileName);

	//�Q�[�^�[�Z�b�^�[
	int GetHandle() { return hPict_; };
	void SetIsSelect(bool flag) { isSelect_ = flag; };
	bool GetIsSelect() {return isSelect_;};
	void SetUseCursor(bool flag) { useCursor_ = flag; };
	bool GetUseCursor() { return useCursor_; };
};