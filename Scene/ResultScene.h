#pragma once
#include "../Engine/GameObject.h"
#include "../Player/Score.h"

//■■シーンを管理するクラス
class ResultScene : public GameObject
{
	Score* pScore_;
	enum Button
	{
		PLAY = 0,
		TITLE,
		MAX_UI
	};

	UI* pUI_[MAX_UI];
	int btnID_;
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};