#include "Fade.h"
#include <cmath>
#include "../Engine/SceneManager.h"
#include "../Engine/Sprite.h"

//定数
namespace
{
	//フェードするときの加算する距離
	static const float FADE_ADD_DISTANCE = 10.0f;

	//フェードするときの加算する透明度
	static const float FADE_ADD_ALPHA = 0.01f;
}

//フェードを行うときに使う
namespace Fade
{

	///////////////////////////////変数//////////////////////////////////

	int fadeStatus_;    //フェードの状態
	float maxDistance_; //円フェードで使用する最大距離
	float nowDistance_; //円フェードで使用する今の距離

	//円フェード用の画像(シーンの数分)
	Sprite* pSprite_;

	//通常フェイド用の画像(黒)
	Sprite* pNormal_;
	Transform normal_;         //通常フェイド用の画像のトランスフォーム
	float normalAlpha_;        //通常フェイドの透明度

	///////////////////////////////関数//////////////////////////////////

	//初期化
	void Fade::Initialize()
	{
		pSprite_ = new Sprite();
		pSprite_->Load("Image/NormalFade.png");

		//通常用の画像ロード
		pNormal_ =  new Sprite();
		pNormal_->Load("Image/NormalFade.png");

		//各変数初期化
		normalAlpha_ =  ZERO;
		fadeStatus_ = NONE;
		maxDistance_ =  (float)(std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2)));
		nowDistance_ =  ZERO;
	}

	//描画
	void Fade::Draw()
	{
		//フェード用の描画
		FadeDraw();
	}

	///////////////////////////////セットゲット関数//////////////////////////////////

	//状態セット
	void Fade::SetFadeStatus(int status, std::string filename)
	{
		//もしファイルネームの記述があればノーマルフェイドの画像変更
		if(filename != "") pNormal_->Load(filename);

		//ステータス更新
		fadeStatus_ = status;

		//状態によって分ける
		switch (fadeStatus_)
		{

			//画像だけ描画
		case DRAW:

			NormalDraw();
			break;

			//円フェードイン
		case FADE_CIRCLE_IN:

			nowDistance_ =  ZERO;
			break;

			//円フェードアウト
		case FADE_CIRCLE_OUT:

			nowDistance_ =  maxDistance_;
			break;

			//通常フェードイン
		case FADE_NORMAL_IN:

			normalAlpha_ =  ZERO;
			break;

			//通常フェードアウト
		case FADE_NORMAL_OUT:

			normalAlpha_ =  1.0f;
			break;

			//それ以外
		default:

			break;
		}
	}

	//状態ゲット
	int Fade::GetFadeStatus() { return fadeStatus_; }

	//通常のフェードが透明じゃないかどうか
	bool isNormalFadeNotTransparency() { return (normalAlpha_ >= 1.0f); }

	///////////////////////////////フェード用関数////////////////////////////////////

	//フェード描画
	void Fade::FadeDraw()
	{
		//状態によって変える
		switch (fadeStatus_)
		{
			//画像だけ描画
		case DRAW:

			NormalDraw();
			break;

			//円フェードイン
		case FADE_CIRCLE_IN:

			FadeInCircleDraw();
			break;

			//円フェードアウト
		case FADE_CIRCLE_OUT:

			FadeOutCircleDraw();
			break;

			//通常フェードイン
		case FADE_NORMAL_IN:

			FadeInNormalDraw();
			break;

			//通常フェードアウト
		case FADE_NORMAL_OUT:

			FadeOutNormalDraw();
			break;

			//それ以外
		default:

			break;
		}

	}

	//描画
	void Fade::NormalDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//描画
		pSprite_->Draw(t, rect);
	}

	//円フェードイン描画
	void Fade::FadeInCircleDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//描画
		pSprite_->Draw(t, nowDistance_, rect);
	};

	//円フェードアウト描画
	void Fade::FadeOutCircleDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pSprite_->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ -= FADE_ADD_DISTANCE;

		if (nowDistance_ < ZERO)
			nowDistance_ = ZERO;

		//描画
		pSprite_->Draw(t, nowDistance_, rect);
	};

    //フェードイン描画
	void Fade::FadeInNormalDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pNormal_->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//徐々に透明じゃなく
		normalAlpha_ += FADE_ADD_ALPHA;

		//描画
		pNormal_->Draw(t, rect, XMFLOAT4(1, 1, 1, normalAlpha_));
	}

	//フェードアウト描画
	void Fade::FadeOutNormalDraw()
	{
		//画像用のtransform
		Transform t;

		//テクスチャのサイズ取得
		XMFLOAT3 size = pNormal_->GetTextureSize();

		//切り抜き範囲をリセット（画像全体を表示する）
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//徐々に透明に
		normalAlpha_ -= FADE_ADD_ALPHA;

		//描画
		pNormal_->Draw(t,rect, XMFLOAT4(1, 1, 1, normalAlpha_));
	}
}
