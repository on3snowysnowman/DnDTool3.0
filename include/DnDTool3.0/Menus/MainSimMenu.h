#pragma once

#include <cstdint>
#include <string>

#include "Menu.h"
#include "SimulationDataContainers.h"

#include "Player.h"


class MainSimMenu : public Menu
{

public:

    MainSimMenu(uint16_t start_x, uint16_t start_y, uint16_t end_x, 
        uint16_t end_y);

    void init_menu();

    void reset_cursor_color();

    void start() final;
    void update() final;

private:

    void render_quick_stats();

    std::string* cursor_color;

    ListSelectionDataContainer lsdc;

    Player* player {};

};

