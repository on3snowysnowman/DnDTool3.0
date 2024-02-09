#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "Item.h"


struct Player
{
    uint16_t hitpoints {};
    uint16_t max_hitpoints {};

    uint16_t defense {};
    uint16_t evasion {};
    uint16_t mana {};
    uint16_t max_mana {};

    std::string name;

    std::vector<Item*> items;
    std::vector<std::string> buffs;
    std::vector<std::string> debuffs;
};