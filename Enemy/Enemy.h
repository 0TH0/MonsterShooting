#pragma once
#include "../Mob/Mob.h"

class Enemy : public Mob
{
    float speed_;       //���x
    XMFLOAT3 goalPos_;  //���������W
    float damage_ = 50;      //�v���C���[�ɗ^����_���[�W

    //�G�̎��
    enum EnemyType
    {
        PURPLE,
        RED
    } enemyType_;

public:
    Enemy(GameObject* parent);

    ~Enemy();

    void ChildInitialize() override;

    void ChildUpdate() override;

    void ChildDraw() override;

    void ChildRelease() override;

    void OnCollision(GameObject* pTarget) override;

    //�����_���Ȉʒu
    int RandPosition();
};