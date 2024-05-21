#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "Character.h"
#include "Enemy.h"

class Terrain
{
public:
	Terrain();
	~Terrain();
	bool Init(ID3D12Device* pDevice, ID3D12CommandQueue* pQueue, DescriptorPool* pPool, UINT width, UINT height);
	void Term();
	void DrawMap(ID3D12GraphicsCommandList* pCmdList, float Scroll = 0.0f);
	DirectX::XMFLOAT2 Collision(DirectX::XMFLOAT2 Trans, DirectX::XMFLOAT2 Scale, Terrain_Collision& Collision_ret,DirectX::XMFLOAT2 Move, bool is_attack=false);
	void SetFloorSpriteSheet(int top, int left, int bottom, int right, int ID);
	void SetFloor2SpriteSheet(int left, int right, int ID);

	void SetScale(DirectX::XMFLOAT2 Scale) { m_CharactorState.Scale = Scale; };
	float GetScaleX() { return m_CharactorState.Scale.x; };
	float GetScaleY() { return m_CharactorState.Scale.y; };
	void SetRotate(float Rotate) { m_CharactorState.Rotate = Rotate; };
	void SetTrans(DirectX::XMFLOAT2 Trans) { m_CharactorState.Trans = Trans; };
	void SetScaleRotateTrans(DirectX::XMFLOAT2 Scale, float Rotate, DirectX::XMFLOAT2 Trans)
	{
		m_CharactorState.Scale = Scale;
		m_CharactorState.Rotate = Rotate;
		m_CharactorState.Trans = Trans;
	};
	void SetRotateTrans(float Rotate, DirectX::XMFLOAT2 Trans)
	{
		m_CharactorState.Rotate = Rotate;
		m_CharactorState.Trans = Trans;
	};
private:
	CharactorState m_CharactorState;//このクラスではマップチップ一枚あたりの大きさの管理に使う
	UINT m_width;
	UINT m_height;
	Enemy m_Enemy;

	Sprite m_spritedata;

	Terrain(const  Terrain&) = delete;
	Terrain& operator=(const Terrain&) = delete;

	float drawMapBuffer;//画面上方のはみ出した領域も衝突判定を行う　判定を行う領域の範囲（Y軸方向）

	void ScrollUpdate(float Scroll);
	int TerrainScroll = 0;

	const int floorSpriteMax = 16;
	const int floor2SpriteMax = 4;

	static const UINT MapX_MAX = 40;
	static const UINT MapY_MAX = 26;
	static const UINT MapY_DIVISION = 32;

	std::vector<UINT> map;
	std::vector<int> mapChipList = { 0,};
	int mapListCount = 0;
	int mapChipCount = 0;
	std::random_device seed_gen;
	std::mt19937 mapRnd;
	const int MapChipNum = 7;

	//0=BG,1=地形,2=すり抜け床,9=敵
	std::vector<int> mapChip[MapY_DIVISION * MapX_MAX] =
	{
		{//0 初期位置のみ使用
			1,1,1,1,0, 0,0,0,0,0,  2,2,2,2,0, 0,0,0,0,0,  0,0,0,0,0, 0,2,2,2,2,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,2,2,2, 2,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,2,2,  2,2,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,2,2,2, 2,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1
		},
		{//1 箸休めマップ
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,2, 2,2,2,1,1,  1,1,1,1,1, 1,1,1,1,1,  2,2,2,2,2, 2,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,1,1,  1,1,0,0,0, 0,1,1,1,1,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,2, 2,2,2,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,  2,2,2,2,2, 2,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  0,0,0,0,0, 0,0,0,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  0,0,0,0,0, 0,0,0,1,1,  1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,2, 2,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  2,2,2,2,1, 1,1,1,2,2,  2,2,1,1,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			
		
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,2,2,2, 2,2,2,1,1,  1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
		},
		{//2
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,2,2,2,2,  1,1,2,2,2, 2,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  1,1,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,9,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,2,2,2, 2,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,9,0,  0,0,0,0,1, 1,1,1,1,1,  2,2,2,2,2, 2,2,2,2,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,  0,0,0,0,0, 0,0,0,0,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,9,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,2, 2,2,2,1,1,  1,1,2,2,2, 2,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
		},
		{//3
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,2,2,1,1,  1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,2,2,2,2,  2,2,1,1,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,2, 2,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  9,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,2,  2,2,2,2,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,2, 2,2,2,1,1,  1,1,2,2,2, 2,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,2,2,2, 2,0,0,0,0,  0,0,0,0,2, 2,2,2,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
		},
		{//4 高難度マップ
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,2,2,2, 2,2,2,1,1,  1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 9,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,2,2,2,2,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,2,2,  2,2,2,1,1, 1,1,2,2,2,  2,2,2,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,1,1, 1,1,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 1,1,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
		},
		{//5 箸休めマップ
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,1,1,  1,1,0,0,0, 0,0,0,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,2,2,1,1,  1,1,2,2,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,1,1,
			1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  1,1,1,1,2, 2,2,2,2,2,  2,2,1,1,1, 1,1,1,1,1,
			1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  1,1,1,1,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,
			1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,
			1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,
		
			1,1,1,1,1, 1,1,1,2,2,  2,2,2,2,1, 1,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,
			1,1,1,1,1, 1,1,1,0,0,  0,0,0,0,1, 1,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,1, 1,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,  1,1,1,1,1, 1,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,2,2,2,2,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,1, 1,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  0,0,0,0,0, 0,0,0,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,1,1,  2,2,2,2,2, 2,2,2,1,1,  1,1,2,2,2, 2,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,1, 1,1,1,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
		},
		{//6 高難度マップ
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,1,1, 2,2,2,2,2,  2,2,2,2,2, 2,2,2,2,2,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,1,1, 2,2,2,2,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,1,1, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,9,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,1,  1,1,1,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,1,  1,1,1,2,2, 2,2,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,9,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,2,2,  2,2,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,1, 1,0,0,0,0,  0,0,0,0,1, 1,2,2,2,2,  2,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,1, 1,2,2,2,2,  2,2,2,2,1, 1,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
		},
		{//7
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  1,1,2,2,2, 2,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,2, 2,2,2,2,2,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,9,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,  1,1,2,2,2, 2,2,2,2,2,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,1,1,1, 1,1,1,1,1,  1,1,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,9,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,  2,2,2,2,2, 2,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,1,2,2,2,  2,2,2,2,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,1,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,1,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,1,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,1,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,1,1,1,1,  1,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,1,1,1,1,  1,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,1, 1,2,2,2,2,  0,0,0,0,1, 1,1,1,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,1, 1,0,0,0,0,  2,2,2,2,1, 1,1,1,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
		}
	};
	int temp[MapY_DIVISION * MapX_MAX]
	{//コピペ用　編集しないこと
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,

			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
			1,1,1,1,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,1,1,1,1,
		};
};
