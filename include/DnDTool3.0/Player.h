#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <array>

#include "Item.h"
#include "Spell.h"


struct Player
{
    uint16_t hitpoints {};
    uint16_t max_hitpoints {};

    uint16_t defense {};
    uint16_t evasion {};
    uint16_t mana {};
    uint16_t max_mana {};

    std::string save_path;

    std::string name;

    std::vector<std::string> buffs;
    std::vector<std::string> debuffs;
    std::vector<std::string> player_attributes;
    std::vector<Item*> items;
    std::vector<Spell> spells;

    std::array<uint8_t, 14> skills;
}; 