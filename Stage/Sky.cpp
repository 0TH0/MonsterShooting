#include "Sky.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Manager/EffectManager.h"

namespace
{
    static const float SCROOL = 0.0005f; //1�t���[���œ�������
    static const float posY = 0;
}

//�R���X�g���N�^
Sky::Sky(GameObject* parent)
    :GameObject(parent, "Sky"), hModel_(-1)
{
}

//�f�X�g���N�^
Sky::~Sky()
{
}

//������
void Sky::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Model\\BackSky.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = posY;
    transform_.scale_ = {6,6,6};
}

//�X�V
void Sky::Update()
{
    transform_.rotate_.y += 0.1f;
}

//�`��
void Sky::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Sky::Release()
{
}