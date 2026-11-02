#pragma once
#include "Plant.h"
#include "World.h"

class Grass : public Plant
{
public:
    Grass(Position position, int turn);
    Grass(Position position);
    Grass();

    virtual ~Grass() override;
    virtual void action(World& world) override;
    virtual void reproduce(World& world) override;

    
};