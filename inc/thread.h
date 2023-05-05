#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <future>
#include <functional>
#include <chrono>

class Thread
{
private:
    bool isDestroy;
    bool isStop;

    size_t poolSize;

    std::vector<std::thread> threadList;
    std::queue<std::function<void()>> jobList;

    std::condition_variable cond;
    std::mutex mutex;
    bool canThisContinue();
    void workerThread();
public:
    Thread(int poolSize = 5);
    ~Thread();

    template<typename F, typename... Args>
    std::future<typename std::result_of<F(Args...)>::type> add(F &&func, Args&&... args);

    void start() { isStop = false; cond.notify_all(); }
    void stop() { isStop = true; }

    size_t getJobCount() { return jobList.size(); }
    static void sleep(size_t milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
};

template<typename F, typename... Args>
std::future<typename std::result_of<F(Args...)>::type> Thread::add(F&& func, Args&&... args)
{
    using returnDataType = typename std::result_of<F(Args...)>::type;
    std::future<returnDataType> result;

    std::shared_ptr<std::packaged_task<returnDataType()>> job = \
        std::make_shared<std::packaged_task<returnDataType()>>(std::bind(std::forward<F>(func), std::forward<Args>(args)...));
    
    result = job->get_future();

    mutex.lock();
    jobList.push([job]() { (*job)(); });
    mutex.unlock();

    cond.notify_one();

    return result;
}

#endif /* __THREAD_H__ */