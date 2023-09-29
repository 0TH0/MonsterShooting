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
    //モデルのロード
    hModel_ = Model::Load("Model/TankHead.fbx");
    assert(hModel_ >= 0);
    //アウトライン使う
    Model::SetOutLineDrawFlag(hModel_, true);
    //弾のアシストを使うか
    if(canAssist_)
    { 
        pAssistBullet_ = Instantiate<AssistBullet>(this);
    }
}

void Cannon::Update()
{
    //発射する方向
    shotPos = Model::GetBonePosition(hModel_, "shotPos");      //先端
    cannonPos = Model::GetBonePosition(hModel_, "cannonRoot");//根本
    vshotPos = XMLoadFloat3(&shotPos);
    vCannonPos = XMLoadFloat3(&cannonPos);
    root = (vshotPos - vCannonPos);
    //正規化する
    root = XMVector3Normalize(root);//ベクトルの長さを１にして
    XMFLOAT3 shot;
    XMStoreFloat3(&shot, root);

    //発射
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) || Input::IsKeyDown(DIK_SPACE))
    {
        Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());

        pBullet->SetPosition(shotPos);
        pBullet->SetMove(shot);
    }

    //回転
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

    //アシスト
    if (canAssist_)
    {
        pAssistBullet_->SetPolyPos(shotPos);
        pAssistBullet_->SetAssistMove(shot);
    }

    //カメラ制限
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
