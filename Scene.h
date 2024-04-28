#pragma once
#include "stdafx.h"
#include "DescriptorPool.h"
#include "Sprite.h"
#include "Terrain.h"

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

	// �L�[�̓��͏�Ԃ�ۑ�����z��
	INPUT_STATE m_InputState[KEY_INFO::MAX_KEY_INFO]{ NOT_PUSH };

	Character m_Chara;
	Terrain m_Terrain;

	UINT m_width;
	UINT m_height;

	//�p�����[�^
	DirectX::XMFLOAT2 Moveinput = DirectX::XMFLOAT2(0.0f, 0.0f);
	const float xa = 0.7f;
	const float xs_MAX = 6.0f;
	const float gravity_s = 1.0f;
	const float jump_s = 20.0f;
	bool on_ground = false;

	void KeyUpdate(unsigned char* key);
	void keyInfoUpdate(unsigned char* key, KEY_INFO keyInfo);

	Scene(const  Scene&) = delete;
	Scene& operator=(const  Scene&) = delete;
};