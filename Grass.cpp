#include "Grass.h"
#include "World.h"

Grass::Grass(Position position, int turn) : Plant(0, 0, 6, 2, position,turn) 
{
    setSpecies("G");   
}
Grass::Grass(Position position) : Plant(0, 0, 6, 2, position,0) 
{
    setSpecies("G");   
}
Grass::Grass() : Grass(Position(0, 0),0) {}
Grass::~Grass() {}

void Grass::action(World& world)
{ 
    incrementAge();
    setPower(getPower() + 1);
     
    if (canReproduce()) {
        reproduce(world);
    }
}

void Grass::reproduce(World& world)
{
    if (canReproduce()) {
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position childPos = freePositions[rand() % freePositions.size()]; 
            auto child = make_unique<Grass>(childPos,world.getTurn());  
            child->copyAncestorsFrom(*this, world.getTurn());
            world.addOrganism(std::move(child));
            setPower(getPower() / 2);
        }
    }
}