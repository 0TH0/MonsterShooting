#include "Water.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Manager/EffectManager.h"

namespace
{
    static const float SCROOL = 0.0005f; //1�t���[���œ�������
    static const float posY = -5;
}

//�R���X�g���N�^
Water::Water(GameObject* parent)
    :GameObject(parent, "Water"), hModel_(-1),scroll_(0.f)
{
}

//�f�X�g���N�^
Water::~Water()
{
}

//������
void Water::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Model\\water.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = posY;
    Model::SetSahder(hModel_, Direct3D::SHADER_NORMALMAP);
    transform_.scale_ = { 2,1,2 };
}

//�X�V
void Water::Update()
{
    scroll_ += SCROOL;
    Model::SetUvScroll(hModel_, scroll_);
}

//�`��
void Water::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Water::Release()
{
}