#include <iostream>
#include <string>
#include <array>


class ConcreteComponentA;
class ConcreteComponentB;
// 抽象访问者
class Visitor
{
public:
    // 定义了对类层次结构中每个元素的访问方法
    virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};


// 抽象的被访问者，定义了接受访问的接口，虚函数进行第一次分发，分发给相应的元素
class Component
{
public:
    virtual ~Component() {}
    virtual void Accept(Visitor *visitor) const = 0;
};

// 具体访问元素
class ConcreteComponentA : public Component
{
public:
    // 实现接受访问的接口
    void Accept(Visitor *visitor) const override
    {
        visitor->VisitConcreteComponentA(this);
    }
    std::string ExclusiveMethodOfConcreteComponentA() const
    {
        return "A";
    }
};

class ConcreteComponentB : public Component
{
public:
    void Accept(Visitor *visitor) const override
    {
        visitor->VisitConcreteComponentB(this);
    }
    std::string SpecialMethodOfConcreteComponentB() const
    {
        return "B";
    }
};

// 具体访问类
class ConcreteVisitor1 : public Visitor
{
public:
    // 实现访问每种元素的方法，继承于访问者类，运行时根据虚函数进行第二次分发，分发到具体的访问者上
    void VisitConcreteComponentA(const ConcreteComponentA *element) const override
    {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }

    void VisitConcreteComponentB(const ConcreteComponentB *element) const override
    {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};


class ConcreteVisitor2 : public Visitor
{
public:
    void VisitConcreteComponentA(const ConcreteComponentA *element) const override
    {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB *element) const override
    {
        std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};


void ClientCode(std::array<const Component *, 2> components, Visitor *visitor)
{
    for (const Component *comp : components)
    {
        comp->Accept(visitor);
    }
}


int main()
{
    std::array<const Component *, 2> components = {new ConcreteComponentA, new ConcreteComponentB};
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component *comp : components)
    {
        delete comp;
    }
    delete visitor1;
    delete visitor2;
    system("pause");
    return 0;
}