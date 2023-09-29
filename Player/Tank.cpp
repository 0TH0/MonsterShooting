#include "Tank.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "Cannon.h"
#include "../Engine/Camera.h"
#include "../Stage/Ground.h"
#include "../Engine/SphereCollider.h"
#include "HP.h"

//�R���X�g���N�^
Tank::Tank(GameObject* parent)
    :Mob(parent, "Tank"),

    //�萔
    RUN_SPEED(0.3f),
    ROTATE_SPEED(3.0f)
{
}

//�f�X�g���N�^
Tank::~Tank()
{
}

void Tank::ChildInitialize()
{
    //���f���̃��[�h
    SetModelName("Model/TankBase.fbx");

    Model::SetOutLineDrawFlag(GetModelHandle(), true);
    Instantiate<Cannon>(this);
    Instantiate<HP>(this);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 1.75f);
    AddCollider(collision);
}

void Tank::ChildUpdate()
{
    //�ړ�
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

    //�n�ʂɉ��킹��
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


    XMFLOAT3 lrMove = { 0.01f, 0, 0 };	//���E�ړ�
    XMVECTOR vlrMove = XMLoadFloat3(&lrMove);
    XMMATRIX xRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    xRotate *= mRotate;							//��]�s��쐬
    vMove = XMVector3TransformCoord(vMove, mRotate); //�x�N�g��vMove���s��mRotate�ŕό`������
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