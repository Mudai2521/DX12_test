#pragma once
#include "stdafx.h"

struct CharactorState
{
	DirectX::XMFLOAT2 Scale;
	float Rotate;
	DirectX::XMFLOAT2 Trans;
	CharactorState() = default;
	CharactorState(DirectX::XMFLOAT2 Scale,
		float Rotate,
		DirectX::XMFLOAT2 Trans)
		: Scale(Scale)
		, Rotate(Rotate)
		, Trans(Trans)
	{
	}
};

//�v���C���[�̃A�j���[�V�����̏��
enum Player_Anim_State
{
	IDLE = 0,//�ҋ@
	RUN,//���E�ړ�
	JUMP,//�W�����v(�㏸)
	FALL,//����
	HOOK,//�Γ���
	TELEPORT_BEGIN,//���[�v�J�n�܂ł̑ҋ@
	TELEPORT_END,//���[�v��̑ҋ@
	TELEPOTING//���[�v���A�O��
};

enum ENEMY_TYPE
{
	ENEMY_IDLE
};

enum ENEMY_STATE
{
	ENEMY_IDLING,
	ENEMY_DAMAGED,
	ENEMY_DELETED
};

enum Terrain_Collision
{
	No_Collision = 0,
	Celling = 0x1,
	Wall = 0x2,
	Floor = 0x4,
	Enemy_Hit_Left = 0x8,
	Enemy_Hit_Right = 0x10
};

DEFINE_ENUM_FLAG_OPERATORS(Terrain_Collision);