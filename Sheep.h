#pragma once
#include "Animal.h"
#include "World.h"

class Sheep : public Animal
{
public:
    Sheep(Position position,int turn);
    Sheep(Position position);
    Sheep();
    
    virtual void onCollision(Organism& other, World& world) override;
    virtual void reproduce(World& world) override;
    virtual void action(World& world) override;
};