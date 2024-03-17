#include "ThreadRunnable.h"



ThreadRunnable::ThreadRunnable()
    : _thread(nullptr),
      _pauseFlag(false),
      _stopFlag(false),
      _state(Stoped)
{

}

ThreadRunnable::~ThreadRunnable()
{
    stop();
}

ThreadRunnable::State ThreadRunnable::state() const
{
    return _state;
}




void ThreadRunnable::start()
{
    if (_thread == nullptr)
    {
        _thread = new std::thread(&ThreadRunnable::run,this);
        _pauseFlag = false;
        _stopFlag = false;
        _state = Running;
    }
}

void ThreadRunnable::stop()
{
    if (_thread != nullptr)
    {
        _pauseFlag = false;
        _stopFlag = true;
        _condition.notify_all();  // Notify one waiting thread, if there is one.
        _thread->join(); // wait for thread finished
        delete _thread;
        _thread = nullptr;
        _state = Stoped;
    }
}

void ThreadRunnable::pause()
{
    if (_thread != nullptr)
    {
        _pauseFlag = true;
        _state = Paused;
    }
}

void ThreadRunnable::resume()
{
    if (_thread != nullptr)
    {
        _pauseFlag = false;
        _condition.notify_all();
        _state = Running;
    }
}



void ThreadRunnable::run()
{
   // std::cout << "enter thread:" << std::this_thread::get_id() << std::endl;

    while (!_stopFlag)
    {
        process();
        if (_pauseFlag)
        {
            std::unique_lock<std::mutex> locker(_mutex);
            while (_pauseFlag)
            {
                _condition.wait(locker); // Unlock _mutex and wait to be notified
            }
            locker.unlock();
        }
    }
    _pauseFlag = false;
    _stopFlag = false;

   // std::cout << "exit thread:" << std::this_thread::get_id() << std::endl;
}
