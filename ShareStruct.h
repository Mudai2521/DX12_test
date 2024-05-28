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
	TELEPOTING,//���[�v���A�O��
	DAMAGE
};

enum ENEMY_TYPE
{
	ENEMY_IDLE
};

enum ENEMY_STATE
{
	ENEMY_IDLING,
	ENEMY_DAMAGED,
	ENEMY_DELETED,
	ENEMY_ATTACKING
};

enum ENEMY_ANIM_STATE
{
	ENEMY_ANIM_IDLE=1,
	ENEMY_ANIM_DAMAGE,
	ENEMY_ANIM_DAMAGE2
};

enum Terrain_Collision
{
	No_Collision = 0,
	Celling = 0x1,
	Wall = 0x2,
	Floor = 0x4,
	Enemy_Hit_Left = 0x8,
	Enemy_Hit_Right = 0x10,
	Goal = 0x20
};

DEFINE_ENUM_FLAG_OPERATORS(Terrain_Collision);

enum SCENE_STATE
{
	SCENE_INGAME,
	SCENE_ENDING,
	SCENE_TITLE
};

enum END_EFFECT_STATE
{
	END_EFFECT_BEFORE,
	END_EFFECT_WHITE,
	END_EFFECT_BEFORETEXT,
	END_EFFECT_TEXT,
	END_EFFECT_TEXTWHITE,
	END_EFFECT_END
};