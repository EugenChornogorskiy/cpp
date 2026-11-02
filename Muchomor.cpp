#include "Muchomor.h"
#include "World.h"

Muchomor::Muchomor(Position position, int turn) : Plant(0, 0, 12, 4, position,turn) 
{
    setSpecies("T");   
}
Muchomor::Muchomor(Position position) : Plant(0, 0, 12, 4, position,0) 
{
    setSpecies("T");   
}
Muchomor::Muchomor() : Muchomor(Position(0, 0),0) {}
Muchomor::~Muchomor() {}

void Muchomor::action(World& world)
{ 
    incrementAge();
    setPower(getPower() + 1);
     
    if (canReproduce()) {
        reproduce(world);
    }
}

void Muchomor::reproduce(World& world)
{
    if (canReproduce()) {
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position childPos = freePositions[rand() % freePositions.size()]; 
            auto child = make_unique<Muchomor>(childPos,world.getTurn());  
            child->copyAncestorsFrom(*this, world.getTurn());
            world.addOrganism(std::move(child));
            setPower(getPower() / 2);
        }
    }
}