#include <iostream>
#include <string>
#include <utility>
#include "mingw.thread.h"
#include <chrono>
#include <atomic>
#include <functional>

using std::string;

class Singleton{
public:
    Singleton(Singleton& other) = delete; // 禁止默认拷贝构造
    void operator=(const Singleton& other) = delete; // 禁止拷贝赋值运算符
    static Singleton* getInstance(const string value);
    void SomeBusinessLogic(){};
    string value() const {
        return value_;
    }
protected : 
    Singleton(const string value) : value_(value){};
    string value_; // 保护成员命名以下划线结尾
    static Singleton* singleton_; // 静态的全局访问点，保证只有一个实例
};

Singleton* Singleton::singleton_ = nullptr; ;
Singleton* Singleton::getInstance(const string value){
    // 实例不存在时构建，否则通过全局访问点进行访问
    if(singleton_==nullptr){
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadFoo(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("FOO");
    std::cout<< singleton->value()<<"\n";
}

void ThreadBar()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::getInstance("BAR");
    std::cout << singleton->value()<<"\n";
}

int main1(){
    std::cout << "If you see the same value, then singleton was reused (yay!\n"
              << "If you see different values, then 2 singletons were created (booo!!)\n\n"
              << "RESULT:\n";
    std::thread t1(ThreadFoo); // 线程异常
    std::thread t2(ThreadBar); 
    t1.join();
    t2.join();
    system("pause"); 
    return 0;
}