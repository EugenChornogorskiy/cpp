#pragma once

#include <vector>
#include <ctime>
#include "Organism.h"
#include <memory>
class Organism;
using namespace std;

class World
{
private:
	int worldX;
	int worldY;
	int turn = 0;
	vector<unique_ptr<Organism>> organisms;
	char separator = '.';

	string getOrganismFromPosition(int x, int y);
	bool isPositionOnWorld(int x, int y);
	bool isPositionFree(Position position);

public:
	World(int worldX, int worldY);
	World() : World(6, 6) {};

	World(const World&) = delete;
    World& operator=(const World&) = delete;
    World(World&&) = default;
    World& operator=(World&&) = default;

	
	int getWorldX();
	void setWorldX(int worldX);
	int getWorldY();
	void setWorldY(int worldY);
	int getTurn() const; 
	 
    void addOrganism(unique_ptr<Organism> organism);
    void removeOrganism(Organism* organism);
    Organism* getOrganismAt(Position position);
    vector<Position> getVectorOfFreePositionsAround(Position position);
	void makeTurn();

	void writeWorld(string fileName);
	void readWorld(string fileName);
	
	string toString();

};

