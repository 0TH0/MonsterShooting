#include "Water.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Manager/EffectManager.h"

namespace
{
    static const float SCROOL = 0.0005f; //1フレームで動かす量
    static const float posY = -5;
}

//コンストラクタ
Water::Water(GameObject* parent)
    :GameObject(parent, "Water"), hModel_(-1),scroll_(0.f)
{
}

//デストラクタ
Water::~Water()
{
}

//初期化
void Water::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Model\\water.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = posY;
    Model::SetSahder(hModel_, Direct3D::SHADER_NORMALMAP);
    transform_.scale_ = { 2,1,2 };
}

//更新
void Water::Update()
{
    scroll_ += SCROOL;
    Model::SetUvScroll(hModel_, scroll_);
}

//描画
void Water::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Water::Release()
{
}