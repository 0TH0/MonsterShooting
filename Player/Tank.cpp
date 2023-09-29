#include "Tank.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "Cannon.h"
#include "../Engine/Camera.h"
#include "../Stage/Ground.h"
#include "../Engine/SphereCollider.h"
#include "HP.h"

//コンストラクタ
Tank::Tank(GameObject* parent)
    :Mob(parent, "Tank"),

    //定数
    RUN_SPEED(0.3f),
    ROTATE_SPEED(3.0f)
{
}

//デストラクタ
Tank::~Tank()
{
}

void Tank::ChildInitialize()
{
    //モデルのロード
    SetModelName("Model/TankBase.fbx");

    Model::SetOutLineDrawFlag(GetModelHandle(), true);
    Instantiate<Cannon>(this);
    Instantiate<HP>(this);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 1.75f);
    AddCollider(collision);
}

void Tank::ChildUpdate()
{
    //移動
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMFLOAT3 move = { 0, 0, RUN_SPEED };
    XMVECTOR vMove = XMLoadFloat3(&move);
    vMove = XMVector3TransformCoord(vMove, mRotate);

    if (Input::GetPadStickL().x > 0.8 || Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += ROTATE_SPEED;
    }

    if (Input::GetPadStickL().x < -0.8 || Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= ROTATE_SPEED;
    }
    if (Input::GetPadStickL().y > 0 || Input::IsKey(DIK_W))
    {
        vPos += vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }
    if (Input::GetPadStickL().y < 0 || Input::IsKey(DIK_S))
    {
        vPos -= vMove;
        XMStoreFloat3(&transform_.position_, vPos);
    }

    //地面に沿わせる
    Ground* pGround = (Ground*)FindObject("Ground");
    int hGroundModel = pGround->GetModelHandle();

    RayCastData data;
    data.start = transform_.position_;
    data.start.y = 0;
    data.dir = XMFLOAT3(0, -1, 0);
    Model::RayCast(hGroundModel, &data);

    if (data.hit)
    {
        transform_.position_.y = -data.dist;
    }


    XMFLOAT3 lrMove = { 0.01f, 0, 0 };	//左右移動
    XMVECTOR vlrMove = XMLoadFloat3(&lrMove);
    XMMATRIX xRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    xRotate *= mRotate;							//回転行列作成
    vMove = XMVector3TransformCoord(vMove, mRotate); //ベクトルvMoveを行列mRotateで変形させる
    vlrMove = XMVector3TransformCoord(vlrMove, mRotate);

    XMFLOAT3 cam = this->transform_.position_;
    XMVECTOR vCam = XMVectorSet(0, 5, -15, 0);
    vCam = XMVector3TransformCoord(vCam, xRotate);
    XMFLOAT3 camTar = transform_.position_;

    XMStoreFloat3(&cam, vPos + vCam);

    Camera::SetPosition(cam);
    Camera::SetTarget(camTar);
}

void Tank::ChildDraw()
{
}

void Tank::ChildRelease()
{
}

void Tank::OnCollision(GameObject* pTarget)
{
}