#pragma once
#include "Organism.h"

class Plant : public Organism
{
	public:
		Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position,int turn);
		Plant();
		
		virtual ~Plant() = 0;
		
		virtual void move(int dx, int dy) override final;  
		virtual void action(World& world) override = 0;
		virtual void onCollision(Organism& other, World& world);
};

