#pragma once
#include "Plant.h"
#include "World.h"

class Mlecz : public Plant
{
public:
    Mlecz(Position position, int turn);
    Mlecz(Position position);
    Mlecz();

    virtual ~Mlecz() override;
    virtual void action(World& world) override;
    virtual void reproduce(World& world) override;

    
};