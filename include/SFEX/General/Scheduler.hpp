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

#ifndef _SFEX_GENERAL_SCHEDULER_HPP_
#define _SFEX_GENERAL_SCHEDULER_HPP_

#include <functional>
#include <type_traits>
#include <unordered_set>
#include <thread>
#include <future>

#include <SFEX/General/StaticClass.hpp>
#include <SFML/System/Time.hpp>

namespace sfex
{

class Scheduler
{
public:
    /// @brief Schedule a function
    /// @param time The delay before running the function
    /// @param funcToSchedule function to schedule
    /// @param funcArgs Function arguments
    template<typename Func, typename... Args>
    auto schedule(const sf::Time& time, const Func& funcionToSchedule, Args&&... funcArgs);

    /// @brief Calls the given function with given interval
    /// 
    /// @param name Name of the task. Must be unique.
    /// @param period Period of function to repeat
    /// @param functionToRepeat The function you want to repeat
    /// @param funcArgs Arguments of function
    /// @throws std::runtime_error If a job with same name exists
    template<typename Func, typename... Args>
    void repeat(const std::string& name, const sf::Time& period, const Func& functionToRepeat, Args&&... funcArgs);

    /// @brief Stops a repeating job
    /// 
    /// @param name Name of the job.
    void stopRepeatingJob(const std::string& name);
private:
    std::unordered_set<std::string> m_repeatingJobs;
};

}

#include <SFEX/General/Scheduler.inl>
#endif // !_SFEX_GENERAL_SCHEDULER_HPP_