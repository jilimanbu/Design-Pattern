#ifndef __STRATEGY_PATTERN_HERO_H__
#define __STRATEGY_PATTERN_HERO_H__

#include <string>

class Skill;

class Hero
{
friend class Battle;
public:
    void subHp(int hp){
        this->hp -= hp;
    }
    void subMp(int mp){
        this->mp -= mp;
    }
    void setSkill(Skill *skillName)
    {
        this->skill = skillName;
    }
    int getHp(){
        return this->hp;
    }
    int getMp(){
        return this->mp;
    }
    int getStrength(){
        return this->strength;
    }
    int getWisdom(){
        return this->wisdom;
    }
    int getDefense(){
        return this->defense;
    }
    std::string getName(){
        return this->name;
    }
    Hero(std::string name, int hp = 20, int mp = 20, int strength = 10, int wisdom = 5, int defense = 5) : 
        name(name), hp(hp), mp(mp), strength(strength), wisdom(wisdom), defense(defense) {}
    virtual ~Hero(){};
private:
    std::string name;
    int hp;
    int mp;
    int strength;
    int wisdom;
    int defense;
    Skill *skill;
    void attack(Hero *targetHero);
};
#endif