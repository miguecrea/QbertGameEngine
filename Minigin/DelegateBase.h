#pragma once

#pragma once
#include <functional>
#include <unordered_map>
#include <cstdint>


#pragma once
#include <functional>
#include <vector>


namespace dae
{

    template<typename... Args>  //variatric template 
    class MulticastDelegate
    {
    public:

        using HandlerType = std::function<void(Args...)>;

        void Add(const HandlerType & handler)
        {
            handlers.push_back(handler);
        }

        void Broadcast(Args...args) const
        {
            if (handlers.empty()) return;

            for (const auto& handler : handlers)
                handler(args...);
        }

        void Clear()
        {
            handlers.clear();
        }

    private:
        std::vector<HandlerType> handlers;
    };

};