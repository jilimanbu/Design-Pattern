#include <iostream>
#include <string>
#include <list>

using std::string;
using std::list;
using std::cout;

// 抽象观察者接口，主要为根据观察目标的状态进行更新
class IObserver{
public:
    virtual ~IObserver(){};
    virtual void Update(const string& message_from_subject) = 0; // 抽象观察者的接口
};

// 抽象的观察目标接口，主要声明了添加观察者（订阅者），删除观察者和同通知观察者的三个接口
class ISubject{
public:
    virtual ~ISubject(){};
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

// 具体观察目标
class Subject: public ISubject{
public:
    virtual ~Subject(){
        cout << "Goodbye, I was the Subject.\n";
    }
    // 在观察者列表中加入新的观察者
    void Attach(IObserver* observer) override {
        list_observer_.push_back(observer);
    }
    // 在观察者列表中移除指定观察者
    void Detach(IObserver* observer) override{
        list_observer_.remove(observer);
    }
    // 自动通知列表中所有观察者，这些观察者可能是不同的类型
    void Notify() override {
        auto iter = list_observer_.begin();
        HowManyObserver();
        while(iter!=list_observer_.end()){
            (*iter)->Update(message_);
            ++iter;
        }
    }
    void HowManyObserver(){
        cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }
    // 状态变化函数，生成新的通知，发送给所有观察者
    void CreateMessage(string message="Empty"){
        this->message_ = message;
        Notify();
    }
    // 带状态变化的业务函数，需要通知列表中的所有观察者
    void SomeBusinessLogic(){
        this->message_ = "change message message";
        Notify();
        cout<<"I'm about to do some thing import\n";
    }


private:
    list<IObserver*> list_observer_; // 观察者列表
    string message_; // 状态（通知）
};


class Observer:public IObserver{
public:
    // 观察者构造函数，在构造时指定观察目标，因此一个观察者只能观察一个目标
    Observer(Subject& subject):subject_(subject){
        this->subject_.Attach(this); 
        cout<<"Hi, I'm the Observer \""<<++Observer::static_number_<<"\".\n";
        this->number_ = Observer::static_number_; // 确定这个观察者的编号
    }
    virtual ~Observer(){
        cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }

    // 观察者更新，通过某个通知（观察目标的状态变化）进行自身的更新
    void Update(const string& message_from_subject) override{
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    // 取消订阅，将观察者移除观察目标的列表，不再具有依赖关系
    void RemoveMefromTheList(){
        subject_.Detach(this);
        cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
    void PrintInfo(){
        cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
    }

private:
    string message_from_subject_; // 通知
    Subject& subject_; // 观察目标
    static int static_number_; // 观察者全局变量
    int number_; // 当前观察者的编号
};

int Observer::static_number_ = 0;

void ClientCode(){
    Subject* subject = new Subject();
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4;
    Observer* observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMefromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMefromTheList();
    observer5 = new Observer(*subject);
    
    subject->CreateMessage("My new car is great! :)");
    observer5->RemoveMefromTheList();

    observer4->RemoveMefromTheList();
    observer1->RemoveMefromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main(){
    ClientCode();
    system("pause");
    return 0;
}