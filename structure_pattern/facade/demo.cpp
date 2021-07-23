#include <iostream>
#include <string>

using std::string;
using std::cout;

class Subsystem1{
public:
    string Operation1() const{
        return "Subsystem1: Ready!\n";
    }
    string OperationN() const{
        return "Subsystem1: Go!\n";
    }
};

class Subsystem2{
public:
    string Operation1() const {
        return "Subsystem2: Get ready!\n";
    }
    string OperationZ() const {
        return "Subsystem2: Fire!\n";
    }
};


class Facade{
// 组合形式包含所有子系统
protected:
    Subsystem1* subsystem1_; 
    Subsystem2* subsystem2_;
public:
    Facade(Subsystem1* subsystem1=nullptr,Subsystem2* subsystem2=nullptr){
        this->subsystem1_=subsystem1?:new Subsystem1;
        this->subsystem2_=subsystem2?:new Subsystem2;
    }
    ~Facade(){
        //delete this->subsystem1_;
        //delete this->subsystem2_;
        delete subsystem1_; // 析构指针对象
        delete subsystem2_; // 析构指针对象
    }
    // 简化接口调用，包括接口调用顺序和子系统之间的配合
    string Opearation(){
        string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

void ClientCode(Facade* facade){
    cout<<facade->Opearation();
};

int main(){
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;
    Facade* facade = new Facade(subsystem1,subsystem2);
    ClientCode(facade);
    delete facade;
    system("pause");
    return 0;
}


