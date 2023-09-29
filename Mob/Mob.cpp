#include "Mob.h"
#include "../Stage/Ground.h"

//�R���X�g���N�^
Mob::Mob(GameObject* parent, std::string name)
    : GameObject(parent, name),
    prevPosition_(), useRotateDirMove_(false), useAlignGround_(true), hModel_(-1),modelName_()
{
}

void Mob::ModelLoad()
{
    hModel_ = Model::Load(modelName_);
    assert(hModel_ >= 0);
}

//������
void Mob::Initialize()
{
    ChildInitialize();

    ModelLoad();

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, 0, 150, 2.0f);
}

//�X�V
void Mob::Update()
{
    //�O�̃t���[��
    prevPosition_ = XMLoadFloat3(&transform_.position_);

    ChildUpdate();

    //�n�ʂɉ��킹�邩
    if (useAlignGround_)
    {
        AlignGround();
    }

    //�i�s������������
    if (useRotateDirMove_)
    {
        RotateDirMove();
    }

    MoveLimit();
}

//�`��
void Mob::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
    ChildDraw();
}

//�J��
void Mob::Release()
{
    ChildRelease();
}

//�i�s����������
void Mob::RotateDirMove()
{
    //���݂̈ʒu�x�N�g��
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //����̈ړ��x�N�g��
    XMVECTOR move = nowPosition - prevPosition_;

    //�ړ��x�N�g���̒����𑪂�
    XMVECTOR length = XMVector3Length(move);

    //�p�x�����߂邽�߂ɒ������P�ɂ���i���K���j
    move = XMVector3Normalize(move);

    //��ƂȂ鉜�����̃x�N�g��
    XMVECTOR front = { 0, 0, 1, 0 };

    //front��move�̓��ς����߂�
    XMVECTOR vecDot = XMVector3Dot(front, move);
    float dot = XMVectorGetX(vecDot);

    //�����Ă�p�x�����߂�i���W�A���j
    float angle_ = acos(dot);

    //front��move�̊O�ς����߂�
    XMVECTOR cross = XMVector3Cross(front, move);

    //�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
    if (XMVectorGetY(cross) < 0)
    {
        angle_ *= -1;
    }

    //���̂Ԃ��]������
    transform_.rotate_.y = angle_ * PI_DEGREES / M_PI;
}

void Mob::AlignGround()
{
    //�n�ʂɉ��킹��
    Ground* pGround = (Ground*)FindObject("Ground");
    int hGroundModel = pGround->GetModelHandle();

    RayCastData data;
    data.start = transform_.position_;
    data.start.y = 0;
    data.dir = XMFLOAT3(0, -1, 0);

    Model::RayCast(hGroundModel, &data);

    if (data.hit)
    {
        transform_.position_.y = -data.dist;
    }
}

void Mob::MoveLimit()
{
    //�ړ�����
    if (transform_.position_.x > LIMIT_POS)
    {
        transform_.position_.x = LIMIT_POS;
    }

    if (transform_.position_.x < -LIMIT_POS)
    {
        transform_.position_.x = -LIMIT_POS;
    }

    if (transform_.position_.z > LIMIT_POS)
    {
        transform_.position_.z = LIMIT_POS;
    }

    if (transform_.position_.z < -LIMIT_POS)
    {
        transform_.position_.z = -LIMIT_POS;
    }
}