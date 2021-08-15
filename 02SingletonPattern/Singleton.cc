//饿汉模式 加锁和不加锁
//加锁的话 使用double check c++已经不用加锁
//为了进一步安全还可以使用pthread_once只初始化一次
//注意不能自定义析构函数，那这个new的对象怎么删？
//template<typename T>
#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include <sys/syscall.h>
class Singleton
{
private:
    /* data */
    Singleton(/* args */){std::cout<<"singleton()"<<std::endl;}
    static Singleton* obj_;
    ~Singleton(/* args */){}
public:
    static Singleton* getInstance();
    
    // {
    //     std::cout<<"~singleton()"<<std::endl;
    //     delete obj_;
        
    // }
    static void destroy();
};
Singleton * Singleton::obj_ = nullptr; //需要在外面初始化
Singleton* Singleton::getInstance()
{
    if(obj_==nullptr)
    {
        obj_ = new Singleton();
        atexit(destroy);
    }
        

    return obj_;
}
void Singleton::destroy()
{
    std::cout<<"destroy"<<syscall(SYS_gettid)<<std::endl;
    delete obj_;
}



Singleton *p;
void* func(void* arg)
{
    p = Singleton::getInstance();
    return NULL;
}

int main()
{
    pthread_t tid;

    for(int i=0;i<50;++i)
    {
        pthread_create(&tid,NULL,func,NULL);
    }
    //detach或者等待join barry
    sleep(10);
    
}