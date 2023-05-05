#include "thread.h"

Thread::Thread(int poolSize)
{
    this->poolSize = poolSize;
    isDestroy = false;
    isStop = false;

    for(int i=0; i<poolSize; i++)
        threadList.emplace_back([this]() { workerThread(); });
}

Thread::~Thread()
{
    isStop = true;
    isDestroy = true;
    
    cond.notify_all();
    for(size_t i=0; i<poolSize; i++)
    {
        threadList.at(i).join();
    }
}

bool Thread::canThisContinue() 
{
    bool result = true;

    if(!isDestroy && !isStop && jobList.empty()) result = false;
    else if(!isDestroy && isStop) result = false;

    return result;
}

void Thread::workerThread()
{
    std::function<void()> temp;

    while(true)
    {
        std::unique_lock<std::mutex> lock(mutex); //canThisContinue();
        cond.wait(lock, [this]() -> bool { return canThisContinue(); });
        if(isDestroy && isStop && jobList.empty())
            break;
        else if(!isDestroy && isStop)
            continue;

        temp = std::move(jobList.front());
        jobList.pop(); 
        lock.unlock();
        temp();
    }
    return;
}
