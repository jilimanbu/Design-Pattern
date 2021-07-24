#include <iostream>
#include <string>
using namespace std;

using std::cout;

class Subject{
public:
    virtual void Request() const=0;
};

class RealSubject : public Subject{
public:
    void Request() const override{
        cout << "RealSubject: Handling request.\n";
    }
};

class Proxy:public Subject{
public:
    Proxy(RealSubject* real_subject):realsubject(new RealSubject(*real_subject)){

    }
    void Request() const override{
        if (this->CheckAccess())
        {
            this->realsubject->Request();
            this->LogAccess();
        }
    }
    ~Proxy(){
        delete realsubject;
    }
private:
    RealSubject* realsubject;
    bool CheckAccess() const {
        cout << "Proxy: Checking access prior to firing a real request.\n";
        return true;
    }
    void LogAccess() const{
        cout << "Proxy: Logging the time of request.\n";
    }
};

void ClientCode(const Subject& subject){
    subject.Request();
}

int main(){
    cout << "Client: Executing the client code with a real subject:\n";
    RealSubject *real_subject = new RealSubject;
    ClientCode(*real_subject);
    cout << "\n";
    cout << "Client: Executing the same client code with a proxy:\n";
    Proxy *proxy = new Proxy(real_subject);
    ClientCode(*proxy);
    system("pause");
    return 0;
}
