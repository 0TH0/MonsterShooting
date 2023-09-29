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

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
: Mob(parent, "Enemy")
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::ChildInitialize()
{
    //���f���Z�b�g
    enemyType_ = (EnemyType)RandInt(0, 1);
    if (enemyType_)
    {
        SetModelName("Model/EnemyPurple.fbx");
    }
    else
    {
        SetModelName("Model/Enemy.fbx");
    }

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 2.5f, 0.0f), 3.f);
    AddCollider(collision);

    //�T�C�Y
    transform_.scale_ = XMFLOAT3(4.0f, 4.0f, 4.0f);

    //�ʒu
    transform_.position_.x = RandPosition();
    transform_.position_.y = -10;
    transform_.position_.z = RandPosition();

    //�X�s�[�h
    speed_ = RandInt(1,5);

    //�i�s����������
    SetUseRotateDirMove(true);
}

void Enemy::ChildUpdate()
{
    //�v���C�V�[��
    if (GameManager::GetpSceneManager()->GetScene() == SCENE_ID_PLAY)
    {
        Tank* pTank = (Tank*)FindObject("Tank");
        goalPos_ = pTank->GetPosition();


        //�v���C���[�Ɍ������Ĉړ�
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

//�����ɓ�������
void Enemy::OnCollision(GameObject* pTarget)
{
    //�e�ɓ�������
    if (pTarget->GetObjectName() == "Bullet")
    {
        //�X�R�A�{�P
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