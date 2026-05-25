#include "Grass.h"
#include "World.h"

Grass::Grass(Position position) : Organism(0, 0, 6, 2, position) 
{
    setSpecies("G");  
}

Grass::Grass() : Grass(Position(0, 0)) {}
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
            world.addOrganism(make_unique<Grass>(childPos));
            setPower(getPower() / 2);
        }
    }
}