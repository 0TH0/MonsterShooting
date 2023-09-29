#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/PolyLine.h"

//AssistBulletシーンを管理するクラス
class AssistBullet : public GameObject
{
	//定数
	const float GRAVITY;	//重力
	PolyLine* pLine_;		//ポリライン
	Transform polyTrans_;	//ポリラインのトランスフォーム
	XMVECTOR root_;			//アシストの道
	XMFLOAT3 assistMove_;	//移動

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	AssistBullet(GameObject* parent);

	//デストラクタ
	~AssistBullet();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//セット
	void SetAssistMove(XMFLOAT3 assistMove) { assistMove_ = assistMove; }
	void SetPolyPos(XMFLOAT3 pos) { polyTrans_.position_ = pos; };
};