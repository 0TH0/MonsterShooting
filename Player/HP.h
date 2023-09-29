#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Gauge.h"

//HPを管理するクラス
class HP : public Gauge
{
public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	HP(GameObject* parent);

	void ChildInitialize() override;

	void ChildUpdate() override;

	void ChildDraw() override;

	void ChildRelease() override;
};