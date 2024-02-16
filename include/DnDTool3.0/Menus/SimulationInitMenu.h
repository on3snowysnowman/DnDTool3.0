#pragma once

#include <cstdint>
#include <string>

#include "Menu.h"
#include "SimulationDataContainers.h"


class SimulationInitMenu : public Menu
{

public:

    SimulationInitMenu(uint16_t start_x, uint16_t start_y, uint16_t end_x,
        uint16_t end_y);

    void init_menu();

    void reset_cursor_color();

    void start() override;
    void update() override;

private:

    std::string* cursor_color;

    ListSelectionDataContainer lsdc;
};
