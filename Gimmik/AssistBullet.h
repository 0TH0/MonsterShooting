#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/PolyLine.h"

//AssistBullet�V�[�����Ǘ�����N���X
class AssistBullet : public GameObject
{
	//�萔
	const float GRAVITY;	//�d��
	PolyLine* pLine_;		//�|�����C��
	Transform polyTrans_;	//�|�����C���̃g�����X�t�H�[��
	XMVECTOR root_;			//�A�V�X�g�̓�
	XMFLOAT3 assistMove_;	//�ړ�

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	AssistBullet(GameObject* parent);

	//�f�X�g���N�^
	~AssistBullet();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�Z�b�g
	void SetAssistMove(XMFLOAT3 assistMove) { assistMove_ = assistMove; }
	void SetPolyPos(XMFLOAT3 pos) { polyTrans_.position_ = pos; };
};