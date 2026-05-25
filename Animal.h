#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{ 
	public:
		Position lastPosition; 
		Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position);
		Animal();

		Animal(const Animal& other);
		Animal(Animal&& other) noexcept;
		Animal& operator=(const Animal& other);
		Animal& operator=(Animal&& other) noexcept;
		virtual ~Animal();
		
		Position getLastPosition() const;
		void setLastPosition(Position pos);
		
		virtual void action(World& world) override = 0;
		virtual void onCollision(Organism& other, World& world) override;
		
		virtual void serialize(ofstream& file) const override;
		virtual void deserialize(ifstream& file) override;
};

