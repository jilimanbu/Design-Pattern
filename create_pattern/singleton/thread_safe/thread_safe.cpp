#include <iostream>
#include <string>
#include <utility>
#include <chrono>
#include <atomic>
#include <functional>
#include "mingw.thread.h" // 安装这个头文件以使用c++11的std::thread
#include "mingw.mutex.h" // 安装这个头文件以使用c++11的std::mutex

using std::string;

class Singleton
{
public:
    Singleton(Singleton &other) = delete;            // 禁止默认拷贝构造
    void operator=(const Singleton &other) = delete; // 禁止拷贝赋值运算符
    static Singleton *getInstance(const string value);
    void SomeBusinessLogic(){};
    string value() const
    {
        return value_;
    }

protected:
    Singleton(const string value) : value_(value){};
    ~Singleton(){}
    string value_;                // 保护成员命名以下划线结尾 
private:
    static Singleton *pinstance_; // 静态的全局访问点，保证只有一个实例
    static std::mutex mutex_; // 互斥访问信息量
};

Singleton *Singleton::pinstance_{nullptr};
std::mutex Singleton::mutex_;


Singleton *Singleton::getInstance(const string value)
{
    // 对单例对象互斥信号量加锁
    // 这里是C++特有的RAII特性：即资源获取时初始化，实现了互斥锁的自动加锁和解锁，避免加锁后因为异常没有解锁，类似智能指针，智能指针生命周期内管理指针，结束后自动释放指针
    std::lock_guard<std::mutex> lock(mutex_);
    if(pinstance_ == nullptr)
    {
        pinstance_ = new Singleton(value);
    }
    return pinstance_;
}

void ThreadFoo()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    Singleton *singleton = Singleton::getInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::getInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main()
{
    std::cout << "If you see the same value, then singleton was reused (yay!\n"
              << "If you see different values, then 2 singletons were created (booo!!)\n\n"
              << "RESULT:\n";
    std::thread t1(ThreadFoo); 
    std::thread t2(ThreadBar); 
    t1.join();
    t2.join(); 
    system("pause");
    return 0;
}