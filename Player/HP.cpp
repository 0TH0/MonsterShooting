#include "HP.h"

//コンストラクタ
HP::HP(GameObject* parent)
    : Gauge(parent, "HP")
{
}

void HP::ChildInitialize()
{
    transform_.scale_ = {3,3,5};
}

void HP::ChildUpdate()
{
}

void HP::ChildDraw()
{
}

void HP::ChildRelease()
{
}