#pragma once


#include <cstdint>
#include <string>

#include "Menu.h"
#include "MenuToolButton.h"
#include "MenuToolVariable.h"
#include "SimulationDataContainers.h"
#include "MenuToolChoice.h"

#include "Player.h"

class StatModificationMenu : public Menu
{

public:

    StatModificationMenu();

    void init_menu();

    void reset_cursor_color();

    void start() final;
    void update() final;

private:

    void load_player_stats();
    void update_player_stats();

    std::string* cursor_color {};

    MenuSimulationDataContainer msdc;

    MenuToolVariable* name_var;
    MenuToolVariable* max_hitpoints_var;
    MenuToolVariable* max_mana_var;
    MenuToolVariable* defense_var;
    MenuToolVariable* evasion_var;

    MenuToolButton<StatModificationMenu>* save_changes_button {};
    MenuToolButton<StatModificationMenu>* cancel_button {};

    Player* player;
};