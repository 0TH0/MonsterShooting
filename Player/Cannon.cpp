#include "Cannon.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Gimmik/Bullet.h"

Cannon::Cannon(GameObject* parent)
    :GameObject(parent, "Cannon"), ROTATE_SPEED(1.0f), ROTATE_LIMIT_MIN(-45.f), ROTATE_LIMIT_PLUS(20.f),
    hModel_(-1), canAssist_(true)
{
}


Cannon::~Cannon()
{
}


void Cannon::Initialize()
{
    //���f���̃��[�h
    hModel_ = Model::Load("Model/TankHead.fbx");
    assert(hModel_ >= 0);
    //�A�E�g���C���g��
    Model::SetOutLineDrawFlag(hModel_, true);
    //�e�̃A�V�X�g���g����
    if(canAssist_)
    { 
        pAssistBullet_ = Instantiate<AssistBullet>(this);
    }
}

void Cannon::Update()
{
    //���˂������
    shotPos = Model::GetBonePosition(hModel_, "shotPos");      //��[
    cannonPos = Model::GetBonePosition(hModel_, "cannonRoot");//���{
    vshotPos = XMLoadFloat3(&shotPos);
    vCannonPos = XMLoadFloat3(&cannonPos);
    root = (vshotPos - vCannonPos);
    //���K������
    root = XMVector3Normalize(root);//�x�N�g���̒������P�ɂ���
    XMFLOAT3 shot;
    XMStoreFloat3(&shot, root);

    //����
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) || Input::IsKeyDown(DIK_SPACE))
    {
        Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());

        pBullet->SetPosition(shotPos);
        pBullet->SetMove(shot);
    }

    //��]
    if (Input::GetPadStickR().x > 0 || Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += ROTATE_SPEED;
    }
    if (Input::GetPadStickR().x < 0 || Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= ROTATE_SPEED;
    }
    if (Input::GetPadStickR().y > 0 || Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += ROTATE_SPEED;
    }
    if (Input::GetPadStickR().y < 0 || Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= ROTATE_SPEED;
    }

    //�A�V�X�g
    if (canAssist_)
    {
        pAssistBullet_->SetPolyPos(shotPos);
        pAssistBullet_->SetAssistMove(shot);
    }

    //�J��������
    Cameralimit();
}

void Cannon::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Cannon::Release()
{
}

void Cannon::Cameralimit()
{
    if (transform_.rotate_.x < ROTATE_LIMIT_MIN)
    {
        transform_.rotate_.x = ROTATE_LIMIT_MIN;
    }
    if (transform_.rotate_.x > ROTATE_LIMIT_PLUS)
    {
        transform_.rotate_.x = ROTATE_LIMIT_PLUS;
    }
}
