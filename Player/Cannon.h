#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/PolyLine.h"
#include "../Gimmik/AssistBullet.h"

//�C��i��Ԃ̏㔼���j���Ǘ�����N���X
class Cannon : public GameObject
{
    const float ROTATE_SPEED;       //��]���x
    const float ROTATE_LIMIT_PLUS;  //�J������]�����v���X
    const float ROTATE_LIMIT_MIN;   //�J������]�����}�C�i�X
    int hModel_;                    //���f���ԍ�
    bool canAssist_;                //�A�V�X�g���g����
    XMFLOAT3 shotPos;
    XMFLOAT3 cannonPos;
    XMVECTOR vshotPos;
    XMVECTOR vCannonPos;
    XMVECTOR root;
    XMFLOAT3 move_;
    AssistBullet* pAssistBullet_;
public:
    //�R���X�g���N�^
    Cannon(GameObject* parent);

    //�f�X�g���N�^
    ~Cannon();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�J��������
    void Cameralimit();

    //�Z�b�^�[�Q�b�^�[
    XMFLOAT3 GetShotPos() { return shotPos; };
    XMFLOAT3 GetCannonPos() { return cannonPos; };
    XMVECTOR GetVshotPos() { return vshotPos; };
    XMVECTOR GetVCannonPos() { return vCannonPos; };
    bool GetCanAssist() { return canAssist_; };
    void SetCanAssist(bool canAssist) { canAssist_ = canAssist; };
};