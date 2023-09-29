#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"
#include "../Engine/UI.h"

//Scoreを管理するクラス
class Score : public GameObject
{
	Text* pText_;//テキスト
	UI* pUI_;	//スコアUI
	int score_;	//スコア
	float ratio_;	//倍率
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Score(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//セッターゲッター
	void SetScore(int point) { score_ = point; };
	int GetScore() { return score_; };
	void SetRatio(float ratio) { ratio_ = ratio; };
	float GetRatio() { return ratio_; };
	void PlusScore() { score_++; };
	void MinScore() { score_--; };
	UI* GetUI() { return pUI_; };
};