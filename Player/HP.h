#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Gauge.h"

//HP���Ǘ�����N���X
class HP : public Gauge
{
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	HP(GameObject* parent);

	void ChildInitialize() override;

	void ChildUpdate() override;

	void ChildDraw() override;

	void ChildRelease() override;
};