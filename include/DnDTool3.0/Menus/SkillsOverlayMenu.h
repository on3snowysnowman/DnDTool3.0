#pragma once

#include <cstdint>
#include <string>

#include "Menu.h"
#include "SimulationDataContainers.h"
#include "SpriteHandler.h"

#include "Player.h"

class SkillsOverlayMenu : public Menu
{

public:

    SkillsOverlayMenu(uint16_t start_x, uint16_t start_y, uint16_t end_x,
        uint16_t end_y);

    void init_menu();

    void reset_cursor_color();

    void start() final;
    void update() final;

private:

    void render_skills();

    std::string* cursor_color {};

    ListSelectionDataContainer lsdc;
    
    Sprite* alchemy_sprite {};
    Sprite* anim_han_sprite {};
    Sprite* appraising_sprite {};
    Sprite* arcanary_sprite {};
    Sprite* athletics_sprite {};
    Sprite* cooking_sprite {};
    Sprite* crafting_sprite {};
    Sprite* intel_sprite {};
    Sprite* medicine_sprite {};
    Sprite* percep_sprite {};
    Sprite* speech_sprite {};
    Sprite* stealth_sprite {};
    Sprite* strength_sprite {};
    Sprite* survival_sprite {};
    Sprite* thiev_sprite {};

    Player* player;
};