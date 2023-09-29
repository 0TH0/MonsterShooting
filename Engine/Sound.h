#pragma once
#include <string>
#include <dsound.h>

// ライブラリリンク
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")


//-----------------------------------------------------------
//DirectSoundを使ったサウンド再生クラス
//-----------------------------------------------------------
class Sound
{
    LPDIRECTSOUND8			    pDSound_;	//DirectSoundオブジェクト
    LPDIRECTSOUNDBUFFER	pPrimary_;	//プライマリバッファ

    //プライマリバッファの作成
    void CreatePrimaryBuffer();

public:
    Sound();
    ~Sound();

    //初期化
    //引数：hWnd	ウィンドウハンドル
    void Initialize(HWND hWnd);

    //ファイルのロード
    //引数：dsb			サウンドバッファ
    //引数：fileName	ファイル名
    HRESULT Load(LPDIRECTSOUNDBUFFER* dsb, const std::string& fileName) const;

    //再生
    //引数：dsb	サウンドバッファ
    static void Play(LPDIRECTSOUNDBUFFER* dsb);

    //再生
    //引数：dsb	サウンドバッファ
    static void PlayLoop(LPDIRECTSOUNDBUFFER* dsb);

    //停止
    //引数：dsb	サウンドバッファ
    static void Stop(LPDIRECTSOUNDBUFFER* dsb);


    //開放
    void Release() const;
};