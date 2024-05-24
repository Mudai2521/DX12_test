#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "ShareStruct.h"

class BackGround
{
public:
	BackGround();
	~BackGround();
	bool Init(ID3D12Device* pDevice, ID3D12CommandQueue* pQueue, DescriptorPool* pPool, UINT width, UINT height);
	void Term();
	void DrawSprite(ID3D12GraphicsCommandList* pCmdList, float Scroll = 0.0f);
private:
	CharactorState m_CharactorState;
	UINT m_width;
	UINT m_height;

	Sprite m_spritedata;

	BackGround(const  BackGround&) = delete;
	BackGround& operator=(const BackGround&) = delete;
};