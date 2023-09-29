#include "Sky.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Manager/EffectManager.h"

namespace
{
    static const float SCROOL = 0.0005f; //1フレームで動かす量
    static const float posY = 0;
}

//コンストラクタ
Sky::Sky(GameObject* parent)
    :GameObject(parent, "Sky"), hModel_(-1)
{
}

//デストラクタ
Sky::~Sky()
{
}

//初期化
void Sky::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Model\\BackSky.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = posY;
    transform_.scale_ = {6,6,6};
}

//更新
void Sky::Update()
{
    transform_.rotate_.y += 0.1f;
}

//描画
void Sky::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Sky::Release()
{
}