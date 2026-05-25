#include <iostream>
#include "Position.h"
#include "Organism.h"
#include "Grass.h"
#include "Sheep.h"
#include "World.h"

using namespace std;

int main()
{
	// Position 
	Position p1;
	Position p2{ 1, 1 };
	Position p3{ -3, -5 };

	//cout << p1.toString() << endl;
	//cout << p2.toString() << endl;
	//cout << p3.toString() << endl;
	//cout << p1.distance(p2) << endl;
	//p2.move(4, 6);
	//cout << p2.toString() << endl;

	// Organism
	//Organism org1;
	//Organism org2{ 10, p2 };

	//cout << org1.toString() << endl;
	//cout << org2.toString() << endl;
	//org1.move(2, 3);
	//cout << org1.toString() << endl;

	// Plant & Animal
	Grass plant{ p3 };
	Sheep animal{ p2 };
	Grass plant2;
	Sheep animal2;

	cout << plant.toString() << endl;
	cout << animal.toString() << endl;
	cout << plant2.toString() << endl;
	cout << animal2.toString() << endl;
	plant.move(3, 4);
	cout << plant.toString() << endl;
	animal.move(1, 2);
	cout << animal.toString() << endl;
	
	// World test
	World world;
	Position posP1{ 4, 5 }; 
	Position posP2{ 5, 4 }; 

	Position posW2{ 3, 2 }; 
	Position posW3{ 2, 3 }; 
	Position posW4{ 1, 2 }; 
	Position posW5{ 2, 4 }; 
    world.addOrganism(make_unique<Grass>(posP1));
    world.addOrganism(make_unique<Grass>(posP2));
    world.addOrganism(make_unique<Sheep>(posW2));
    world.addOrganism(make_unique<Sheep>(posW3));
	world.addOrganism(make_unique<Sheep>(posW4));
    world.addOrganism(make_unique<Sheep>(posW5));
	auto positions = world.getVectorOfFreePositionsAround(Position(5, 5));

	for(auto pos: positions)
		cout << pos.toString() << endl;

	// Tura 0
	cout << world.toString() << endl;

	// Tura 1
	world.makeTurn();
	cout << world.toString() << endl;

	// Tura 2
	world.makeTurn();
	cout << world.toString() << endl;
 

	// Tura 3
	world.makeTurn();
	cout << world.toString() << endl;

	// powrot do Tury 2 
	cout << world.toString() << endl;
 
	for (size_t i = 0; i < 20; i++)
	{ 
		world.makeTurn();
		cout << world.toString() << endl;
	} 
	return 0;
}
