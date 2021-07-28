#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using std::string;
using std::cout;
using std::time_t;
using std::time;
using std::ctime;
using std::rand;
using std::vector;
using std::srand;


class Memento // 备忘录抽象接口
{
public:
    virtual string GetName() const = 0;  
    virtual string date() const = 0; 
    virtual string state() const = 0;
};


class ConcreteMemento : public Memento
{
private:
    string state_; // 备忘录保存的快照状态
    string date_; // 备忘录的一些自身的内部状态

public:
    ConcreteMemento(std::string state) : state_(state)
    {
        this->state_ = state;
        time_t now = time(0);
        this->date_ = ctime(&now);
    }
    string state() const override
    {
        return this->state_;
    }
    std::string GetName() const override
    {
        return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
    }
    string date() const override
    {
        return this->date_;
    }
};


class Originator // 原发器对象
{
private:
    string state_;
    string GenerateRandomString(int length = 10) // 生成随机字符串来作为对象的序列化表示
    {
        const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;
        string random_string;
        for (int i = 0; i < length; i++)
        {
            random_string += alphanum[rand() % stringLength];
        }
        return random_string;
    }
public:
    Originator(string state) : state_(state)
    {
        std::cout << "Originator: My initial state is: " << this->state_ << "\n";
    }
    void DoSomething()
    {
        cout << "Originator: I'm doing something important.\n";
        this->state_ = this->GenerateRandomString(30);
        cout << "Originator: and my state has changed to: " << this->state_ << "\n";
    }
    Memento *Save() // 添加快照，也就是添加备忘录
    {
        return new ConcreteMemento(this->state_);
    }
    void Restore(Memento *memento) // 恢复状态
    {
        this->state_ = memento->state();
        cout << "Originator: My state has changed to: " << this->state_ << "\n";
    }
};

class Caretaker // 控制备忘录的对象
{
private:
    vector<Memento *> mementos_; // 保存所有备忘录对象指针
    Originator *originator_; // 保存唯一的原发器对象指针

public:
    Caretaker(Originator *originator) : originator_(originator)
    {
        this->originator_ = originator;
    }
    void Backup()  // 添加备忘录对象
    {
        std::cout << "\nCaretaker: Saving Originator's state...\n";
        this->mementos_.push_back(this->originator_->Save());
    }
    void Undo() // 撤销最新的备忘录
    {
        if (!this->mementos_.size()) // 没有备忘录
        {
            return;
        }
        Memento *memento = this->mementos_.back(); // 取出最新的备忘录
        this->mementos_.pop_back();
        cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
        try
        {
            this->originator_->Restore(memento); // 恢复到最新保存的备忘录状态
        }
        catch (...)
        {
            this->Undo(); // 恢复失败后重复撤销动作
        }
    }
    void ShowHistory() const
    {
        cout << "Caretaker: Here's the list of mementos:\n";
        for (Memento *memento : this->mementos_)
        {
            cout << memento->GetName() << "\n";
        }
    }
};


void ClientCode()
{
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    cout << "\n";
    caretaker->ShowHistory();
    cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->Undo();
    cout << "\nClient: Once more!\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    ClientCode();
    system("pause");
    return 0;
}