#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Gauge.h"
#include "../Mob/Mob.h"

//戦車本体を管理するクラス
class Tank : public Mob
{
    //定数
    const float     RUN_SPEED;          //移動速度
    const float     ROTATE_SPEED;       //回転速度
public:
    Tank(GameObject* parent);

    ~Tank();

    void ChildInitialize() override;

    void ChildUpdate() override;

    void ChildDraw() override;

    void ChildRelease() override;

    void OnCollision(GameObject* pTarget) override;
};