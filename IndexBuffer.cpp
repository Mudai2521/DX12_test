#include "IndexBuffer.h"


IndexBuffer::IndexBuffer()
    : m_pIB(nullptr)
{
    memset(&m_View, 0, sizeof(m_View));
}

IndexBuffer::~IndexBuffer()
{
    Term();
}

bool IndexBuffer::Init(ID3D12Device* pDevice, size_t size, const uint32_t* pInitData)
{
    // �����`�F�b�N
    if (pDevice == nullptr || size == 0)
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
        IID_PPV_ARGS(m_pIB.GetAddressOf()));
    if (FAILED(hr))
    {
        return false;
    }

    // �C���f�b�N�X�o�b�t�@�r���[�̐ݒ�
    m_View.BufferLocation = m_pIB->GetGPUVirtualAddress();
    m_View.Format = DXGI_FORMAT_R32_UINT;
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

        m_pIB->Unmap(0, nullptr);
    }

    // ����I��
    return true;
}

void IndexBuffer::Term()
{
    m_pIB.Reset();
    memset(&m_View, 0, sizeof(m_View));
}

uint32_t* IndexBuffer::Map()
{
    uint32_t* ptr;
    auto hr = m_pIB->Map(0, nullptr, reinterpret_cast<void**>(&ptr));
    if (FAILED(hr))
    {
        return nullptr;
    }

    return ptr;
}

void IndexBuffer::Unmap()
{
    m_pIB->Unmap(0, nullptr);
}

D3D12_INDEX_BUFFER_VIEW IndexBuffer::GetView() const
{
    return m_View;
}
