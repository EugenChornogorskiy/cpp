#include "World.h"
#include <fstream>
#include "OrganismFactory.h" 
#include "Organism.h" 
#include <algorithm>
#include <iostream>

string World::getOrganismFromPosition(int x, int y)
{	
	for (const auto& org : organisms)
		if (org->getPosition().getX() == x && org->getPosition().getY() == y)
			return org->getSpecies();
	return "";
}

bool World::isPositionOnWorld(int x, int y)
{
	return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
	return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

vector<Position> World::getVectorOfFreePositionsAround(Position position)
{	
	int pos_x = position.getX(), pos_y = position.getY();
	vector<Position> result;
	for(int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			if ((x != 0 || y != 0) && 
				isPositionOnWorld(pos_x + x, pos_y + y)) {
				result.push_back(Position(pos_x + x, pos_y + y));
			}
	auto iter = remove_if(result.begin(), result.end(),
		[this](Position pos) {return !isPositionFree(pos); });
	result.erase(iter, result.end());

	return result;
}

vector<Position> World::getVectorOfPositionsAround(Position position)
{	
	int pos_x = position.getX(), pos_y = position.getY();
	vector<Position> result;
	for(int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			if ((x != 0 || y != 0) && 
				isPositionOnWorld(pos_x + x, pos_y + y)) {
				result.push_back(Position(pos_x + x, pos_y + y));
			} 

	return result;
}

World::World(int worldX, int worldY)
{
	setWorldX(worldX);
	setWorldY(worldY);
}

int World::getWorldX()
{
	return this->worldX;
}

void World::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int World::getWorldY()
{
	return this->worldY;
}

void World::setWorldY(int worldY)
{
	this->worldY = worldY;
}

int World::getTurn() const
{
	return this->turn;
}

void World::addOrganism(unique_ptr<Organism> organism)
{
	this->organisms.push_back(std::move(organism));
}

Organism* World::getOrganismAt(Position position)
{
    for (const auto& org : organisms) {
        if (org->getPosition().getX() == position.getX() &&
            org->getPosition().getY() == position.getY()) {
            return org.get();
        }
    }
    return nullptr;
}

void World::removeOrganism(Organism* organism)
{
    for (auto it = organisms.begin(); it != organisms.end(); ++it) {
        if ((*it)->getPosition().getX() == organism->getPosition().getX() &&
            (*it)->getPosition().getY() == organism->getPosition().getY()) {
            organisms.erase(it);
            break;
        }
    }
}

void World::makeTurn()
{
    sort(organisms.begin(), organisms.end(),
        [](const unique_ptr<Organism>& a, const unique_ptr<Organism>& b) {
            return a->getInitiative() > b->getInitiative();
        });
     
    vector<Organism*> copy;
    for (auto& org : organisms) {
        copy.push_back(org.get());
    }

    for (auto* org : copy) {
        if (org && org->isDead()) {
            org->updateAncestorDeath(turn,turn-org->getAge()); 
            org->toString();
        }
    }

    for (auto* org : copy) {
        if (org && !org->isDead()) {
            org->action(*this);
        }
    }
     
    organisms.erase(
        remove_if(organisms.begin(), organisms.end(),
            [](const unique_ptr<Organism>& org) { return org->isDead(); }),
        organisms.end()
    );
    
    turn++;
}


void World::writeWorld(string fileName)
{
    ofstream file(fileName, ios::binary);
    if (!file.is_open()) return;
    
    file.write((char*)&worldX, sizeof(int));
    file.write((char*)&worldY, sizeof(int));
    file.write((char*)&turn, sizeof(int));
    
    int size = organisms.size();
    file.write((char*)&size, sizeof(int));
    
    for (auto& org : organisms) { 
        string species = org->getSpecies();
        int len = species.length();
        file.write((char*)&len, sizeof(int));
        file.write(species.c_str(), len);
         
        org->serialize(file);
    }
    
    file.close();
}

void World::readWorld(string fileName)
{
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cerr << "Nie mozna otworzyc pliku: " << fileName << endl;
        return;
    }
    
    file.read((char*)&worldX, sizeof(int));
    file.read((char*)&worldY, sizeof(int));
    file.read((char*)&turn, sizeof(int));
    
    int size;
    file.read((char*)&size, sizeof(int));
    
    organisms.clear();
    
    for (int i = 0; i < size; i++) { 
        int len;
        file.read((char*)&len, sizeof(int));
        string species;
        species.resize(len);
        file.read(&species[0], len);
          
        auto org = OrganismFactory::create(species);
        
        if (org) { 
            org->deserialize(file);
            organisms.push_back(std::move(org));
        }
    }
    
    file.close();
}


string World::toString()
{
	string result = "";
	string spec;

	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
			spec = getOrganismFromPosition(wX, wY);
			if (spec != "")
				result += spec;
			else
				result += separator;
		};
		result += "\n";
	}
	return result;
}

