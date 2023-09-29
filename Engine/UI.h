#pragma once
#include "GameObject.h"

class UI : public GameObject
{
	int hPict_;
	std::string fileName_;
	bool isSelect_;	//選ばれているか
	bool useCursor_;//カーソルを使うか
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	UI(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	virtual void Load(std::string fileName);

	//ゲーターセッター
	int GetHandle() { return hPict_; };
	void SetIsSelect(bool flag) { isSelect_ = flag; };
	bool GetIsSelect() {return isSelect_;};
	void SetUseCursor(bool flag) { useCursor_ = flag; };
	bool GetUseCursor() { return useCursor_; };
};