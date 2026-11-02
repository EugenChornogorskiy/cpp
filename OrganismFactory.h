#pragma once
#include <memory>
#include <string>
#include "Organism.h"
#include "Sheep.h"
#include "Grass.h"
#include "Wilk.h"
#include "Muchomor.h"
#include "Mlecz.h"

class OrganismFactory {
public:
    static std::unique_ptr<Organism> create(const std::string& species) {
        if (species == "S") return std::make_unique<Sheep>(Position(0,0));
        if (species == "G") return std::make_unique<Grass>(Position(0,0));
        if (species == "W") return std::make_unique<Wilk>(Position(0,0));
        if (species == "D") return std::make_unique<Mlecz>(Position(0,0));
        if (species == "T") return std::make_unique<Muchomor>(Position(0,0));
        return nullptr;
    }
};