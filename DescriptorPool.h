#pragma once

#include <cstdint>
#include <mutex>
#include <cassert>
#include <functional>
#include "stdafx.h"


template<typename T>
class Pool
{
public:
	Pool()
		:m_pBuffer(nullptr),
		m_pActive(nullptr),
		m_pfree(nullptr),
		m_Capacity(0),
		m_COunt(0)
	{}
	~Pool()
	{
		Term();
	}
	bool Init(uint32_t count);
	void Term();
	T* Alloc(std::function<void(uint32_t, T*)> func = nullptr);
	void Free(T* pValue);
	uint32_t Getsize()const { return m_Capacity; }
	uint32_t GetUsedCount() const { return m_Count; }
	uint32_t GetAvailableCount() const { return m_Capacity - m_Count; }
private:
	struct Item
	{
		T m_Value;
		uint32_t m_Index;
		Item* m_pNext;
		Item* m_pPrev;

		Item()
			:m_Value(),
			m_Index(0),
			m_pNext(nullptr),
			m_pPrev(nullptr)
		{}
		~Item() 
		{}
	};

	uint8_t* m_pBuffer;
	Item* m_pActive;
	Item* m_pFree;
	uint32_t m_Capacity;
	uint32_t m_Count;
	std::mutex m_Mutex;

	Item* GetItem(uint32_t index)
	{
		assert(0 <= index && index <= m_Capacity + 2);
		return reinterpret_cast<Item*>(m_pBuffer + sizeof(Item) * index);
	}

	Item* AssignItem(uint32_t index);
	{
		assert(0 <= index && index <= m_Capacity + 2);
		auto buf = (m_pBuffer + sizeof(Item) * index);
		return new (buf) Item;
	}
	
	Pool(const Pool&) = delete;
	void operator = (const Pool&) = delete;
};