#ifndef RUNNABLEBASE_H
#define RUNNABLEBASE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <thread>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <QDebug>
class RunnableBase
{
public:
    RunnableBase(){

    }
    ~RunnableBase(){
        if(obj_thread){
            StopRunnable();
        }
    }
    template<typename _Callable, typename... _Args>
    std::thread * InitRunnable(_Callable&& __func, _Args&&... __args)
    {
//        if(!obj_thread){
//            obj_thread = new std::thread(std::forward<_Callable>(__func),
//                                            std::forward<_Args>(__args)...);
//            if(!obj_thread){
//                qDebug() << "Runnable::Start() failed";
//                return nullptr;
//            }
//            return obj_thread;
//        }
//        return obj_thread;
         return obj_thread=new std::thread(std::forward<_Callable>(__func), std::forward<_Args>(__args)...);
    }
    int StopRunnable(){
        if(obj_thread){
            obj_thread->join();
            delete obj_thread;
        }

        return 0;
    }
    int abort=0;
    bool loop =false;
    std::thread *obj_thread=nullptr;
};

#endif // RUNNABLEBASE_H
