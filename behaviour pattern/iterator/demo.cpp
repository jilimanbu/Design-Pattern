#include <iostream>
#include <string>
#include <vector>


template <typename T, typename U>
class Iterator // 声明迭代器接口
{
public:
    typedef typename std::vector<T>::iterator iter_type; // traits技巧 在编译时根据相应的迭代器对迭代器自身的特征进行萃取
    Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data)
    {
        m_it_ = m_p_data_->m_data_.begin(); // 将当前迭代器初始化为第一个迭代器
    }
    // 返回第一个迭代器
    void First()
    {
        m_it_ = m_p_data_->m_data_.begin();
    }
    // 返回下一个迭代器
    void Next()
    {
        m_it_++;
    }
    // 返回是否为最后一个迭代器
    bool IsDone()
    {
        return (m_it_ == m_p_data_->m_data_.end());
    }
    // 返回当前迭代器
    iter_type Current()
    {
        return m_it_;
    }

private:
    U *m_p_data_; // 迭代器指向的元素
    iter_type m_it_; // 当前迭代器
};


template <class T>
class Container
{
    friend class Iterator<T, Container>; // 将相应的迭代器声明为友元，便于迭代器访问
public:
    // 在容器中添加元素
    void Add(T a)
    {
        m_data_.push_back(a);
    }
    // 为容器创建相应的迭代器
    Iterator<T, Container> *CreateIterator()
    {
        return new Iterator<T, Container>(this);
    }

private:
    std::vector<T> m_data_; 
};

// 复杂/自定义的元素类型
class Data
{
public:
    Data(int a = 0) : m_data_(a) {}

    void set_data(int a)
    {
        m_data_ = a;
    }

    int data()
    {
        return m_data_;
    }

private:
    int m_data_;
};

 
void ClientCode()
{
    std::cout << "________________Iterator with int______________________________________" << std::endl;
    Container<int> cont;

    for (int i = 0; i < 10; i++)
    {
        cont.Add(i);
    }

    Iterator<int, Container<int>> *it = cont.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next())
    {
        std::cout << *it->Current() << std::endl;
    }

    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.Add(a);
    cont2.Add(b);
    cont2.Add(c);

    std::cout << "________________Iterator with custom Class______________________________" << std::endl;
    Iterator<Data, Container<Data>> *it2 = cont2.CreateIterator();
    for (it2->First(); !it2->IsDone(); it2->Next())
    {
        std::cout << it2->Current()->data() << std::endl;
    }
    delete it;
    delete it2;
}

int main()
{
    ClientCode();
    system("pause");
    return 0;
}