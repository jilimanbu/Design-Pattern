#include <iostream>
#include <string>

using std::string;
using std::cout;

// 实现类
class Implementation{
public:
    virtual ~Implementation(){}
    virtual string OperationImplementation() const = 0;
};
// 具体实现类
class ConcreteImplementationA: public Implementation{
public:
    string OperationImplementation() const override{
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};

class ConcreteImplementationB:public Implementation{
public:
    string OperationImplementation() const override{
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};
// 抽象类
class Abstraction{
protected:
    Implementation* implementation_; // 使用组合机制实现运行时多态，选择不同的实现
public:
    Abstraction(Implementation* implementation):implementation_(implementation){
    }
    virtual ~Abstraction(){
    }
    virtual string Operation() const{
        return "Abstraction: Base operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};
// 扩展抽象类，重载了抽象类中的操作
class ExtendedAbstraction:public Abstraction{
public:
    ExtendedAbstraction(Implementation* implementation):Abstraction(implementation){
    }
    string Operation() const override{
        return "ExtendedAbstraction: Extended operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};

void ClientCode(const Abstraction& abstraction){
    cout<<abstraction.Operation();
}

int main(){
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    cout<<"\n";
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);
    delete implementation;
    delete abstraction;

    system("pause");
    return 0;


}