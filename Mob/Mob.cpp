#include "Mob.h"
#include "../Stage/Ground.h"

//コンストラクタ
Mob::Mob(GameObject* parent, std::string name)
    : GameObject(parent, name),
    prevPosition_(), useRotateDirMove_(false), useAlignGround_(true), hModel_(-1),modelName_()
{
}

void Mob::ModelLoad()
{
    hModel_ = Model::Load(modelName_);
    assert(hModel_ >= 0);
}

//初期化
void Mob::Initialize()
{
    ChildInitialize();

    ModelLoad();

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 150, 2.0f);
}

//更新
void Mob::Update()
{
    //前のフレーム
    prevPosition_ = XMLoadFloat3(&transform_.position_);

    ChildUpdate();

    //地面に沿わせるか
    if (useAlignGround_)
    {
        AlignGround();
    }

    //進行方向を向くか
    if (useRotateDirMove_)
    {
        RotateDirMove();
    }

    MoveLimit();
}

//描画
void Mob::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
    ChildDraw();
}

//開放
void Mob::Release()
{
    ChildRelease();
}

//進行方向を向く
void Mob::RotateDirMove()
{
    //現在の位置ベクトル
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //今回の移動ベクトル
    XMVECTOR move = nowPosition - prevPosition_;

    //移動ベクトルの長さを測る
    XMVECTOR length = XMVector3Length(move);

    //角度を求めるために長さを１にする（正規化）
    move = XMVector3Normalize(move);

    //基準となる奥向きのベクトル
    XMVECTOR front = { 0, 0, 1, 0 };

    //frontとmoveの内積を求める
    XMVECTOR vecDot = XMVector3Dot(front, move);
    float dot = XMVectorGetX(vecDot);

    //向いてる角度を求める（ラジアン）
    float angle_ = acos(dot);

    //frontとmoveの外積を求める
    XMVECTOR cross = XMVector3Cross(front, move);

    //外積の結果のYがマイナス　＝　下向き　＝　左に進んでる
    if (XMVectorGetY(cross) < 0)
    {
        angle_ *= -1;
    }

    //そのぶん回転させる
    transform_.rotate_.y = angle_ * PI_DEGREES / M_PI;
}

void Mob::AlignGround()
{
    //地面に沿わせる
    Ground* pGround = (Ground*)FindObject("Ground");
    int hGroundModel = pGround->GetModelHandle();

    RayCastData data;
    data.start = transform_.position_;
    data.start.y = 0;
    data.dir = XMFLOAT3(0, -1, 0);

    Model::RayCast(hGroundModel, &data);

    if (data.hit)
    {
        transform_.position_.y = -data.dist;
    }
}

void Mob::MoveLimit()
{
    //移動制限
    if (transform_.position_.x > LIMIT_POS)
    {
        transform_.position_.x = LIMIT_POS;
    }

    if (transform_.position_.x < -LIMIT_POS)
    {
        transform_.position_.x = -LIMIT_POS;
    }

    if (transform_.position_.z > LIMIT_POS)
    {
        transform_.position_.z = LIMIT_POS;
    }

    if (transform_.position_.z < -LIMIT_POS)
    {
        transform_.position_.z = -LIMIT_POS;
    }
}