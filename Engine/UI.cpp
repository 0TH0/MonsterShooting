#include "UI.h"
#include "Image.h"
#include "Input.h"

//�R���X�g���N�^
UI::UI(GameObject* parent)
	: GameObject(parent, "UI"),hPict_(-1),isSelect_(false),useCursor_(false)
{
}

//������
void UI::Initialize()
{
	//�摜�����[�h
	Load(fileName_);
}

//�X�V
void UI::Update()
{
	//�J�[�\������������������g����
	if (useCursor_)
	{
		//�J�[�\�����摜�ɓ������Ă�����
		if (Image::IsHitCursor(hPict_))
		{
			isSelect_ = true;
		}
		else
		{
			isSelect_ = false;
		}
	}
	//�I�΂�Ă�����
	if (isSelect_)
	{
		Image::SetColor(hPict_, 0.5f, 0.5f, 0.5f);
	}
	else
	{
		Image::SetColor(hPict_, 1, 1, 1);
	}
}

//�`��
void UI::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void UI::Release()
{
}

void UI::Load(std::string fileName)
{
	fileName_ = fileName;
	hPict_ = Image::Load(fileName_);
}