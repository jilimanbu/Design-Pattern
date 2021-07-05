#include <iostream>
#include <string>
#include <unordered_map>
using std::string;

// 枚举类型表示原型的类型
enum Type{
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

// 抽象原型类，声明了复制接口和业务逻辑接口
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
// 具体原型类，实现原型的复制
class ConcretePrototype1:public Prototype{
private:
    float concrete_prototype_field1_;
public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field){
    }
    Prototype* Clone() const override{
        // 深拷贝复制
        // 继承体系下需要调用各自的构造函数，避免生成父类对象
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
// 原型工厂函数，基于抽象工厂模式，客户端调用业务逻辑
// 工厂类只是预生成了所有原型，然后通过复制进行构建
class PrototypeFactory{
private:
    // 使用哈希表进行原型类型到抽象原型类指针的映射
    std::unordered_map<Type, Prototype *,std::hash<int>> prototypes_;

public:
    PrototypeFactory(){
        // 构建原型哈希表
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1",50.f);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2",60.f);
    }
    ~PrototypeFactory(){
        // 析构原型哈希表
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    Prototype* CreatePrototype(Type type){
        // 根据原型类型生成一个具体的原型对象/指针
        return prototypes_[type]->Clone();
    }
};

void Client(PrototypeFactory& prototype_factory){
    // 客户端调用业务逻辑，为抽象工厂模式
    std::cout << "Let's create a prototype 1\n";
    Prototype* prototype1 = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype1->Method(90.f);
    // 客户端生成的原型对象（客户端本身不认为这个对象与其它产品有区别）需要自己析构
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