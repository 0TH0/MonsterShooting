#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class Sky : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Sky(GameObject* parent);

    //�f�X�g���N�^
    ~Sky();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};