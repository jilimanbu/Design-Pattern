#include <iostream>
#include <string>

// 抽象命令对象，声明了命令的接口
class Command
{
public:
    virtual ~Command()
    {
    }
    virtual void Execute() const = 0;
};

// 具体命令对象，完成对具体命令请求的转发
class SimpleCommand : public Command
{
private:
    // 命令参数设置为私有成员
    std::string pay_load_;

public:
    // 不允许隐式转换的构造函数
    explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load)
    {
    }
    // 重写具体的命令执行方法，简单的命令可以直接由命令对象完成请求的实现
    void Execute() const override
    {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
    }
};


// 命令对象的接受者
class Receiver
{
public:
    // 对于命令的处理逻辑
    void DoSomething(const std::string &a)
    {
        std::cout << "Receiver: Working on (" << a << ".)\n";
    }
    void DoSomethingElse(const std::string &b)
    {
        std::cout << "Receiver: Also working on (" << b << ".)\n";
    }
};


// 具体命令对象
class ComplexCommand : public Command
{
private:
    // 命令的参数以及实际命令的实现者（也是实际请求的接受者）
    Receiver *receiver_;
    std::string a_;
    std::string b_;
public:
    ComplexCommand(Receiver *receiver, std::string a, std::string b) : receiver_(receiver), a_(a), b_(b)
    {
    }
    // 通过请求接受者完成命令的实现
    void Execute() const override
    {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->receiver_->DoSomething(this->a_);
        this->receiver_->DoSomethingElse(this->b_);
    }
};


// 请求的发起者
class Invoker
{
private:
    // 设置抽象的请求对象（也是命令对象）
    Command *on_start_;
    Command *on_finish_;
public:
    ~Invoker()
    {
        delete on_start_;
        delete on_finish_;
    }
    // 运行时绑定命令对象
    void SetOnStart(Command *command)
    {
        this->on_start_ = command;
    }
    void SetOnFinish(Command *command)
    {
        this->on_finish_ = command;
    }
    // 命令的发起，借助命令对象完成而无需关心命令如何实现
    void DoSomethingImportant()
    {
        std::cout << "Invoker: Does anybody want something done before I begin?\n";
        if (this->on_start_)
        {
            this->on_start_->Execute();
        }
        std::cout << "Invoker: ...doing something really important...\n";
        std::cout << "Invoker: Does anybody want something done after I finish?\n";
        if (this->on_finish_)
        {
            this->on_finish_->Execute();
        }
    }
};

int main()
{
    // 命令发起者在运行时绑定到具体的命令对象，由命令对象自己决定如何实现命令（实现或转发）
    Invoker *invoker = new Invoker;
    invoker->SetOnStart(new SimpleCommand("Say Hi!"));
    Receiver *receiver = new Receiver;
    invoker->SetOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;
    system("pause");
    return 0;
}