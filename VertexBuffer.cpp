#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
    : m_pVB(nullptr)
{
    memset(&m_View, 0, sizeof(m_View));
}


VertexBuffer::~VertexBuffer()
{
    Term();
}


bool VertexBuffer::Init(ID3D12Device* pDevice, size_t size, size_t stride, const void* pInitData)
{
    // �����`�F�b�N
    if (pDevice == nullptr || size == 0 || stride == 0)
    {
        return false;
    }


    // ���\�[�X�𐶐�
    auto hr = pDevice->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(size),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(m_pVB.GetAddressOf()));
    if (FAILED(hr))
    {
        return false;
    }

    // ���_�o�b�t�@�r���[�̐ݒ�
    m_View.BufferLocation = m_pVB->GetGPUVirtualAddress();
    m_View.StrideInBytes = UINT(stride);
    m_View.SizeInBytes = UINT(size);

    // �������f�[�^������΁C��������ł���
    if (pInitData != nullptr)
    {
        void* ptr = Map();
        if (ptr == nullptr)
        {
            return false;
        }

        memcpy(ptr, pInitData, size);

        m_pVB->Unmap(0, nullptr);
    }

    // ����I��
    return true;
}

void VertexBuffer::Term()
{
    m_pVB.Reset();
    memset(&m_View, 0, sizeof(m_View));
}


void* VertexBuffer::Map()
{
    void* ptr;
    auto hr = m_pVB->Map(0, nullptr, &ptr);
    if (FAILED(hr))
    {
        return nullptr;
    }

    return ptr;
}


void VertexBuffer::Unmap()
{
    m_pVB->Unmap(0, nullptr);
}


D3D12_VERTEX_BUFFER_VIEW VertexBuffer::GetView() const
{
    return m_View;
}

