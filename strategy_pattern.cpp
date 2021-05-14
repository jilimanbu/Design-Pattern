#include <iostream>
#include <string>
using namespace std;
class Hero{
public:
    Hero(string name,int hp=20,int mp=20,int strength=10,int wisdom=5,int defense=5):
        name(name),hp(hp),mp(mp),strength(strength),wisdom(wisdom),defense(defense){}
    virtual ~Hero(){};
    virtual void attach(Hero* hero){};
    string name;
    int hp;
    int mp;
    int strength;
    int wisdom;
    int defense;
};
class PhysicalHero : public Hero{
public:
    PhysicalHero(string name, int hp = 20, int mp = 20, int strength = 10, int wisdom = 5, int defense = 5):
        // 显示调用基类的构造函数，否则调用基类的默认构造函数
        Hero(name, hp, mp, strength, wisdom, defense){}
    ~PhysicalHero(){};
    void attach(Hero *hero)
    {
        hero->hp-=this->strength-hero->defense;
        cout << hero->name << " is attached by " << this->name << "!! hp-" << this->strength - hero->defense << " !!" << endl;
        return;
    }
};
class MagicalHero:public Hero{
public:
    MagicalHero(string name, int hp = 20, int mp = 20, int strength = 10, int wisdom = 5, int defense = 5):
        Hero(name, hp, mp, strength, wisdom, defense){}
    ~MagicalHero(){};
    void attach(Hero* hero){
        if(this->mp>=5){
            hero->hp -= this->wisdom*2;
            this->mp -= 5;
            cout << hero->name << " is attached by "<< this->name << "!! hp-" << this->wisdom * 2 << " !!" << endl;
        }
        else{
            cout << hero->name << " is short of mp!!"  << endl;
        }
        return;
    }
};
class Battle{
public:
    Battle(Hero* hero1,Hero* hero2):hero1(hero1),hero2(hero2){};
    Hero* hero1;
    Hero* hero2;
    void start(){
        int now=0;
        while(hero1->hp >0 && hero2->hp>0){
            if(now==0){
                hero1->attach(hero2);
                now=1;
            }
            else{
                hero2->attach(hero1);
                now=0;
            }
        }
        if(hero1->hp<=0){
            cout<<hero2->name << " win!!"<<endl;
        }
        else{
            cout<<hero1->name << " win!!"<<endl;
        }
    }
};
int main(){
    Hero* hero1 = new PhysicalHero("Mingming");
    Hero* hero2 = new MagicalHero("Dingding");
    Battle round1(hero1,hero2);
    round1.start();
    delete hero1;
    delete hero2;
    system("pause");
    return 0;
}