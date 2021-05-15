#include "strategy_pattern_skill.h"
#include "strategy_pattern_hero.h"


void Hero::attack(Hero *targetHero)
{
    int damage = skill->attack(this, targetHero);
    targetHero->subHp(damage);
}