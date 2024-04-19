#pragma once

#include "stdafx.h"
#include "DescriptorPool.h"
#include "DXHelper.h"

class RenderTargetView
{
public:
	RenderTargetView();
	~RenderTargetView();
	bool Init(ID3D12Device* pDevice, DescriptorPool* pPool, IDXGISwapChain3* pSwapChain, ID3D12CommandAllocator* pCommandAllocator, UINT Index);
	void Term();
	ID3D12Resource* Get();
private:
	DescriptorHandle* m_pHandle;      //�f�B�X�N���v�^�n���h��
	DescriptorPool* m_pPool;        //�f�B�X�N���v�^�v�[��
	ComPtr<ID3D12Resource> m_pRenderTargetView;
	UINT rtvIndex;

	RenderTargetView(const RenderTargetView&) = delete;       // �A�N�Z�X�֎~
	void operator = (const RenderTargetView&) = delete;       // �A�N�Z�X�֎~
};
