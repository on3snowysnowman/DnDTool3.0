#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Menu.h"
#include "SimulationDataContainers.h"
#include "MenuToolChoice.h"
#include "MenuToolButton.h"


class SettingsMenu : public Menu
{

public:

    SettingsMenu(uint16_t start_x, uint16_t end_x, uint16_t start_y, 
        uint16_t end_y);

    void reset_cursor_color();

    void start() final;
    void update() final;

    std::string* get_cursor_color();

private:

    void update_cursor_color();
    void exit_menu();

    uint8_t cursor_color_index {};

    std::string cursor_color = "Blue";

    MenuSimulationDataContainer msdc;

    MenuToolButton<SettingsMenu>* apply_button;
    MenuToolButton<SettingsMenu>* cancel_button;
    MenuToolChoice* cursor_color_choice;
};
