#include<iostream>
#include<string>

class Product{
public:
    virtual ~Product(){};
    virtual std::string DoStuff() const = 0;
};
class ConcreteProduct1:public Product{
    std::string DoStuff() const override{
        return "{Result of the concreteProduct1}";
    }
};
class ConcreteProduct2 : public Product
{
    std::string DoStuff() const override
    {
        return "{Result of the concreteProduct2}";
    }
};
// 抽象工厂类
class Creator{
public:
    virtual ~Creator(){};
    // 生成产品类
    virtual Product* FactoryMethod() const = 0;
    // 产品类的业务逻辑函数->所有产品有一致的接口
    std::string DoStuff() const{
        Product* product = this->FactoryMethod();
        std::string result = "Creator: The same creator's code has just worked with " + product->DoStuff();
        delete product;
        return result;
    }
};
// 具体工厂类1
class ConcreteCreator1:public Creator{
    Product* FactoryMethod() const override{
        return new ConcreteProduct1();
    }
};
// 具体工厂类2
class ConcreteCreator2:public Creator{
    Product* FactoryMethod() const override{
        return new ConcreteProduct2();
    } 
};


// 客户端代码
void ClientCode(const Creator& creator){
    // 客户端不知道具体的产品，但仍然可以了解产品做了什么
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n" << 
        creator.DoStuff() << std::endl;
};

int main(){
    // 使用第一个产品
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    Creator *creator1 = new ConcreteCreator1();
    ClientCode(*creator1);
    std::cout << std::endl;

    // 使用第二个产品
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    Creator *creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator1;
    delete creator2;
    system("pause");
    return 0;
}