#include <iostream>
#include "strategy_pattern_skill.h"
#include "strategy_pattern_hero.h"

using namespace std;

Skill::~Skill()
{
}

Colliding::~Colliding()
{
}

Waterball::~Waterball()
{
}

int Colliding::attack(Hero *attackHero, Hero *targetHero)
{
    int damage = attackHero->getStrength() - targetHero->getDefense();
    std::cout << attackHero->getName() << " use " << this->skillName << ", " << targetHero->getName() << " hp-" << damage << " !!" << std::endl;
    return damage;
}

int Waterball::attack(Hero *attackHero, Hero *targetHero)
{
    int damage=0;
    if (attackHero->getMp() >= 5)
    {
        damage = attackHero->getWisdom() * 2;
        attackHero->subMp(5);
        std::cout << attackHero->getName() << " use " << this->skillName << ", " << targetHero->getName() << " hp-" << damage << " !!" << std::endl;
        return damage;
    }
    else
    {
        cout << attackHero->getName() << " is short of mp!!" << endl;
    }
    return damage;
}
