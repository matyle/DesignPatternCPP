//有锁版本
//有种更优秀的写法使用pthread_once
#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include <sys/syscall.h>
class Singleton3
{
private:
    /* data */
    Singleton3(/* args */)
    {
        std::cout<<"singleton3()"<<std::endl;
    }
    // ~Singleton3(/* args */)
    // {
    //     std::cout<<"~singleton3()"<<std::endl;
    // }
    // Singleton3();
    // ~Singleton3();
    static Singleton3* obj_;
    static pthread_once_t once_;
    static void init();
    static void destroy();
public:
    static Singleton3* getInstance();
    
};

Singleton3 * Singleton3::obj_ = nullptr; //需要在外面初始化
pthread_once_t Singleton3::once_ = PTHREAD_ONCE_INIT;

void Singleton3::destroy()
{
    std::cout<<"destroy thread: "<<syscall(SYS_gettid)<<std::endl;
    delete obj_;
}


void Singleton3::init()
{
        obj_ = new Singleton3();
        atexit(destroy);
}

Singleton3* Singleton3::getInstance()
{
    
    pthread_once(&once_,init);
    return obj_;
}

void* func(void* arg)
{
    //pthread_detach(pthread_self());
    //std::cout<<"this is a thread:"<<syscall(SYS_gettid)<<std::endl;
    Singleton3 *p = Singleton3::getInstance();
    return NULL;
}

int main()
{
    pthread_t tid;
    std::cout<<"this is a main thread:"<<getpid()<<std::endl;
    std::cout<<"this is a main thread:"<<syscall(SYS_gettid)<<std::endl;

    for(int i=0;i<100;++i)
    {
        pthread_create(&tid,NULL,func,NULL);
    }
    sleep(15);
    //detach或者等待join barry
}


