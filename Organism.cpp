#include "Organism.h"
#include <fstream>
#include "World.h"
#include "Sheep.h"
#include "Grass.h"
using namespace std;

Organism::Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position) : power(power), initiative(initiative), liveLength(liveLength),
	powerToReproduce(powerToReproduce), position(position), species("O"), age(0)
{ 
    ancestorsHistory.push_back({0, -1}); 
}

Organism::Organism() : Organism(0, 0, 10, 5, Position(0, 0)) {}

Organism::Organism(const Organism& other) : power(other.power), initiative(other.initiative), liveLength(other.liveLength), powerToReproduce(other.powerToReproduce), 
	age(other.age), position(other.position), species(other.species), ancestorsHistory(other.ancestorsHistory){}

Organism::Organism(Organism&& other) noexcept 
    : power(other.power), initiative(other.initiative), liveLength(other.liveLength), powerToReproduce(other.powerToReproduce), age(other.age), position(std::move(other.position)),
  	species(std::move(other.species)), ancestorsHistory(std::move(other.ancestorsHistory))
{  
    other.power = 0;
    other.initiative = 0;
    other.liveLength = 0; 
    other.powerToReproduce = 0; 
    other.age = 0;  
    other.position = Position(0, 0); 
    other.species.clear(); 
    other.ancestorsHistory.clear();  
}

Organism& Organism::operator=(const Organism& other)
{ 
    if (this != &other) {
        power = other.power;
        initiative = other.initiative;
        liveLength = other.liveLength;
        powerToReproduce = other.powerToReproduce;
        age = other.age;
        position = other.position;
        species = other.species;
        ancestorsHistory = other.ancestorsHistory; 
    }
    return *this;
}
Organism& Organism::operator=(Organism&& other) noexcept
{ 
    if (this != &other) {
        power = other.power;
        initiative = other.initiative;
        liveLength = other.liveLength;
        powerToReproduce = other.powerToReproduce;
        age = other.age;
        position = std::move(other.position);
        species = std::move(other.species);
        ancestorsHistory = std::move(other.ancestorsHistory);
        
		other.power = 0;
		other.initiative = 0;
		other.liveLength = 0; 
		other.powerToReproduce = 0; 
		other.age = 0;  
		other.position = Position(0, 0); 
		other.species.clear(); 
		other.ancestorsHistory.clear();  
    }
    return *this;
} 

Organism::~Organism() {}

int Organism::getPower() const { return power; }
void Organism::setPower(int power) { this->power = max(0, power); }
int Organism::getInitiative() const { return initiative; }
int Organism::getLiveLength() const { return liveLength; }
int Organism::getPowerToReproduce() const { return powerToReproduce; }
int Organism::getAge() const { return age; }
void Organism::setInitiative(int initiative) { this->initiative = initiative; }
void Organism::setLiveLength(int liveLength) { this->liveLength = liveLength; }
void Organism::setPowerToReproduce(int powerToReproduce) { this->powerToReproduce = powerToReproduce; }
void Organism::setAge(int age) { this->age = age; }
void Organism::incrementAge() { age++; }
Position Organism::getPosition() const { return position; }
void Organism::setPosition(Position position) { this->position = position; }
string Organism::getSpecies() const { return species; }
void Organism::setSpecies(string spec) { species = spec; }

void Organism::addAncestor(int birthTurn, int deathTurn)
{
    ancestorsHistory.push_back({birthTurn, deathTurn});
}

vector<pair<int, int>> Organism::getAncestorsHistory() const
{
    return ancestorsHistory;
}

void Organism::updateAncestorDeath(int turn)
{
    if (!ancestorsHistory.empty() && ancestorsHistory.back().second == -1) {
        ancestorsHistory.back().second = turn;
    }
}
bool Organism::isDead() const
{
    return age >= liveLength;
}

bool Organism::canReproduce() const
{
    return power >= powerToReproduce;
}

void Organism::move(int dx, int dy)
{
    position.move(dx, dy);
}

void Organism::action(World& world)
{ 
    power++;
    age++;
}

void Organism::reproduce(World& world)
{ 
    if (canReproduce()) {
        power /= 2;
    }
}

void Organism::onCollision(Organism& other, World& world) {}

string Organism::toString()
{
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + "}";
}
unique_ptr<Organism> Organism::createFromSpecies(const std::string& species) {
    if (species == "S") return std::make_unique<Sheep>(Position(0,0));
    if (species == "G") return std::make_unique<Grass>(Position(0,0)); 
    return nullptr;
}
void Organism::serialize(ofstream& file) const
{ 
    file.write((char*)&power, sizeof(int));
    file.write((char*)&initiative, sizeof(int));
    file.write((char*)&liveLength, sizeof(int));
    file.write((char*)&powerToReproduce, sizeof(int));
    file.write((char*)&age, sizeof(int));
    
    int x = position.getX();
    int y = position.getY();
    file.write((char*)&x, sizeof(int));
    file.write((char*)&y, sizeof(int));
     
    int historySize = ancestorsHistory.size();
    file.write((char*)&historySize, sizeof(int));
    for (const auto& ancestor : ancestorsHistory) {
        file.write((char*)&ancestor.first, sizeof(int));
        file.write((char*)&ancestor.second, sizeof(int));
    }
}
void Organism::deserialize(ifstream& file)
{
    file.read((char*)&power, sizeof(int));
    file.read((char*)&initiative, sizeof(int));
    file.read((char*)&liveLength, sizeof(int));
    file.read((char*)&powerToReproduce, sizeof(int));
    file.read((char*)&age, sizeof(int));
    
    int x, y;
    file.read((char*)&x, sizeof(int));
    file.read((char*)&y, sizeof(int));
    position = Position(x, y);
    
    int historySize;
    file.read((char*)&historySize, sizeof(int));
    ancestorsHistory.clear();
    for (int i = 0; i < historySize; i++) {
        int birth, death;
        file.read((char*)&birth, sizeof(int));
        file.read((char*)&death, sizeof(int));
        ancestorsHistory.push_back({birth, death});
    }
}