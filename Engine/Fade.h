#pragma once
#include <string>

//フェードの状態の列挙型
enum FadeStatus
{
	NONE,			 //何もしない
	DRAW,			 //画像だけ表示
	FADE_CIRCLE_IN,  //円のフェードイン
	FADE_CIRCLE_OUT, //円のフェードアウト
	FADE_NORMAL_IN,  //通常のフェードイン
	FADE_NORMAL_OUT, //通常のフェードアウト
};

//フェードを行うときに使う
namespace Fade
{
	//初期化
	void Initialize();

	//描画
	void Draw();

	//普通の画像を表示
	void NormalDraw();

	//状態によって呼ぶ関数分ける
	void FadeDraw();
	
	//フェードイン描画
	void FadeInCircleDraw();

	//フェードアウト描画
	void FadeOutCircleDraw();

	//フェードイン描画
	void FadeInNormalDraw();

	//フェードアウト描画
	void FadeOutNormalDraw();

	//状態をセット
	void SetFadeStatus(int status, std::string filename = "");

	//現在の状態を取得
	int GetFadeStatus();

	//通常のフェードが透明じゃないかどうか
	bool isNormalFadeNotTransparency();
}

