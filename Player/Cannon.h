#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/PolyLine.h"
#include "../Gimmik/AssistBullet.h"

//砲台（戦車の上半分）を管理するクラス
class Cannon : public GameObject
{
    const float ROTATE_SPEED;       //回転速度
    const float ROTATE_LIMIT_PLUS;  //カメラ回転制限プラス
    const float ROTATE_LIMIT_MIN;   //カメラ回転制限マイナス
    int hModel_;                    //モデル番号
    bool canAssist_;                //アシストを使うか
    XMFLOAT3 shotPos;
    XMFLOAT3 cannonPos;
    XMVECTOR vshotPos;
    XMVECTOR vCannonPos;
    XMVECTOR root;
    XMFLOAT3 move_;
    AssistBullet* pAssistBullet_;
public:
    //コンストラクタ
    Cannon(GameObject* parent);

    //デストラクタ
    ~Cannon();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //カメラ制限
    void Cameralimit();

    //セッターゲッター
    XMFLOAT3 GetShotPos() { return shotPos; };
    XMFLOAT3 GetCannonPos() { return cannonPos; };
    XMVECTOR GetVshotPos() { return vshotPos; };
    XMVECTOR GetVCannonPos() { return vCannonPos; };
    bool GetCanAssist() { return canAssist_; };
    void SetCanAssist(bool canAssist) { canAssist_ = canAssist; };
};