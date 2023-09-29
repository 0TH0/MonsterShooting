#include "AssistBullet.h"
#include "../Stage/Ground.h"
#include "../Stage/Water.h"
#include "../Engine/Model.h"
#include "../Manager/EffectManager.h"
#include "../Manager/AudioManager.h"

namespace
{
    const int MAX_POLY_LENGTH = 80;  //�|�����C���̍ő�̒���
}


//�R���X�g���N�^
AssistBullet::AssistBullet(GameObject* parent)
    :GameObject(parent, "AssistBullet"), GRAVITY(0.03f)
{
}

//�f�X�g���N�^
AssistBullet::~AssistBullet()
{
}

//������
void AssistBullet::Initialize()
{
    pLine_ = new PolyLine();
    pLine_->Load("Image\\normalfade.png");
    pLine_->SetWidth(0.2f);
}

//�X�V
void AssistBullet::Update()
{
    for (int i = 0; i < MAX_POLY_LENGTH; i++)
    {
        pLine_->AddPosition(polyTrans_.position_);

        //�ړ�
        XMVECTOR vPos = XMLoadFloat3(&polyTrans_.position_);
        //�d��
        assistMove_.y -= GRAVITY;

        XMVECTOR vMove = XMLoadFloat3(&assistMove_);
        XMStoreFloat3(&polyTrans_.position_, vPos + vMove);
    }
}

//�`��
void AssistBullet::Draw()
{
    pLine_->Draw();
}

//�J��
void AssistBullet::Release()
{
    pLine_->Release();
}