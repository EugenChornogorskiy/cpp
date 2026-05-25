#pragma once
#include "Organism.h"
#include "World.h"

class Grass : public Organism
{
public:
    Grass(Position position);
    Grass();

    virtual ~Grass() override;
    virtual void action(World& world) override;
    virtual void reproduce(World& world) override;

    
};