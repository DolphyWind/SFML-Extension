//
// MIT License
//
// Copyright (c) 2023 Yunus Emre Aydın
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef _SFEX_GENERAL_SCHEDULER_INL_
#define _SFEX_GENERAL_SCHEDULER_INL_

#include <SFEX/General/Scheduler.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>

namespace sfex
{

template<typename Func, typename... Args>
auto Scheduler::schedule(const sf::Time& time, const Func& functionToSchedule, Args&&... funcArgs)
{
    auto func = [&time, &functionToSchedule](Args&&... args){
        sf::sleep(time);
        return functionToSchedule( std::forward<Args>(args)... );
    };

    return std::async(func, funcArgs...);
}

template<typename Func, typename... Args>
void Scheduler::repeat(const std::string& name, const sf::Time& period, const Func& functionToRepeat, Args&&... funcArgs)
{
    auto insertion_result = m_repeatingJobs.insert(name);
    if(!insertion_result.second)
    {
        throw std::runtime_error("An option with the same name already exists!");
    }

    auto func = [this, name, &period, &functionToRepeat](Args&&... args){
        while(m_repeatingJobs.find(name) != m_repeatingJobs.end())
        {
            functionToRepeat( std::forward<Args>(args)... );
            sf::sleep(period);
        }
    };

    std::thread repeatingThread(func, funcArgs...);
    repeatingThread.detach();
}

void Scheduler::stopRepeatingJob(const std::string& name)
{
    m_repeatingJobs.erase(name);
}

}

#endif // !_SFEX_GENERAL_SCHEDULER_INL_