#ifndef __STRATEGY_PATTERN_SKILL_H__
#define __STRATEGY_PATTERN_SKILL_H__

#include <string>
#include "strategy_pattern_hero.h"

class Skill
{
public:
    std::string skillName;
    Skill(std::string skillname) : skillName(skillname){};
    ~Skill();
    virtual int attack(Hero *AttachHero, Hero *targetHero) = 0;
};

class Colliding : public Skill
{
public:
    Colliding(std::string name) : Skill(name){};
    ~Colliding();
    int attack(Hero *attackHero, Hero *targetHero);
};

class Waterball : public Skill
{
public:
    Waterball(std::string name) : Skill(name) {}
    ~Waterball();
    int attack(Hero *attackHero, Hero *targetHero);
};
#endif