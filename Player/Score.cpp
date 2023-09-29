#include "Score.h"
#include "../Engine/Model.h"
#include "../Stage/Water.h"
#include "../Stage/Ground.h"
#include "../Manager/EffectManager.h"
#include "../Engine/Input.h"

//コンストラクタ
Score::Score(GameObject* parent)
    : GameObject(parent, "Score"),pText_(), score_(0),ratio_(1.f)
{
}

//初期化
void Score::Initialize()
{
    pUI_ = Instantiate<UI>(this);
    pUI_->Load("Image/Score.png");
    pText_ = new Text();
    pText_->Initialize("Image/Number.png", 128, 256, 10);
    transform_.position_ = XMFLOAT3(400, 80, 0);
}

//更新
void Score::Update()
{
}

//描画
void Score::Draw()
{
    pText_->NumberDraw(transform_.position_.x, transform_.position_.y, score_, ratio_);
}

//開放
void Score::Release()
{
}