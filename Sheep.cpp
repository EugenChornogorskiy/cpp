
#include "Sheep.h"
#include "World.h"

Sheep::Sheep(Position position,int turn) : Animal(3, 3, 10, 6, position,turn)
{
    setSpecies("S"); 
}
Sheep::Sheep(Position position) : Animal(3, 3, 10, 6, position,0)
{
    setSpecies("S"); 
}
Sheep::Sheep() : Sheep(Position(0, 0),0) {}

void Sheep::action(World& world)
{ 
    setLastPosition(getPosition());
     
    vector<Position> freePositions = world.getVectorOfPositionsAround(getPosition());
    
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
        other.setLiveLength(-1);
        setPosition(other.getPosition());
    } 
    else if (otherSpecies == "S") { 
        if (canReproduce() && other.canReproduce()) {
            reproduce(world);
            other.reproduce(world);
        }
    } 
    else if (otherSpecies == "W") { 
        this->setLiveLength(-1);
    } 
    else { 
        Animal::onCollision(other, world);
    }
}

void Sheep::reproduce(World& world)
{
    if (canReproduce()) { 
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position childPos = freePositions[rand() % freePositions.size()]; 
            auto child = make_unique<Sheep>(childPos,world.getTurn()); 
            child->copyAncestorsFrom(*this, world.getTurn());
            world.addOrganism(std::move(child));
            setPower(getPower() / 2);
        }
    }
}