#include "Gauge.h"
#include "Image.h"

//コンストラクタ
Gauge::Gauge(GameObject* parent, std::string name)
    :GameObject(parent, name),
    hPict_{ -1,-1,-1 },
    stopRatio_((float)nowHp_ / (float)maxHp_), moveRatio_(stopRatio_),
    nowHp_(250),      //初期HP （適宜変更）
    maxHp_(250),      //MaxHP（適宜変更）
    SPEED(0.005f)     //バーの移動速度（お好みで）
{
}

//初期化
void Gauge::Initialize()
{
    //ゲージのサイズ（画像サイズが基準）
    transform_.scale_ = XMFLOAT3(1.5f, 1.5f, 1.0f);

    //ゲージの位置（画面中心が基準）
    transform_.position_ = XMFLOAT3(-0.95f, -0.7f, 0);



    //画像ファイルロード
    {
        //使用する画像ファイル名
        const char* fileName[] = { "Gauge\\Gauge_Frame.png", "Gauge\\Gauge_Green.png", "Gauge\\Gauge_LightGreen.png", "Gauge\\Gauge_Red.png" };

        //ロード
        for (int i = 0; i < PICT_MAX; i++)
        {
            hPict_[i] = Image::Load(fileName[i]);
            assert(hPict_[i] >= 0);
        }
    }

    ChildInitialize();
}

//更新
void Gauge::Update()
{
    //最大HPに対する、現在HPの割合
    stopRatio_ = (float)nowHp_ / (float)maxHp_;

    //バーを動かす
    if (moveRatio_ < stopRatio_) moveRatio_ += SPEED;
    if (moveRatio_ > stopRatio_) moveRatio_ -= SPEED;

    ChildUpdate();
}

//描画
void Gauge::Draw()
{

    Transform gaugeTrans;

    //HP変化なし
    if (abs(moveRatio_ - stopRatio_) < SPEED)
    {
        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }


    //回復中
    else if (moveRatio_ < stopRatio_)
    {
        //黄緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_LGREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_LGREEN]);

        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }

    //ダメージ中
    else
    {
        //赤ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[PICT_RED], gaugeTrans);
        Image::Draw(hPict_[PICT_RED]);

        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }



    //枠
    gaugeTrans = transform_;
    Image::SetTransform(hPict_[PICT_FRAME], gaugeTrans);
    Image::Draw(hPict_[PICT_FRAME]);

    ChildDraw();
}


//開放
void Gauge::Release()
{
    ChildRelease();
}

///////////////////////////////

//ダメージ
void Gauge::Damage(float value)
{
    nowHp_ -= value;
    if (nowHp_ < 0)    nowHp_ = 0;
}

//回復
void Gauge::Recovery(float value)
{
    nowHp_ += value;
    if (nowHp_ > maxHp_) nowHp_ = maxHp_;
}
