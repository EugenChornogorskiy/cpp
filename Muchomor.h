#include "Plant.h"
#include "World.h"

class Muchomor : public Plant
{
public:
    Muchomor(Position position, int turn);
    Muchomor(Position position);
    Muchomor();

    virtual ~Muchomor() override;
    virtual void action(World& world) override;
    virtual void reproduce(World& world) override; 
    
};