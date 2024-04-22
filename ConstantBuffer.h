#pragma once

#include "stdafx.h"
#include "DescriptorPool.h"
#include "DXHelper.h"



using Microsoft::WRL::ComPtr;

struct Transform
{
    DirectX::XMMATRIX World; // ���[���h�s��
    DirectX::XMMATRIX View; // �r���[�s��
    DirectX::XMMATRIX Proj; // ���e�s��
    float padding[16]; // Padding so the constant buffer is 256-byte aligned.
};
static_assert((sizeof(Transform) % 256) == 0, "Constant Buffer size must be 256-byte aligned");

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();
    bool Init(
        ID3D12Device* pDevice,
        DescriptorPool* pPool);

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

    void SetTransform(DirectX::XMMATRIX World, DirectX::XMMATRIX View, DirectX::XMMATRIX Proj)
    {
        m_ConstantBufferData.World = World;
        m_ConstantBufferData.View = View;
        m_ConstantBufferData.Proj = Proj;
        memcpy(m_pMappedPtr, &m_ConstantBufferData, sizeof(m_ConstantBufferData));
    }

    void SetWorldMatrix(DirectX::XMMATRIX World)
    {
        m_ConstantBufferData.World *= World;
        memcpy(m_pMappedPtr, &m_ConstantBufferData, sizeof(m_ConstantBufferData));
    }

private:
    
    ComPtr<ID3D12Resource>          m_pCB;          //�萔�o�b�t�@
    DescriptorHandle* m_pHandle;      //�f�B�X�N���v�^�n���h��
    DescriptorPool* m_pPool;        //�f�B�X�N���v�^�v�[��
    D3D12_CONSTANT_BUFFER_VIEW_DESC m_Desc;         //�萔�o�b�t�@�r���[�̍\���ݒ�
    void* m_pMappedPtr;   //�}�b�v�ς݃|�C���^
    Transform m_ConstantBufferData;
    UINT8* m_pCbvDataBegin;

    
    ConstantBuffer(const ConstantBuffer&) = delete;       // �A�N�Z�X�֎~
    void operator = (const ConstantBuffer&) = delete;       // �A�N�Z�X�֎~
};