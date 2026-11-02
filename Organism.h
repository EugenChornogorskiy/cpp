#pragma once
#include <string>
#include "Position.h"
#include <vector> 
#include <memory>
class World;
using namespace std;

class Organism
{
private:
	int power;
	Position position;
	string species;
    int initiative;
    int liveLength;
    int powerToReproduce; 
    int age = 0; 
    vector<Organism*> children;
	vector<pair<int, int>> ancestorsHistory;
public:
	Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position, int turn);
	Organism();

	Organism(const Organism& other);  
    Organism(Organism&& other) noexcept;  
    Organism& operator=(const Organism& other); 
    Organism& operator=(Organism&& other) noexcept;  

    int getPower() const;
    void setPower(int power);
    int getInitiative() const;
	void setInitiative(int initiative);
    int getLiveLength() const;
	void setLiveLength(int liveLength);
    int getPowerToReproduce() const;
	void setPowerToReproduce(int powerToReproduce); 
    int getAge() const;
	void setAge(int age);
    void incrementAge();
    Position getPosition() const;
    void setPosition(Position position);
    string getSpecies() const;
    void setSpecies(string spec);
 
    void addChild(Organism* org);

    void addAncestor(int birthTurn, int deathTurn);
    vector<pair<int, int>> getAncestorsHistory() const;
    void updateAncestorDeath(int turn,int parentBirth);
    void copyAncestorsFrom(const Organism& parent, int birthTurn);

	string toString();

	virtual void move(int dx, int dy);
    virtual void action(World& world) = 0;
    virtual bool isDead() const;
    virtual bool canReproduce() const;
    virtual void reproduce(World& world) = 0; 

	virtual void serialize(ofstream& file) const;
    virtual void deserialize(ifstream& file); 
	virtual ~Organism() = 0;
};