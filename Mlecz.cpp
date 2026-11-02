#include "Mlecz.h"
#include "World.h"

Mlecz::Mlecz(Position position, int turn) : Plant(0, 0, 6, 2, position,turn) 
{
    setSpecies("D");   
}
Mlecz::Mlecz(Position position) : Plant(0, 0, 6, 2, position,0) 
{
    setSpecies("D");   
}
Mlecz::Mlecz() : Mlecz(Position(0, 0),0) {}
Mlecz::~Mlecz() {}

void Mlecz::action(World& world)
{ 
    incrementAge();
    setPower(getPower() + 1);
     
    if (canReproduce()) {
        reproduce(world);
    }
}

void Mlecz::reproduce(World& world)
{
    if (canReproduce()) {
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position childPos = freePositions[rand() % freePositions.size()]; 
            auto child = make_unique<Mlecz>(childPos,world.getTurn());  
            child->copyAncestorsFrom(*this, world.getTurn());
            world.addOrganism(std::move(child));
            setPower(getPower() / 2);
        }
    }
}