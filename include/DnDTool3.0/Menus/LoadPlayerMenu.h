#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include "Menu.h"
#include "SimulationDataContainers.h"

#include "PlayerHandler.h"
#include "Player.h"


class LoadPlayerMenu : public Menu
{

public:

    LoadPlayerMenu(uint16_t start_x, uint16_t start_y, uint16_t end_x,
        uint16_t end_y);

    void init_menu();

    void reset_cursor_color();

    void start() override;
    void update() override;

    void set_player_handler(PlayerHandler* player_handler);

private:

    bool player_saves_found = false;

    std::string* cursor_color;

    std::unordered_map<std::string, std::string> file_names_to_paths;

    ListSelectionDataContainer lsdc;

    Player* player {};

    PlayerHandler* player_handler {};
};
