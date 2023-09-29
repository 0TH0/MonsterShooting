#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/UI.h"

//■■シーンを管理するクラス
class TitleScene : public GameObject
{
	//UIの名前
	enum UIName
	{
		TITLE = 0,
		TUTORIAL,
		PLAY,
		MAX_UI
	};

	//ボタン
	enum Button
	{
		BTN_TUTORIAL = 0,
		BTN_PLAY
	};

	UI* pUI_[MAX_UI];	//UI
	int btnID_;			//ボタンのid

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};