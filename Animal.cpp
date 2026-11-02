#include "Animal.h"
#include "World.h"
#include <fstream>
#include <cstdlib>

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position,int turn) : Organism(power, initiative, liveLength, powerToReproduce, position,turn), lastPosition(position)
{
    setSpecies("A");
} 
Animal::Animal() : Organism()
{
	setSpecies("A");
}

Animal::Animal(const Animal& other) : Organism(other), lastPosition(other.lastPosition){}
Animal::Animal(Animal&& other) noexcept : Organism(std::move(other)), lastPosition(std::move(other.lastPosition)){}
Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        Organism::operator=(other);
        lastPosition = other.lastPosition;
    }
    return *this;
}
Animal& Animal::operator=(Animal&& other) noexcept {
    if (this != &other) {
        Organism::operator=(std::move(other));
        lastPosition = std::move(other.lastPosition);
    }
    return *this;
}
Animal::~Animal() {}


Position Animal::getLastPosition() const { return lastPosition; }
void Animal::setLastPosition(Position pos) { lastPosition = pos; }


void Animal::onCollision(Organism& other, World& world)
{ 
    if (getPower() >= other.getPower()) { 
        other.setLiveLength(-1); 
        setPosition(other.getPosition());
    } else { 
        this->setLiveLength(-1);
    }
}

void Animal::serialize(ofstream& file) const
{
    Organism::serialize(file);
    int lx = lastPosition.getX();
    int ly = lastPosition.getY();
    file.write((char*)&lx, sizeof(int));
    file.write((char*)&ly, sizeof(int));
}

void Animal::deserialize(ifstream& file)
{
    Organism::deserialize(file);
    int lx, ly;
    file.read((char*)&lx, sizeof(int));
    file.read((char*)&ly, sizeof(int));
    setLastPosition(Position(lx, ly));
}
