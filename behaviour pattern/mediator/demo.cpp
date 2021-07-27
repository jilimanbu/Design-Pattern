#include <iostream>
#include <string>
using std::string;
using std::cout;

class BaseComponent;
class Mediator{
public:
    // 中介者的任务就是完成组件之间的通信
    virtual void Notify(BaseComponent* sender,string event) const=0;
};

class BaseComponent{
protected:
    // 组件与中介者相关联，组合方式
    Mediator* mediator_;
public:
    BaseComponent(Mediator* mediator = nullptr):mediator_(mediator){

    }
    void set_mediator(Mediator* mediator){
        this->mediator_ = mediator;
    }
};

class Component1:public BaseComponent{
public:
    void DoA(){
        cout << "Component 1 does A.\n";
        this->mediator_->Notify(this, "A");
    }
    void DoB()
    {
        cout << "Component 1 does B.\n";
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent
{
public:
    void DoC()
    {
        cout << "Component 2 does C.\n";
        this->mediator_->Notify(this, "C");
    }
    void DoD()
    {
        cout << "Component 2 does D.\n";
        this->mediator_->Notify(this, "D");
    }
};

class ConcreteMediator:public Mediator{
private:
    // 与所有组件相关联，组合方式
    Component1* component1_; 
    Component2* component2_;
public:
    ConcreteMediator(Component1* c1,Component2* c2):component1_(c1),component2_(c2){
        this->component1_->set_mediator(this); // 组件与中介者进行关联
        this->component2_->set_mediator(this);
    }
    void Notify(BaseComponent* sender,string event) const override{
        if(event == "A"){
            std::cout << "Mediator reacts on A and triggers following operations:\n";
            this->component2_->DoC();
        }
        if (event == "D")
        {
            std::cout << "Mediator reacts on D and triggers following operations:\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

void ClientCode(){
    Component1* c1 = new Component1;
    Component2* c2 = new Component2;
    ConcreteMediator* mediator = new ConcreteMediator(c1,c2);
    cout << "Client triggers operation A.\n";
    c1->DoA();
    cout << "\n";
    cout << "Client triggers operation D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}

int main(){
    ClientCode();
    system("pause");
    return 0;
}