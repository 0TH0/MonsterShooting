#pragma once
#include "GameObject.h"

//�̗̓Q�[�W���Ǘ�����N���X
class Gauge : public GameObject
{
    float nowHp_; //���݂̂g�o
    float maxHp_; //�ő�g�o


    float stopRatio_;       //�ő�HP�ɑ΂���Œ肳�ꂽ�Q�[�W�̊���
    float moveRatio_;       //�ő�HP�ɑ΂���ω����Ă�Q�[�W�̊���
    const float SPEED;      //�o�[�̑��x


    //�g�p����摜�̎��
    enum
    {
        PICT_FRAME,
        PICT_GREEN,
        PICT_LGREEN,
        PICT_RED,
        PICT_MAX
    };

    //�摜�ԍ�
    int hPict_[PICT_MAX];

public:
    //�R���X�g���N�^
    Gauge(GameObject* parent, std::string name);

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�p���p�̏�����
    virtual void ChildInitialize() {};
    //�p���p�̍X�V
    virtual void ChildUpdate() {};
    //�p���p�̕`��
    virtual void ChildDraw() {};
    //�p���p�̊J��
    virtual void ChildRelease() {};

    ////////////////////////////////////////

    //�_���[�W���󂯂�
    //�����Fvalue  �_���[�W��
    void Damage(float value);

    //��
    //�����Fvalue  �񕜗�
    void Recovery(float value);

    //�Z�b�^�[�Q�b�^�[
    void SetNowHP(float nowHp) { nowHp_ = nowHp; };
    float GetNowHP() { return nowHp_; };
    void SetMaxHP(float maxHp) { maxHp_ = maxHp; };
    float GetMaxHP() { return maxHp_; };
};