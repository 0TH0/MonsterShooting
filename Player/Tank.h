#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Gauge.h"
#include "../Mob/Mob.h"

//��Ԗ{�̂��Ǘ�����N���X
class Tank : public Mob
{
    //�萔
    const float     RUN_SPEED;          //�ړ����x
    const float     ROTATE_SPEED;       //��]���x
public:
    Tank(GameObject* parent);

    ~Tank();

    void ChildInitialize() override;

    void ChildUpdate() override;

    void ChildDraw() override;

    void ChildRelease() override;

    void OnCollision(GameObject* pTarget) override;
};