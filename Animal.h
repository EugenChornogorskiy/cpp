#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{ 
	private:
		Position lastPosition; 
	public:
		
		Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position,int turn);
		Animal();

		Animal(const Animal& other);
		Animal(Animal&& other) noexcept;
		Animal& operator=(const Animal& other);
		Animal& operator=(Animal&& other) noexcept;
		virtual ~Animal();
		
		Position getLastPosition() const;
		void setLastPosition(Position pos);
		
		virtual void action(World& world) override = 0;
		virtual void onCollision(Organism& other, World& world);
		virtual void reproduce(World& world) override = 0; 
		
		virtual void serialize(ofstream& file) const override;
		virtual void deserialize(ifstream& file) override;
};

