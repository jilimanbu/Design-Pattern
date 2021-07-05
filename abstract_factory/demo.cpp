#include <iostream>
#include <string>

class AbstractProductA{
// 抽象产品类，定义了产品业务逻辑的接口
public:
    virtual ~AbstractProductA(){};
    virtual std::string usefulFuction() const = 0;
};

class ConcreteProductA1:public AbstractProductA{
public:
// 具体产品类，实现了具体的产品逻辑
    std::string usefulFuction() const override{
        return "the result of the product A1.";
    };
};

class ConcreteProductA2:public AbstractProductA{
public:
    std::string usefulFuction() const override{
        return "the result of the product A2.";
    }
};

class AbstractProductB{
public:
    virtual ~AbstractProductB(){};
    virtual std::string usefulFuction() const = 0;
};

class ConcreteProductB1:public AbstractProductB{
public:
    std::string usefulFuction() const override
    {
        return "the result of the product B1.";
    };
};

class ConcreteProductB2:public AbstractProductB{
public:
    std::string usefulFuction() const override
    {
        return "the result of the product B2.";
    };
};

class AbstractCreator{
// 抽象工厂类，定义了生成一系列相关产品的接口
public:
    virtual AbstractProductA* createA() const = 0;
    virtual AbstractProductB* createB() const = 0;
};

class ConcreteCreator1:public AbstractCreator{
// 具体工厂类，实现了生成一系列具体产品
public:
    AbstractProductA* createA() const override{
        return new ConcreteProductA1(); 
    }
    AbstractProductB* createB() const override
    {
        return new ConcreteProductB1();
    }
};

class ConcreteCreator2:public AbstractCreator{
public:
    AbstractProductA* createA() const override{
        return new ConcreteProductA2();
    }
    AbstractProductB* createB() const override{
        return new ConcreteProductB2();
    }
};

void ClientCode(AbstractCreator* creator){
    AbstractProductA* productA = creator->createA();
    AbstractProductB* productB = creator->createB();
    std::cout<< productA->usefulFuction() <<std::endl;
    std::cout<< productB->usefulFuction() <<std::endl;
    delete productA;
    delete productB;
    return ;
}

int main(){
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteCreator1* creator1 = new ConcreteCreator1();
    ClientCode(creator1);
    delete creator1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteCreator2 *creator2 = new ConcreteCreator2();
    ClientCode(creator2);
    delete creator2;
    system("pause");
    return 0;
}