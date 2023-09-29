#include "Enemy.h"
#include "../Stage/Ground.h"
#include "../Manager/AudioManager.h"
#include "../Engine/SphereCollider.h"
#include "../Manager/GameManager.h"
#include "../Player/Tank.h"
#include "../Manager/EffectManager.h"
#include "../Engine/Color.h"
#include "../Player/Score.h"
#include "../Player/HP.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
: Mob(parent, "Enemy")
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::ChildInitialize()
{
    //モデルセット
    enemyType_ = (EnemyType)RandInt(0, 1);
    if (enemyType_)
    {
        SetModelName("Model/EnemyPurple.fbx");
    }
    else
    {
        SetModelName("Model/Enemy.fbx");
    }

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 2.5f, 0.0f), 3.f);
    AddCollider(collision);

    //サイズ
    transform_.scale_ = XMFLOAT3(4.0f, 4.0f, 4.0f);

    //位置
    transform_.position_.x = RandPosition();
    transform_.position_.y = -10;
    transform_.position_.z = RandPosition();

    //スピード
    speed_ = RandInt(1,5);

    //進行方向を向く
    SetUseRotateDirMove(true);
}

void Enemy::ChildUpdate()
{
    //プレイシーン
    if (GameManager::GetpSceneManager()->GetScene() == SCENE_ID_PLAY)
    {
        Tank* pTank = (Tank*)FindObject("Tank");
        goalPos_ = pTank->GetPosition();


        //プレイヤーに向かって移動
        transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_),
            XMLoadFloat3(&goalPos_), 0.001f * speed_));
    }
}

void Enemy::ChildDraw()
{
}

void Enemy::ChildRelease()
{
}

//何かに当たった
void Enemy::OnCollision(GameObject* pTarget)
{
    //弾に当たった
    if (pTarget->GetObjectName() == "Bullet")
    {
        //スコア＋１
        Score* pScore = (Score*)FindObject("Score");
        pScore->PlusScore();
        GameManager::SetScore(pScore->GetScore());

        AudioManager::DieAudio();
        KillMe();
    }

    if (pTarget->GetObjectName() == "Tank")
    {
        HP* pHP = (HP*)FindObject("HP");
        pHP->Damage(damage_);

        AudioManager::HitAudio();
        KillMe();
    }
}

int Enemy::RandPosition()
{
    return RandInt(-LIMIT_POS, LIMIT_POS);
}