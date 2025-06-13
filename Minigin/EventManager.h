#pragma once
#include "EventQueue.h"
#include "QueueEvent.h"
#include "Singleton.h"
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace dae
{
    class EventManager final : public Singleton<EventManager>
    {
    public:
        ~EventManager()
        {
            for (auto pQueue : m_pQueues)
            {
                delete pQueue.second;
            }
        }
        void HandleEvents();

    private:
      
        std::unordered_map<std::type_index, EventQueue<QueueEvent>*> m_pQueues{};
        std::unordered_map<std::type_index, EventQueue<QueueEvent>*> m_pNewQueues{};
        bool m_IsDirty{ false };
    };
}