#include "AudioManager.h"
#include "../Engine/Audio.h"

// �l�X�ȉ����Ǘ�����
namespace AudioManager
{
	int hClickAudio;			   //�N���b�N��
	int hHitAudio;				   //�q�b�g��
	int hPlayBGM;				   //�v���CBGM
	int hTitleBGM;				   //�^�C�g��BGM
	int hWinAudio;					//��������
	int hLoseAudio;					//��������
	int hSmokeAudio;				//���̉�
	int hJumpAudio;					//�W�����v������
	int hStarAudio;					//���̉�
	int hDieAudio;					//���񂾉�
	int hBtnMoveAudio;				//��������
	int hBtnSelectAudio;			//�I�񂾉�
	
	//������
	void Initialize()
	{
		hClickAudio = Audio::Load("Audio/click.wav");
		assert(hClickAudio >= ZERO);

		hHitAudio = Audio::Load("Audio/hit.wav");
		assert(hHitAudio >= ZERO);

		hPlayBGM = Audio::Load("Audio/BGM.wav");
		assert(hPlayBGM >= ZERO);

		hTitleBGM = Audio::Load("Audio/titleBGM.wav");
		assert(hTitleBGM >= ZERO);

		hWinAudio = Audio::Load("Audio/win.wav");
		assert(hWinAudio >= ZERO);

		hLoseAudio = Audio::Load("Audio/lose.wav");
		assert(hLoseAudio >= ZERO);

		hSmokeAudio = Audio::Load("Audio/smoke.wav");
		assert(hSmokeAudio >= ZERO);

		hJumpAudio = Audio::Load("Audio/jump.wav");
		assert(hJumpAudio >= ZERO);

		hStarAudio = Audio::Load("Audio/star.wav");
		assert(hStarAudio >= ZERO);

		hDieAudio = Audio::Load("Audio/die.wav");
		assert(hDieAudio >= ZERO);

		hBtnMoveAudio = Audio::Load("Audio/Move.wav");
		assert(hBtnMoveAudio >= ZERO);

		hBtnSelectAudio = Audio::Load("Audio/Select.wav");	
		assert(hBtnSelectAudio >= ZERO);
	}

	// �V�[���J�ڂ̎��̏�����
	void SceneTransitionInitialize()
	{
		Initialize();
	}

	void ClickAudio() { Audio::Play(hClickAudio); }
	void HitAudio() { Audio::Play(hHitAudio); }
	void PlayBGM(){ Audio::PlayLoop(hPlayBGM); }
	void TitleBGM() { Audio::PlayLoop(hTitleBGM); }
	void WinAudio() { Audio::Play(hWinAudio); }
	void LoseAudio() { Audio::Play(hLoseAudio); }
	void JumpAudio() { Audio::Play(hJumpAudio); }
	void SmokeAudio() { Audio::Play(hSmokeAudio); }
	void StarAudio() { Audio::Play(hStarAudio); }
	void DieAudio() { Audio::Play(hDieAudio); }
	void BtnSelectAudio() { Audio::Play(hBtnSelectAudio); };
	void BtnMoveAudio() { Audio::Play(hBtnMoveAudio); };
	void StopPlayBGM() { Audio::Stop(hPlayBGM); };
	void StopTitleBGM() { Audio::Stop(hTitleBGM); };
}