#pragma once
#include "stdafx.h"
#include "DescriptorPool.h"
#include "Sprite.h"
#include "Terrain.h"
#include "Hook.h"

//�V�[���Ǘ��N���X
class Scene
{
public:
	Scene();
	~Scene();
	bool Init(ID3D12Device* pDevice, ID3D12CommandQueue* pQueue, DescriptorPool* pPool, UINT width, UINT height);
	void Term();
	void DrawSprite(ID3D12GraphicsCommandList* pCmdList);
	void OnUpdate(unsigned char* key);
	
private:
	//�L�[�̏��
	enum INPUT_STATE
	{
		NOT_PUSH = 0,	// ������ĂȂ�
		PUSH_ENTER,	// �����ꂽ�u��
		PUSH,		// ������Ă�
		PUSH_EXIT,	// �����ꂽ�u��
	};

	// �Q�[���Ŏg���L�[���
	enum KEY_INFO
	{
		JUMP_KEY = 0,
		HOOK_KEY,
		LEFT_KEY,
		RIHGT_KEY,
		MAX_KEY_INFO,
	};

	// ���C�u�������L�[���z��
	// �萔��DirectInput�ŗp�ӂ���Ă���DIK_�`���g�p����
	int m_KeyInfo[4] = {
		DIK_W,
		DIK_P,
		DIK_A,
		DIK_D
	};

	//�t�b�N�V���b�g(��)�̏��
	enum HOOK_STATE
	{
		SHOOTING=0,
		RETURNING,
		HANGING,
		HANGING_ENEMY,
		H_IDLING
	};

	//���@�̏��
	enum PLAYER_STATE
	{
		IDLING = 0,
		P_H_IDLING,
		DAMAGED_LEFT,
		DAMAGED_RIGHT
	};

	// �L�[�̓��͏�Ԃ�ۑ�����z��
	INPUT_STATE m_InputState[KEY_INFO::MAX_KEY_INFO]{ NOT_PUSH };

	Character m_Chara;
	Terrain m_Terrain;
	Hook m_Hook;

	//�E�B���h�E�̑傫��
	UINT m_width;
	UINT m_height;

	//�p�����[�^
	DirectX::XMFLOAT2 Moveinput = DirectX::XMFLOAT2(0.0f, 0.0f);	//�ړ����x�̍��v
	const float xa = 0.7f;											//X�������̉����x
	const float xs_MAX = 6.0f;										//X���������x�̍ő�l
	const float gravity_s = 1.0f;									//�d�͉����x
	const float gravity_MAX = 20.0f;								//�������x�̍ő�l
	const float jump_s = 20.0f;										//�W�����v���̏����x
	const float ejump_s = 25.0f;									//�G�ւ̃t�b�N�V���b�g����W�����v�������̏����x
	Terrain_Collision  Player_Collision = No_Collision;				//���@�ƒn�`�E�G�Ƃ̓����蔻��̋L�^
	const float move_s_h = 20.0f;									//���[�v���̈ړ����x
	DirectX::XMFLOAT2 p_firstPos;									//���@�̏����ʒu
	DirectX::XMFLOAT2 h_move_pos;									//���[�v���̈ړ������ۑ��p

	const float move_s_d = 4.0f;									//��_������X�������x
	const float move_a_d = 0.02f;									//��_������X�������x
	const float jump_s_d = 13.0f;									//��_������Y�������x

	bool jump_hook_flag = false;									//�W�����v���̃t�b�N�V���b�g�͈�x���[�v����ƒ��n�܂ōĔ��˕s�@�̔���p
	PLAYER_STATE Player_state = IDLING;								//���@�̏�Ԃ�ۑ�

	DirectX::XMFLOAT2 Hook_Moveinput = DirectX::XMFLOAT2(0.0f, 0.0f);//�t�b�N�̈ړ����x���v
	const float Hook_s = 10.0f;										//�t�b�N�̏����x�@�������Ȃ��̂ł��̂܂�
	const float Hook_length = 300.0f;								//���̋����܂ŗ��ꂽ�甽�]
	HOOK_STATE Hook_state = H_IDLING;								//�t�b�N�̏�Ԃ�ۑ�
	Terrain_Collision Hook_Collision = No_Collision;				//�t�b�N�ƒn�`�E�G�Ƃ̓����蔻��̋L�^
	bool hookAnimFlag = false;										//���@�̃t�b�N���˃��[�V�����̍Đ��t���O

	float scrollPosY = 0.0f;										//Y�������̃X�N���[������
	const float default_scroll_s = 1.0f;							//�X�N���[�����x�̍Œ�l
	float scroll_s = default_scroll_s;								//�X�N���[�����x
	const float scroll_s_c = 0.1f;									//���̌W�����X�N���[�������ɂ����ăX�N���[�����x�Ƃ���

	void KeyUpdate(unsigned char* key);
	void keyInfoUpdate(unsigned char* key, KEY_INFO keyInfo);
	void PlayerUpdate();
	void PlayerUpdate_Hanging();
	void PlayerUpdate_Damaged();
	void HookUpdate(DirectX::XMFLOAT2 CharaMoveLog);
	void Scroll();
	void AnimUpdate();

	Scene(const  Scene&) = delete;
	Scene& operator=(const  Scene&) = delete;
};