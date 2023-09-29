#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class Water : public GameObject
{
    int hModel_;    //���f���ԍ�
    float scroll_;  //���ʂ𓮂���
public:
    //�R���X�g���N�^
    Water(GameObject* parent);

    //�f�X�g���N�^
    ~Water();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    int GetModelHandle() { return hModel_; }
};