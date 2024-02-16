#pragma once


#include <cstdint>
#include <string>

#include "Menu.h"
#include "MenuToolButton.h"
#include "MenuToolVariable.h"
#include "SimulationDataContainers.h"
#include "MenuToolChoice.h"

#include "Player.h"

class SkillModificationMenu : public Menu
{

public:

    SkillModificationMenu();

    void init_menu();

    void reset_cursor_color();

    void start() final;
    void update() final;

private:

    void update_player_skills();

    void load_player_skills();
    void randomize_skills();

    std::string* cursor_color;

    MenuSimulationDataContainer msdc;

    MenuToolVariable* alchemy_skill {};
    MenuToolVariable* anim_han_skill {};
    MenuToolVariable* appraising_skill {};
    MenuToolVariable* arcanary_skill {};
    MenuToolVariable* athletics_skill {};
    MenuToolVariable* cooking_skill {};
    MenuToolVariable* intelligence_skill {};
    MenuToolVariable* medicine_skill {};
    MenuToolVariable* perception_skill {};
    MenuToolVariable* speech_skill {};
    MenuToolVariable* stealth_skill {};
    MenuToolVariable* strength_skill {};
    MenuToolVariable* survival_skill {};
    MenuToolVariable* sl_of_hand_skill {};

    MenuToolButton<SkillModificationMenu>* randomize_skill_button {};
    MenuToolButton<SkillModificationMenu>* save_changes_button {};
    MenuToolButton<SkillModificationMenu>* cancel_button {};

    Player* player;
};