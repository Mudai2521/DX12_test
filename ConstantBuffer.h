#pragma once

#include "stdafx.h"
#include "DescriptorPool.h"

using Microsoft::WRL::ComPtr;

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();
    bool Init(
        ID3D12Device* pDevice,
        DescriptorPool* pPool,
        size_t          size);

    void Term();

    
    D3D12_GPU_VIRTUAL_ADDRESS GetAddress() const;

    
    D3D12_CPU_DESCRIPTOR_HANDLE GetHandleCPU() const;

    
    D3D12_GPU_DESCRIPTOR_HANDLE GetHandleGPU() const;

    
    void* GetPtr() const;

   
    template<typename T>
    T* GetPtr()
    {
        return reinterpret_cast<T*>(GetPtr());
    }

private:
    
    ComPtr<ID3D12Resource>          m_pCB;          //�萔�o�b�t�@
    DescriptorHandle* m_pHandle;      //�f�B�X�N���v�^�n���h��
    DescriptorPool* m_pPool;        //�f�B�X�N���v�^�v�[��
    D3D12_CONSTANT_BUFFER_VIEW_DESC m_Desc;         //�萔�o�b�t�@�r���[�̍\���ݒ�
    void* m_pMappedPtr;   //�}�b�v�ς݃|�C���^

    
    ConstantBuffer(const ConstantBuffer&) = delete;       // �A�N�Z�X�֎~
    void operator = (const ConstantBuffer&) = delete;       // �A�N�Z�X�֎~
};