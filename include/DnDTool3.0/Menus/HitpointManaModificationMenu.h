#pragma once

#include <cstdint>
#include <string>

#include <Menu.h>
#include <MenuToolButton.h>
#include <MenuToolVariable.h>
#include <SimulationDataContainers.h>
#include <MenuToolChoice.h>

#include "Player.h"

class HitpointManaModificationMenu : public Menu
{

public:

    HitpointManaModificationMenu(uint16_t start_x, uint16_t start_y, 
        uint16_t end_x, uint16_t end_y);

    void init_menu();

    void reset_cursor_color();

    void start() final;
    void update() final;

private:

    void handle_increment();
    void handle_decrement();

    std::string* cursor_color;

    MenuSimulationDataContainer msdc;

    MenuToolButton* increase_hitpoints_button;
    MenuToolButton* decrease_hitpoints_button;
    MenuToolButton* back_button;
    MenuToolVariable* delta_amount;
    MenuToolChoice* modification_choice;

    Player* player;

};

