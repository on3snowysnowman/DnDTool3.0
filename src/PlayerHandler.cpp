#include <filesystem>

#include <Debug.h>

#include "PlayerHandler.h"
#include "JsonLoader.h"


// Constructors / Deconstructor

PlayerHandler::PlayerHandler(std::string _saves_directory) 
{
    saves_directory = _saves_directory;

    find_player_saves(_saves_directory);
}


// Public

void PlayerHandler::save_player(Player* p)
{
    Json player_save;

    player_save["Name"] = p->name;
    player_save["Hitpoints"] = p->hitpoints;
    player_save["Max Hitpoints"] = p->max_hitpoints;
    player_save["Defense"] = p->defense;
    player_save["Evasion"] = p->evasion;
    player_save["Mana"] = p->mana;
    player_save["Max Mana"] = p->max_mana;

    // Save player to a new file
    if(active_player_name.size() == 0)
    {
        std::string player_save_directory = saves_directory + "/" + p->name
            + ".json";

        Debug::log("Saving player: " + p->name + " to directory : " + 
            player_save_directory);

        JsonLoader::dump(player_save, player_save_directory.c_str());
    }
    
}

const std::vector<std::string>* PlayerHandler::get_player_saves() 
{ return &known_save_paths; }

Player* PlayerHandler::load_player(std::string save_path) 
{
    Json player_save = JsonLoader::get(save_path.c_str());

    Player* new_p = new Player;

    new_p->name = player_save.at("Name");

    Debug::log("Loading player: " + new_p->name);

    new_p->hitpoints = player_save.at("Hitpoints");
    new_p->max_hitpoints = player_save.at("Max Hitpoints");
    new_p->defense = player_save.at("Defense");
    new_p->evasion = player_save.at("Evasion");
    new_p->mana = player_save.at("Mana");
    new_p->max_mana = player_save.at("Max Mana");

    return new_p;
}

// Private

void PlayerHandler::find_player_saves(std::string saves_directory)
{
    Debug::log("Searching for player saves...");

    // Couldn't find directory
    if(!Debug::does_directory_exist(saves_directory.c_str()))
    {
        std::string message = "PlayerHandler.find_player_saves(std::string "
            "saves_directory) where 'saves_directory' is " + saves_directory 
            + ": couldn't find directory.";

        Debug::log(message, Debug::ERR);
        exit(1);
    }

    std::string save_path;
    Json player_save;

    // Iterate through each save in this directory
    for(const auto& save : 
        std::filesystem::directory_iterator(saves_directory))
    {
        // Add this path to the vector of known save paths
        known_save_paths.push_back(save.path().string());
    }

    if(known_save_paths.size() == 0)
    {
        Debug::log("No player saves found");
        return;
    }

    Debug::log(std::to_string(known_save_paths.size()) + 
        " save(s) found.");
}

