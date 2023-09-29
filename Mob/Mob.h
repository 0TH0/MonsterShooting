#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"

static const float LIMIT_POS = 70;	//移動制限

//Mobを管理するクラス
class Mob : public GameObject
{
	int hModel_;			//モデルの番号
	XMVECTOR prevPosition_;	//前のフレームの座標ベクトル
	bool useRotateDirMove_;	//進行方向を向くか
	bool useAlignGround_;	//地面に沿わせるか
	std::string modelName_; //ファイルネームパス
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Mob(GameObject* parent, std::string name);
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

	//モデルのロード
	void ModelLoad();
	//進行方向を向く
	void RotateDirMove();
	//地面に沿わせる
	void AlignGround();
	//移動制限
	void MoveLimit();

	//セッターゲッター
	void SetModelName(std::string modelNamePath) { modelName_ = modelNamePath; };
	void SetUseRotateDirMove(bool useRotateDirMove) { useRotateDirMove_ = useRotateDirMove; };
	bool GetUseRotateDirMove() { return useRotateDirMove_; };
	void SetUseAlignGround(bool useAlignGround) { useAlignGround_ = useAlignGround; };
	bool GetUseAlignGround() { return useAlignGround_; };

	int GetModelHandle() { return hModel_; };
};