#include "SteadyProfiler.h"

namespace engine {
    /*
     * SteadyProfiler
     */

    ProfilerEntry* SteadyProfiler::newEntry(const std::string &name)
    {
        auto [it, _] = entries.try_emplace(name, name);
        return &it->second;
    }

    void SteadyProfiler::forEachEntries(const std::function<void(ProfilerEntry&)> &func)
    {
        for (auto& [_, entry] : entries)
            func(entry);
    }

    nanoseconds SteadyProfiler::calculateTotalSpentTime()
    {
        nanoseconds total = nanoseconds::zero();

        for (auto& [_, entry] : entries)
            total += entry.getAccumulatedTime();

        return total;
    }

    uint64_t SteadyProfiler::calculateTotalNumCalls()
    {
        uint64_t total = 0;

        for (auto& [_, entry] : entries)
            total += entry.getNumCalls();

        return total;
    }

    /*
     * ProfilerEntry
     */

    void ProfilerEntry::begin()
    {
        if (bClosed)
        {
            //TODO: throw error
        }

        if (bProfiling)
        {
            //TODO: throw error
        }

        beginTime = steady_clock::now();
        bProfiling = true;
    }

    void ProfilerEntry::end()
    {
        if (bClosed)
        {
            //TODO: throw error
        }

        if (!bProfiling)
        {
            //TODO: throw error
        }

        const nanoseconds durationNs = steady_clock::now() - beginTime;

        accumulatedTime += durationNs;
        lastSpentTime = durationNs;

        numCalls++;

        bProfiling = false;
    }

    void ProfilerEntry::reset()
    {
        accumulatedTime = nanoseconds::zero();
        lastSpentTime = nanoseconds::zero();

        numCalls = 0;
    }

    void ProfilerEntry::stop()
    {
        if (bClosed)
        {
            //TODO: throw error
        }

        if(bProfiling)
            end();

        bClosed = true;
        endTime = steady_clock::now();
    }

    nanoseconds ProfilerEntry::calculateSpentTimeAvg() const
    {
        if (numCalls <= 0)
            return nanoseconds::zero();

        return accumulatedTime / numCalls;
    }

}
