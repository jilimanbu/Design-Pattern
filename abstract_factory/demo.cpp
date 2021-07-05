#include <iostream>
#include <string>

class abstractProductA{
// 抽象产品类，定义了产品业务逻辑的接口
public:
    virtual ~abstractProductA(){};
    virtual std::string usefulFuction() const = 0;
};

class concreteProductA1:public abstractProductA{
public:
// 具体产品类，实现了具体的产品逻辑
    std::string usefulFuction() const override{
        return "the result of the product A1.";
    };
};

class concreteProductA2:public abstractProductA{
public:
    std::string usefulFuction() const override{
        return "the result of the product A2.";
    }
};

class abstractProductB{
public:
    virtual ~abstractProductB(){};
    virtual std::string usefulFuction() const = 0;
};

class concreteProductB1:public abstractProductB{
public:
    std::string usefulFuction() const override
    {
        return "the result of the product B1.";
    };
};

class concreteProductB2:public abstractProductB{
public:
    std::string usefulFuction() const override
    {
        return "the result of the product B2.";
    };
};

class abstractCreator{
// 抽象工厂类，定义了生成一系列相关产品的接口
public:
    virtual abstractProductA* createA() const = 0;
    virtual abstractProductB* createB() const = 0;
};

class concreteCreator1:public abstractCreator{
// 具体工厂类，实现了生成一系列具体产品
public:
    abstractProductA* createA() const override{
        return new concreteProductA1(); 
    }
    abstractProductB* createB() const override
    {
        return new concreteProductB1();
    }
};

class concreteCreator2:public abstractCreator{
public:
    abstractProductA* createA() const override{
        return new concreteProductA2();
    }
    abstractProductB* createB() const override{
        return new concreteProductB2();
    }
};

void clientCode(abstractCreator* creator){
    abstractProductA* productA = creator->createA();
    abstractProductB* productB = creator->createB();
    std::cout<< productA->usefulFuction() <<std::endl;
    std::cout<< productB->usefulFuction() <<std::endl;
    delete productA;
    delete productB;
    return ;
}

int main(){
    std::cout << "Client: Testing client code with the first factory type:\n";
    concreteCreator1* creator1 = new concreteCreator1();
    clientCode(creator1);
    delete creator1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    concreteCreator2 *creator2 = new concreteCreator2();
    clientCode(creator2);
    delete creator2;
    system("pause");
    return 0;
}