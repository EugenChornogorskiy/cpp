
#include "Wilk.h"
#include "World.h"

Wilk::Wilk(Position position,int turn) : Animal(8, 5, 20, 16, position,turn)
{
    setSpecies("W"); 
}
Wilk::Wilk(Position position) : Animal(8, 5, 20, 16, position,0)
{
    setSpecies("W"); 
}

Wilk::Wilk() : Wilk(Position(0, 0),0) {}

void Wilk::action(World& world)
{ 
    setLastPosition(getPosition());     
    
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

void Wilk::onCollision(Organism& other, World& world)
{
    string otherSpecies = other.getSpecies();
    
    if (otherSpecies == "S") {  
        setPower(getPower() + other.getPower());
        other.setLiveLength(-1);
        setPosition(other.getPosition());
    } else if (otherSpecies == "W") { 
        if (canReproduce() && other.canReproduce()) {
            reproduce(world);
            other.reproduce(world);
        }
    } else { 
        Animal::onCollision(other, world);
    }
}

void Wilk::reproduce(World& world)
{
    if (canReproduce()) { 
        vector<Position> freePositions = world.getVectorOfFreePositionsAround(getPosition());
        if (!freePositions.empty()) {
            Position childPos = freePositions[rand() % freePositions.size()]; 
            auto child = make_unique<Wilk>(childPos,world.getTurn()); 
            child->copyAncestorsFrom(*this, world.getTurn());
            world.addOrganism(std::move(child));
            setPower(getPower() / 2);
        }
    }
}