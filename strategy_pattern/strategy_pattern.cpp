#include <iostream>
#include <string>
#include "strategy_pattern_skill.h"
#include "strategy_pattern_hero.h"
using namespace std;

/*
//////////
// 版本一：多态实现不同的攻击形式
// 问题： 基于一个成员函数的实现而滥用继承，会导致真正需要继承的时候造成组合爆炸的问题
// 代码细节：类成员变量访问权限的设置
//////////
class Hero{
public:
    Hero(string name,int hp=20,int mp=20,int strength=10,int wisdom=5,int defense=5):
        name(name),hp(hp),mp(mp),strength(strength),wisdom(wisdom),defense(defense){}
    virtual ~Hero(){};
    virtual void attack(Hero* hero){};
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
    void attack(Hero *hero)
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
    void attack(Hero* hero){
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
*/
//////////
// 版本二: 将招式（策略）抽象为一个类
// 优点：遵循单一职责原则，不滥用继承
//////////



class Battle
{
public:
    Hero *hero1;
    Hero *hero2;
    Battle(Hero *hero1, Hero *hero2) : hero1(hero1), hero2(hero2){};
    void start()
    {
        int now = 0;
        while (hero1->hp > 0 && hero2->hp > 0)
        {
            if (now == 0)
            {
                hero1->attack(hero2);
                now = 1;
            }
            else
            {
                hero2->attack(hero1);
                now = 0;
            }
        }
        if (hero1->hp <= 0)
        {
            cout << hero2->name << " win!!" << endl;
        }
        else
        {
            cout << hero1->name << " win!!" << endl;
        }
    }
};
int main()
{
    Hero* hero1 = new Hero("Mingming",100);
    Hero* hero2 = new Hero("Dingding",50);
    Skill* colliding = new Colliding("Colliding Level 1");
    Skill* waterball = new Waterball("Waterball level 1");
    hero1->setSkill(colliding);
    hero2->setSkill(waterball);
    Battle battle(hero1,hero2);
    battle.start();
    delete hero1;
    delete hero2;
    delete colliding;
    delete waterball;
    system("pause");
    return 0;
}