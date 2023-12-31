#pragma once
#include <list>
#include "Direct3D.h"
#include "Texture.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;
using namespace std;

class PolyLine
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMFLOAT4	color = XMFLOAT4(1, 1, 1, 1);
	} cb;

	//頂点情報
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 uv;
	};

	float width_;		//太さ
	int length_;		//長さ



	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;	//画像


	list<XMFLOAT3> positions_;	//過去length_回分の位置

public:
	//コンストラクタ
	PolyLine();


	//現在の位置を記憶させる
	//引数：pos	現在の位置
	void AddPosition(XMFLOAT3 pos);

	//ロード
	//引数：fileName	画像ファイル名
	//戻値：成功/失敗
	HRESULT Load(std::string fileName);

	//描画
	void Draw();

	//解放
	void Release();

	void SetColor(XMFLOAT4 color);

	XMFLOAT4 GetColor() { return cb.color; };

	void SetWidth(float w);
};

