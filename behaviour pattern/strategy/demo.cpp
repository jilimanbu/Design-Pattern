#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::for_each;
using std::sort;
using std::swap;
using std::begin;
using std::end;

// 抽象基类，声明了算法接口
class Strategy{
public:
    virtual ~Strategy(){};
    virtual string DoAlgorithm(const vector<string>& data) const=0;
};

// 上下文类，声明了多态策略对象和算法执行的上下文，以及更改算法的方法
class Context{
private:
    Strategy* strategy_;
public:
    Context(Strategy* strategy=nullptr):strategy_(strategy)
    {
    }
    ~Context(){
        delete strategy_;
    }
    void set_strategy(Strategy* strategy){
        delete this->strategy_;
        this->strategy_ = strategy;
    }
    void DoSomeBusinessLogic() const {
        cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
        string result = this->strategy_->DoAlgorithm(std::vector<std::string>{"a", "e", "c", "b", "d"});
        cout << result << "\n";
    }
};

// 具体策略对象，实现了算法策略接口
class ConcreteStrategyA : public Strategy
{
public:
    std::string DoAlgorithm(const vector<string> &data) const override
    {
        string result;
        for_each(begin(data), end(data), [&result](const string &letter)
                    { result += letter; });
        sort(begin(result), end(result));

        return result;
    }
};

class ConcreteStrategyB:public Strategy{
public:
    string DoAlgorithm(const vector<string>& data) const override
    {
        string result;
        for_each(begin(data),end(data),[&result](const string& letter)
                    {result+=letter;});
        sort(begin(result), end(result));
        for(int i=0;i<result.size()/2;++i){
            swap(result[i],result[result.size()-i-1]);
        }
        return result;
    }
};

void ClientCode(){
    Context* context = new Context(new ConcreteStrategyA);
    cout << "Client: Strategy is set to normal sorting.\n";
    context->DoSomeBusinessLogic();
    cout << "\n";
    cout << "Client: Strategy is set to reverse sorting.\n";
    context->set_strategy(new ConcreteStrategyB);
    context->DoSomeBusinessLogic();
    delete context;
}

int main(){
    ClientCode();
    system("pause");
    return 0;
}