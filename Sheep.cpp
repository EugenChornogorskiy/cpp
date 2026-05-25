
#include "Sheep.h"
#include "World.h"

Sheep::Sheep(Position position) : Animal(3, 3, 10, 6, position)
{
    setSpecies("S"); 
}

Sheep::Sheep() : Sheep(Position(0, 0)) {}

void Sheep::action(World& world)
{ 
    lastPosition = getPosition();
     
    vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
    
    if (!freePositions.empty()) {
        int randomIndex = rand() % freePositions.size();
        Position newPos = freePositions[randomIndex];
         
        Organism* other = world.getOrganismAt(newPos);
        if (other != nullptr && other != this) {
            onCollision(*other, world);
        } else {
            setPosition(newPos);
        }
    }
     
    incrementAge();
    setPower(getPower() + 1); 
}

void Sheep::onCollision(Organism& other, World& world)
{
    string otherSpecies = other.getSpecies();
    
    if (otherSpecies == "G") {  
        setPower(getPower() + other.getPower());
        world.removeOrganism(&other);
        setPosition(other.getPosition());
    } else if (otherSpecies == "S") { 
        if (canReproduce() && other.canReproduce()) {
            reproduce(world);
            other.reproduce(world);
        }
    } else { 
        Animal::onCollision(other, world);
    }
}

void Sheep::reproduce(World& world)
{
    if (canReproduce()) { 
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position childPos = freePositions[rand() % freePositions.size()]; 
            world.addOrganism(make_unique<Sheep>(childPos));
            setPower(getPower() / 2);
        }
    }
}