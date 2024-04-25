#include "Character.h"

using namespace DirectX;

Character::Character():
	m_CharactorState(
		XMFLOAT2(32.0f,32.0f),
		0.0f,
		XMFLOAT2(0.0f,0.0f))
{
}

Character::~Character()
{
	Term();
}

bool Character::Init(ID3D12Device* pDevice, ID3D12CommandQueue* pQueue, DescriptorPool* pPool, UINT width, UINT height)
{
	m_spritedata.resize(1);
	auto pSpritedata = new (std::nothrow) Sprite();
	if (!pSpritedata->Init(L"2024_03_29_3.dds", pDevice, pQueue, pPool, width, height))throw std::exception();
	m_spritedata[0] = pSpritedata;
	m_width = width;
	m_height = height;

	
	m_spritedata[0]->SetWorldMatrix(m_CharactorState.Scale, m_CharactorState.Rotate, m_CharactorState.Trans);

	return true;
}

void Character::Term()
{
	for (size_t i = 0; i < m_spritedata.size(); ++i)
	{
		if (m_spritedata[i] != nullptr)
		{
			m_spritedata[i]->Term();
			delete m_spritedata[i];
			m_spritedata[i] = nullptr;
		}
	}
}

void Character::DrawSprite(ID3D12GraphicsCommandList* pCmdList)
{
	m_spritedata[0]->SetWorldMatrix(m_CharactorState.Scale, m_CharactorState.Rotate, m_CharactorState.Trans);
	m_spritedata[0]->Draw(pCmdList);
}