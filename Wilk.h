#pragma once
#include "Animal.h"
#include "World.h"

class Wilk : public Animal
{
public:
    Wilk(Position position,int turn);
    Wilk(Position position);
    Wilk();
    
    virtual void onCollision(Organism& other, World& world) override;
    virtual void reproduce(World& world) override;
    virtual void action(World& world) override;
};