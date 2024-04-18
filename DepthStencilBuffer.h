#pragma once

#include "stdafx.h"
#include "DescriptorPool.h"

class DepthStencilBuffer
{
public:
	DepthStencilBuffer();
	~DepthStencilBuffer();
	bool Init();
private:
	DescriptorHandle* m_pHandle;      //�f�B�X�N���v�^�n���h��
	DescriptorPool* m_pPool;        //�f�B�X�N���v�^�v�[��
};