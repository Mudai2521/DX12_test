#include "Enemy.h"

using namespace DirectX;

EnemyData::EnemyData() :
	m_CharactorState(
		XMFLOAT2(128.0f, 128.0f),
		0.0f,
		XMFLOAT2(0.0f, 0.0f)),
	direction(true)
{
}

EnemyData::~EnemyData()
{
	Term();
}

bool EnemyData::Init(XMFLOAT2 Scale, float Rotate, XMFLOAT2 Trans, bool Direction, ENEMY_TYPE Type)
{
	SetScaleRotateTrans(Scale, Rotate, Trans);
	if (GetDirection() != Direction)turn();
	m_type = Type;
	return true;
}

void EnemyData::Term() 
{
}

Enemy::Enemy() 
{
}

Enemy::~Enemy()
{
	Term();
}

bool Enemy::Init(ID3D12Device* pDevice, ID3D12CommandQueue* pQueue, DescriptorPool* pPool, UINT width, UINT height)
{
	m_spritedata.resize(1);
	auto pSpritedata = new (std::nothrow) Sprite();
	if (!pSpritedata->Init(L"Sprite/Enemy_temp.dds", pDevice, pQueue, pPool, width, height))throw std::exception();
	m_spritedata[0] = pSpritedata;
	m_width = width;
	m_height = height;

	m_spritedata[0]->SetSpriteSheet(2,1, 1, 1);
	return true;
}

void Enemy::Term()
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
	for (size_t i = 0; i < m_enemyData.size(); ++i)
	{
		if (m_enemyData[i] != nullptr)
		{
			m_enemyData[i]->Term();
			delete m_enemyData[i];
			m_enemyData[i] = nullptr;
		}
	}
}

void Enemy::DrawSprite(ID3D12GraphicsCommandList* pCmdList, float Scroll)
{
	for (auto& e : m_enemyData) 
	{
		SetSprite(e->GetEnemyType(), e->GetEnemyState());
		m_spritedata[e->GetEnemyType()]->SetWorldMatrix(e->GetScale(), e->GetRotate(), XMFLOAT2(e->GetTrans().x, e->GetTrans().y + Scroll));
		m_spritedata[e->GetEnemyType()]->Draw(pCmdList);
		m_spritedata[e->GetEnemyType()]->Setdrawcount();
	}
}

void Enemy::SetSprite(ENEMY_TYPE Type, ENEMY_STATE State)
{
	if (Type == ENEMY_IDLE) 
	{
		if (State == ENEMY_IDLING) 
		{
			m_spritedata[0]->SetSpriteSheet(2, 1, 1, 1);
		}
		else if (State == ENEMY_DAMAGED) 
		{
			m_spritedata[0]->SetSpriteSheet(2, 1, 2, 1);
		}
	}
}

void Enemy::AddEnemy(XMFLOAT2 Trans, bool Direction, ENEMY_TYPE Type)
{
	auto pEData = new (std::nothrow)EnemyData();
	pEData->Init(pEData->GetScale(), pEData->GetRotate(), Trans, Direction, Type);
	m_enemyData.push_back(pEData);
	return;
}

XMFLOAT2 Enemy::Collision(XMFLOAT2 Trans, XMFLOAT2 Scale, Terrain_Collision& Collision_ret, bool is_attack)
{
	XMFLOAT2 returnVec = XMFLOAT2(0.0f, 0.0f);

	for (auto& e : m_enemyData)
	{
		//����̂��߂ɋ�`���m�̋�����萔�Ƃ��Ē�`
		const float DIS_X = (Scale.x + e->GetScale().x) / 2;
		const float DIS_Y = (Scale.y + e->GetScale().y) / 2;

		if (abs(e->GetTrans().x - Trans.x) < DIS_X && abs(e->GetTrans().y - Trans.y) < DIS_Y&&e->GetEnemyState()== ENEMY_IDLING)
		{
			if (e->GetTrans().x - Trans.x > 0)
			{
				Collision_ret |= Enemy_Hit_Right;
			}
			else
			{
				Collision_ret |= Enemy_Hit_Left;
			}

			if (is_attack)
			{
				e->SetEnemyState(ENEMY_DAMAGED);
			}
		}

		if (abs(e->GetTrans().y - Trans.y) > m_height * 2) 
		{
			e->SetEnemyState(ENEMY_DELETED);
		}
	}
	return returnVec;
}