#pragma once
#include "../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class Bullet : public GameObject
{
	//�ϐ�
	int hModel_; //���f���ԍ�
	XMFLOAT3 move_; //�ړ�
	//�萔
	const float GRAVITY; //�d��
	XMVECTOR root_;		  //
	float radius_;		  //�����蔻��̃T�C�Y

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Bullet(GameObject* parent);

	//�f�X�g���N�^
	~Bullet();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�Z�b�g
	void SetMove(XMFLOAT3 move) { move_ = move; };

	//����
	void OnCollision(GameObject* pTarget) override;
};