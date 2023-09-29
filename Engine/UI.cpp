#include "UI.h"
#include "Image.h"
#include "Input.h"

//コンストラクタ
UI::UI(GameObject* parent)
	: GameObject(parent, "UI"),hPict_(-1),isSelect_(false),useCursor_(false)
{
}

//初期化
void UI::Initialize()
{
	//画像をロード
	Load(fileName_);
}

//更新
void UI::Update()
{
	//カーソルが当たった判定を使うか
	if (useCursor_)
	{
		//カーソルが画像に当たっていたら
		if (Image::IsHitCursor(hPict_))
		{
			isSelect_ = true;
		}
		else
		{
			isSelect_ = false;
		}
	}
	//選ばれていたら
	if (isSelect_)
	{
		Image::SetColor(hPict_, 0.5f, 0.5f, 0.5f);
	}
	else
	{
		Image::SetColor(hPict_, 1, 1, 1);
	}
}

//描画
void UI::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void UI::Release()
{
}

void UI::Load(std::string fileName)
{
	fileName_ = fileName;
	hPict_ = Image::Load(fileName_);
}