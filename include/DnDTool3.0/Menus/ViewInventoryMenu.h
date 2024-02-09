#pragma once

#include <cstdint>
#include <string>

#include <Menu.h>
#include <SimulationDataContainers.h>
#include<MenuTools.h>

#include "Player.h"


class ViewInventoryMenu : public Menu
{

public:

    ViewInventoryMenu(uint16_t start_x, uint16_t start_y, uint16_t end_x,
        uint16_t end_y);

    void init_menu();

    void reset_cursor_color();

    void handle_keys();

    void start() final;
    void update() final;

private:

    void render_inventory();

    uint16_t inventory_cursor_pos {};

    std::string* cursor_color;

    ListSelectionDataContainer lsdc;

    Player* player = nullptr;
};
