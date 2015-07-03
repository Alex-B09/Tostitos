#ifndef SYSTEM_H__TOSTITOS
#define SYSTEM_H__TOSTITOS

#include "threads/scheduler.h"
#include "memory/userMemory.h"

class System
{
private:
    System() = default;
    System(const System &) = delete;
    void operator=(const System &) = delete;

public:
    static System & getInstance()
    {
        static System Instance;
        return Instance;
    }

    Threads::Scheduler & getScheduler()
    {
        return Threads::Scheduler::GetInstance();
    }

    UserMemory::Memory & getMemory()
    {
        return UserMemory::Memory::GetInstance();
    }

    // TODO -- the file system should have the same kind of logic...
};

#endif