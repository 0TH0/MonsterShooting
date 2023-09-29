#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"

static const float LIMIT_POS = 70;	//�ړ�����

//Mob���Ǘ�����N���X
class Mob : public GameObject
{
	int hModel_;			//���f���̔ԍ�
	XMVECTOR prevPosition_;	//�O�̃t���[���̍��W�x�N�g��
	bool useRotateDirMove_;	//�i�s������������
	bool useAlignGround_;	//�n�ʂɉ��킹�邩
	std::string modelName_; //�t�@�C���l�[���p�X
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Mob(GameObject* parent, std::string name);
	//������
	void Initialize() override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;
	//�J��
	void Release() override;
	//�p���p�̏�����
	virtual void ChildInitialize() {};
	//�p���p�̍X�V
	virtual void ChildUpdate() {};
	//�p���p�̕`��
	virtual void ChildDraw() {};
	//�p���p�̊J��
	virtual void ChildRelease() {};

	//���f���̃��[�h
	void ModelLoad();
	//�i�s����������
	void RotateDirMove();
	//�n�ʂɉ��킹��
	void AlignGround();
	//�ړ�����
	void MoveLimit();

	//�Z�b�^�[�Q�b�^�[
	void SetModelName(std::string modelNamePath) { modelName_ = modelNamePath; };
	void SetUseRotateDirMove(bool useRotateDirMove) { useRotateDirMove_ = useRotateDirMove; };
	bool GetUseRotateDirMove() { return useRotateDirMove_; };
	void SetUseAlignGround(bool useAlignGround) { useAlignGround_ = useAlignGround; };
	bool GetUseAlignGround() { return useAlignGround_; };

	int GetModelHandle() { return hModel_; };
};