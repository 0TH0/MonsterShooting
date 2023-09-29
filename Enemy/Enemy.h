#pragma once
#include "../Mob/Mob.h"

class Enemy : public Mob
{
    float speed_;       //速度
    XMFLOAT3 goalPos_;  //向かう座標
    float damage_ = 50;      //プレイヤーに与えるダメージ

    //敵の種類
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

    //ランダムな位置
    int RandPosition();
};