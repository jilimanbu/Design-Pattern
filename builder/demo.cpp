#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;

// 产品类
class Product1{
public:
    vector<string> part_;
    void ListParts() const {
        cout << "Product parts: ";
        for(size_t i=0;i<part_.size();++i){
            if(part_[i] == part_.back()){
                cout << part_[i];
            }
            else{
                cout << part_[i] << ","; 
            }
        }
        cout << "\n\n";
    }    
};

// 抽象工人类
// 定义了工人需要实现的事情，就是创建产品的接口
class Builder{
public:
    virtual ~Builder(){}
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};

// 具体工人类
// 管理好自己创建的产品，明确自己怎么创建，怎么展示就行
class ConcreteBuilder1:public Builder{
public: 
    ConcreteBuilder1(){
        this->Reset();
    }
    ~ConcreteBuilder1(){
        delete product;
    }
    void Reset(){
        this->product = new Product1(); 
    }
    void ProducePartA() const override{
        this->product->part_.push_back("PartA1");
    } 
    void ProducePartB() const override{
        this->product->part_.push_back("PartB1");
    }
    void ProducePartC() const override{
        this->product->part_.push_back("PartC1");
    }
    Product1* GetProduct(){
        Product1* result = this->product;
        this->Reset();
        return result;
    }
private:
    Product1* product;
};

class Director{
public:
    void set_builder(Builder* builder){
        this->builder=builder;
    }
    // 受约束的创建过程，封装好的
    void BuildMinimalViableProduct(){
        this->builder->ProducePartA();
    }
    // 同上
    void BuildFullFeaturedProduct(){
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
private:
    Builder* builder;
};

void ClientCode(Director &director)
{
    // 通过与指导者（包工头）交互，创建受约束的产品
    ConcreteBuilder1 *builder = new ConcreteBuilder1();
    director.set_builder(builder);
    cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();

    Product1 *p = builder->GetProduct();
    p->ListParts();
    delete p;

    cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();

    p = builder->GetProduct();
    p->ListParts();
    delete p;
    // 直接与创建者（工人）交互，自定义创建过程
    cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main(){
    Director* director = new Director();
    ClientCode(*director);
    delete director;
    system("pause");
    return 0;
}