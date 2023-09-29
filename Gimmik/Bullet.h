#pragma once
#include "../Engine/GameObject.h"

//■■シーンを管理するクラス
class Bullet : public GameObject
{
	//変数
	int hModel_; //モデル番号
	XMFLOAT3 move_; //移動
	//定数
	const float GRAVITY; //重力
	XMVECTOR root_;		  //
	float radius_;		  //当たり判定のサイズ

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bullet(GameObject* parent);

	//デストラクタ
	~Bullet();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//セット
	void SetMove(XMFLOAT3 move) { move_ = move; };

	//判定
	void OnCollision(GameObject* pTarget) override;
};