#pragma once
#include "../Engine/GameObject.h"

namespace EffectManager
{
	//�d�C
	void ElectricEffect(XMFLOAT3 pos);
	//���e
	void BombEffect(XMFLOAT3 pos);
	//�G
	void EnemyEffect(XMFLOAT3, XMFLOAT4 color);
	//�A�C�e��
	void TakeItemBoxEffect(XMFLOAT3 pos);
	//��
	void SmokeEffect(XMFLOAT3 pos, XMFLOAT4 color);
	//��
	void StarEffect(XMFLOAT3 pos);
	//��
	void RiverEffect(XMFLOAT3 pos);
	//����
	void DieEffect(XMFLOAT3 pos);
	//��
	void WaterEffect(XMFLOAT3 pos);
};