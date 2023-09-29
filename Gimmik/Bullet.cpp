#include "Bullet.h"
#include "../Stage/Ground.h"
#include "../Stage/Water.h"
#include "../Engine/Model.h"
#include "../Enemy/Enemy.h"
#include "../Manager/EffectManager.h"
#include "../Manager/AudioManager.h"

//コンストラクタ
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet")
    , hModel_(-1), move_(XMFLOAT3(0.1f, 0.0, 0.0))
    , GRAVITY(0.03f),radius_(0.75f)
{
}

//デストラクタ
Bullet::~Bullet()
{
}

//初期化
void Bullet::Initialize()
{
    //モデルロード
    hModel_ = Model::Load("Model/Bullet.fbx");
    assert(hModel_ >= 0);

    //モデルサイズ
    transform_.scale_ = XMFLOAT3(0.5, 0.5f, 0.5f);

    //判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0, 0), radius_);
    AddCollider(collision);

    //アウトライン使う
    Model::SetOutLineDrawFlag(hModel_, true);
}

//更新
void Bullet::Update()
{
    //移動
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //重力
    move_.y -= GRAVITY;

    XMVECTOR vMove = XMLoadFloat3(&move_);
    XMStoreFloat3(&transform_.position_, vPos + vMove);

    {
        //地面に沿わせる
        Ground* pGround = (Ground*)FindObject("Ground");
        int hGroundModel = pGround->GetModelHandle();

        //レイ
        RayCastData data;
        data.start = transform_.position_;
        data.dir = XMFLOAT3(0, -1, 0);
        Model::RayCast(hGroundModel, &data);

        //消去
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
        //水面
        Water* pWater= (Water*)FindObject("Water");
        int hWaterModel = pWater->GetModelHandle();

        //レイ
        RayCastData data;
        data.start = transform_.position_;
        data.dir = XMFLOAT3(0, -1, 0);
        Model::RayCast(hWaterModel, &data);

        //消去
        if (data.dist <= 1.0f)
        {
            EffectManager::WaterEffect(transform_.position_);
            AudioManager::HitAudio();
            KillMe();
        }
    }

}

//描画
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bullet::Release()
{
}

//何かに当たった
void Bullet::OnCollision(GameObject* pTarget)
{
    //弾に当たった
    if (pTarget->GetObjectName() == "Enemy")
    {
        EffectManager::BombEffect(transform_.position_);
        EffectManager::DieEffect(transform_.position_);
        AudioManager::HitAudio();
        KillMe();
    }
}