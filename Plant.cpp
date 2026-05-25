#include "Plant.h"
#include "World.h"

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position) : Organism(power, initiative, liveLength, powerToReproduce, position)
{
	setSpecies("P");
}

Plant::Plant() : Organism()
{
	setSpecies("P");
}

void Plant::move(int dx, int dy)
{
	Organism::move(0, 0);
}

void Plant::onCollision(Organism& other, World& world)
{ 
    if (other.getPower() > getPower()) {
        world.removeOrganism(this);
    }
}

Plant::~Plant() {}


