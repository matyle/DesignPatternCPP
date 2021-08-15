//观察者和观察目标
//使用weak_ptr和shared_ptr实现，解决线程安全，以及循环引用问题
//一个观察目标中（被观察）可能有多个观察者
//而每个观察者对应一个观察目标
//观察目标会notify观察者，同时观察者会根据通知做出响应
//观察者类会添加目标，移除目标。由于移除目标（这时不知道目标对象的生死）
#include<iostream>
#include<memory>
#include<vector>
using namespace std;
//公众号订阅者
class Observer
{
private:
    /* data */
public:
    Observer(/* args */);
    ~Observer();
};


//目标 girls 公众号
class Subject
{
private:
    /* data */
    vector<weak_ptr<Observer>> observers_; //多个观察者 


public:
    Subject(/* args */);
    ~Subject();
    
};