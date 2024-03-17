#ifndef THREADBASE_H
#define THREADBASE_H

#include <thread>

//class ThreadBase
//{
//public:
//    ThreadBase() {}
//    ~ThreadBase() {
//        if(thread_) {
//            ThreadBase::Stop();
//        }
//    }
//    int Start() {}
//    int Stop() {
//        abort_ = 1;
//        if(thread_) {
//            thread_->join();
//            delete thread_;
//            thread_ = NULL;
//        }
//    };
//    virtual void Run() = 0;
//protected:
//    int abort_ = 0;
//    std::thread *thread_ = NULL;
//};
#endif // THREADBASE_H
