#include <iostream>
#include <string>
#include <unordered_map>
using std::string;

enum Type{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype{
protected:
    string prototype_name_;
    float prototype_field_;
public:
    Prototype(){};
    Prototype(string prototype_name)
        : prototype_name_(prototype_name){

    }
    virtual ~Prototype(){};
    virtual Prototype* Clone() const=0;
    virtual void Method(float prototype_field){
        this->prototype_field_ = prototype_field;
        std::cout<< "Call Method from " << prototype_name_ << " with field : " << prototype_field_ << std::endl;
    }
};

class ConcretePrototype1:public Prototype{
private:
    float concrete_prototype_field1_;
public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field){
    }
    Prototype* Clone() const override{
        // 深拷贝
        return new ConcretePrototype1(*this);
    }
};  

class ConcretePrototype2:public Prototype{
private:
    float concrete_prototype_field2_;
public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field)
    {
    }
    Prototype *Clone() const override
    {
        return new ConcretePrototype2(*this);
    }
};

class PrototypeFactory{
private:
    std::unordered_map<Type, Prototype *,std::hash<int>> prototypes_;

public:
    PrototypeFactory(){
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1",50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2",60.f);
    }
    ~PrototypeFactory(){
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    Prototype* CreatePrototype(Type type){
        return prototypes_[type]->Clone();
    }
};

void Client(PrototypeFactory& prototype_factory){
    std::cout << "Let's create a prototype 1\n";
    Prototype* prototype1 = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype1->Method(90.f);
    delete prototype1;

    std::cout << "\n";

    std::cout << "Let's create a prototype 2\n";
    Prototype* prototype2 = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype2->Method(10);

    delete prototype2;
}

int main(){
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;
    system("pause");
    return 0;
}