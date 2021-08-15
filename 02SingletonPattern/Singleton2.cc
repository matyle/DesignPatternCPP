//有锁版本
//有种更优秀的写法使用pthread_once
#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include <sys/syscall.h>
class Singleton2
{
private:
    /* data */
    Singleton2(/* args */)
    {
        pthread_mutex_init(&mutex_,NULL);
        std::cout<<"singleton()"<<std::endl;
    }
    static Singleton2* obj_;
    //static pthread_mutex_t mutex_;

public:
    static Singleton2* getInstance();
    static pthread_mutex_t mutex_;
     static void destroy();
    
};
Singleton2 * Singleton2::obj_ = nullptr; //需要在外面初始化
pthread_mutex_t Singleton2::mutex_;

Singleton2* Singleton2::getInstance()
{
    if(obj_ == nullptr) //避免频繁加锁解锁
    {
        pthread_mutex_lock(&mutex_); //加锁
        if(obj_ == nullptr)
        {
            std::cout<<"build object"<<std::endl;
            obj_ = new Singleton2();
            atexit(destroy);
        }
        pthread_mutex_unlock(&mutex_);
    }
    return obj_;
}

void Singleton2::destroy()
{
    std::cout<<"destroy thread:"<<syscall(SYS_gettid)<<std::endl;
    delete obj_;
}

Singleton2 *p;
void* func(void* arg)
{
    //pthread_detach(pthread_self());
    //std::cout<<"this is a thread:"<<syscall(SYS_gettid)<<std::endl;
    p = Singleton2::getInstance();
    sleep(20);
    return NULL;
}

int main()
{
    pthread_t tid;

    for(int i=0;i<500;++i)
    {
        pthread_create(&tid,NULL,func,NULL);
    }
    sleep(20);
    //detach或者等待join barry

}


