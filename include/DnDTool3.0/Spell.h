#pragma once

#include <string>
#include <cstdint>

struct Spell
{
    uint16_t mana_cost {};
            
    std::string name;

    std::string description;
};
