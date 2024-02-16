#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "Player.h"

class PlayerHandler
{

public:

    // Delete the default constructor as the saves_directory parameter
    // is required for object creation
    PlayerHandler() = delete;
    PlayerHandler(std::string saves_directory);

    void save_player(Player* p);

    const std::vector<std::string>* get_player_saves();

    Player* load_player(std::string save_file_path);

private:

    void find_player_saves(std::string saves_directory);

    std::string saves_directory;

    std::string active_player_name;

    std::vector<std::string> known_save_paths;
};