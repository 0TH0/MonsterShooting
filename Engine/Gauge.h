#pragma once
#include "GameObject.h"

//体力ゲージを管理するクラス
class Gauge : public GameObject
{
    float nowHp_; //現在のＨＰ
    float maxHp_; //最大ＨＰ


    float stopRatio_;       //最大HPに対する固定されたゲージの割合
    float moveRatio_;       //最大HPに対する変化してるゲージの割合
    const float SPEED;      //バーの速度


    //使用する画像の種類
    enum
    {
        PICT_FRAME,
        PICT_GREEN,
        PICT_LGREEN,
        PICT_RED,
        PICT_MAX
    };

    //画像番号
    int hPict_[PICT_MAX];

public:
    //コンストラクタ
    Gauge(GameObject* parent, std::string name);

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //継承用の初期化
    virtual void ChildInitialize() {};
    //継承用の更新
    virtual void ChildUpdate() {};
    //継承用の描画
    virtual void ChildDraw() {};
    //継承用の開放
    virtual void ChildRelease() {};

    ////////////////////////////////////////

    //ダメージを受ける
    //引数：value  ダメージ量
    void Damage(float value);

    //回復
    //引数：value  回復量
    void Recovery(float value);

    //セッターゲッター
    void SetNowHP(float nowHp) { nowHp_ = nowHp; };
    float GetNowHP() { return nowHp_; };
    void SetMaxHP(float maxHp) { maxHp_ = maxHp; };
    float GetMaxHP() { return maxHp_; };
};