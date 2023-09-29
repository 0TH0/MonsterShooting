#include "Score.h"
#include "../Engine/Model.h"
#include "../Stage/Water.h"
#include "../Stage/Ground.h"
#include "../Manager/EffectManager.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
Score::Score(GameObject* parent)
    : GameObject(parent, "Score"),pText_(), score_(0),ratio_(1.f)
{
}

//������
void Score::Initialize()
{
    pUI_ = Instantiate<UI>(this);
    pUI_->Load("Image/Score.png");
    pText_ = new Text();
    pText_->Initialize("Image/Number.png", 128, 256, 10);
    transform_.position_ = XMFLOAT3(400, 80, 0);
}

//�X�V
void Score::Update()
{
}

//�`��
void Score::Draw()
{
    pText_->NumberDraw(transform_.position_.x, transform_.position_.y, score_, ratio_);
}

//�J��
void Score::Release()
{
}