#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using std::string;
using std::list;
using std::cout;

class Component // 抽象组合对象
{
protected:
    Component *parent_; // 指向父节点的指针
public:
    virtual ~Component() {}
    void SetParent(Component *parent) // 加入父节点
    {
        this->parent_ = parent;
    }
    Component *GetParent() const // 获取对象的父节点指针
    {
        return this->parent_;
    }
    virtual void Add(Component *component) {} // 默认操作，叶子对象不进行重写，对象容器需要进行重写
    virtual void Remove(Component *component) {} // 默认操作，叶子对象不进行重写，对象容器需要进行重写
    virtual bool IsComposite() const // 判断是否为对象容器，而不是叶子对象
    {
        return false;
    }  
    virtual string Operation() const = 0;
};

class Leaf : public Component // 叶子对象
{
public:
    string Operation() const override
    {
        return "Leaf";
    }
};
class Composite : public Component // 对象容器，又称为组合对象
{
protected:
    list<Component *> children_; // 底层容器的数据结构，保存子对象，可以是叶子对象，也可以是对象容器

public:
    void Add(Component *component) override  // 重写添加对象的函数
    {
        this->children_.push_back(component);
        component->SetParent(this);
    }
    void Remove(Component *component) override // 重写移除子对象的函数
    {
        children_.remove(component);
        component->SetParent(nullptr);
    }
    bool IsComposite() const override 
    {
        return true;
    }
    string Operation() const override
    {
        string result;
        for (const Component *c : children_)
        {
            if (c == children_.back())
            {
                result += c->Operation();
            }
            else
            {
                result += c->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};

void ClientCode(Component *component)
{
    cout << "RESULT: " << component->Operation();
}

void ClientCode2(Component *component1, Component *component2)
{
    if (component1->IsComposite())
    {
        component1->Add(component2);
    }
    cout << "RESULT: " << component1->Operation();
}

int main()
{
    Component *simple = new Leaf;
    cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    cout << "\n\n";

    Component *tree = new Composite;
    Component *branch1 = new Composite;

    Component *leaf_1 = new Leaf;
    Component *leaf_2 = new Leaf;
    Component *leaf_3 = new Leaf;
    branch1->Add(leaf_1);
    branch1->Add(leaf_2);
    Component *branch2 = new Composite;
    branch2->Add(leaf_3);
    tree->Add(branch1);
    tree->Add(branch2);
    cout << "Client: Now I've got a composite tree:\n";
    ClientCode(tree);
    cout << "\n\n";

    cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(tree, simple);
    cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

    system("pause");
    return 0;
}