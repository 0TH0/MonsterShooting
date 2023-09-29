#include "AssistBullet.h"
#include "../Stage/Ground.h"
#include "../Stage/Water.h"
#include "../Engine/Model.h"
#include "../Manager/EffectManager.h"
#include "../Manager/AudioManager.h"

namespace
{
    const int MAX_POLY_LENGTH = 80;  //ポリラインの最大の長さ
}


//コンストラクタ
AssistBullet::AssistBullet(GameObject* parent)
    :GameObject(parent, "AssistBullet"), GRAVITY(0.03f)
{
}

//デストラクタ
AssistBullet::~AssistBullet()
{
}

//初期化
void AssistBullet::Initialize()
{
    pLine_ = new PolyLine();
    pLine_->Load("Image\\normalfade.png");
    pLine_->SetWidth(0.2f);
}

//更新
void AssistBullet::Update()
{
    for (int i = 0; i < MAX_POLY_LENGTH; i++)
    {
        pLine_->AddPosition(polyTrans_.position_);

        //移動
        XMVECTOR vPos = XMLoadFloat3(&polyTrans_.position_);
        //重力
        assistMove_.y -= GRAVITY;

        XMVECTOR vMove = XMLoadFloat3(&assistMove_);
        XMStoreFloat3(&polyTrans_.position_, vPos + vMove);
    }
}

//描画
void AssistBullet::Draw()
{
    pLine_->Draw();
}

//開放
void AssistBullet::Release()
{
    pLine_->Release();
}