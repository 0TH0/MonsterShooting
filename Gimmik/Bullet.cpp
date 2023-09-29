#include "Bullet.h"
#include "../Stage/Ground.h"
#include "../Stage/Water.h"
#include "../Engine/Model.h"
#include "../Enemy/Enemy.h"
#include "../Manager/EffectManager.h"
#include "../Manager/AudioManager.h"

//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet")
    , hModel_(-1), move_(XMFLOAT3(0.1f, 0.0, 0.0))
    , GRAVITY(0.03f),radius_(0.75f)
{
}

//�f�X�g���N�^
Bullet::~Bullet()
{
}

//������
void Bullet::Initialize()
{
    //���f�����[�h
    hModel_ = Model::Load("Model/Bullet.fbx");
    assert(hModel_ >= 0);

    //���f���T�C�Y
    transform_.scale_ = XMFLOAT3(0.5, 0.5f, 0.5f);

    //����
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0, 0), radius_);
    AddCollider(collision);

    //�A�E�g���C���g��
    Model::SetOutLineDrawFlag(hModel_, true);
}

//�X�V
void Bullet::Update()
{
    //�ړ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //�d��
    move_.y -= GRAVITY;

    XMVECTOR vMove = XMLoadFloat3(&move_);
    XMStoreFloat3(&transform_.position_, vPos + vMove);

    {
        //�n�ʂɉ��킹��
        Ground* pGround = (Ground*)FindObject("Ground");
        int hGroundModel = pGround->GetModelHandle();

        //���C
        RayCastData data;
        data.start = transform_.position_;
        data.dir = XMFLOAT3(0, -1, 0);
        Model::RayCast(hGroundModel, &data);

        //����
        if (data.dist <= 1.0f)
        {
            SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0, 0), radius_ * 5);
            AddCollider(collision);

            EffectManager::BombEffect(transform_.position_);
            EffectManager::DieEffect(transform_.position_);
            AudioManager::HitAudio();
            KillMe();
        }
    }
    {
        //����
        Water* pWater= (Water*)FindObject("Water");
        int hWaterModel = pWater->GetModelHandle();

        //���C
        RayCastData data;
        data.start = transform_.position_;
        data.dir = XMFLOAT3(0, -1, 0);
        Model::RayCast(hWaterModel, &data);

        //����
        if (data.dist <= 1.0f)
        {
            EffectManager::WaterEffect(transform_.position_);
            AudioManager::HitAudio();
            KillMe();
        }
    }

}

//�`��
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Bullet::Release()
{
}

//�����ɓ�������
void Bullet::OnCollision(GameObject* pTarget)
{
    //�e�ɓ�������
    if (pTarget->GetObjectName() == "Enemy")
    {
        EffectManager::BombEffect(transform_.position_);
        EffectManager::DieEffect(transform_.position_);
        AudioManager::HitAudio();
        KillMe();
    }
}