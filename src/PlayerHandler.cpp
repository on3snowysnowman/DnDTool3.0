#include <filesystem>
#include <iostream>

#include "Debug.h"

#include "PlayerHandler.h"
#include "Item.h"
#include "LRandom.h"
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

    // Save player attributes
    player_save["Name"] = p->name;
    player_save["Hitpoints"] = p->hitpoints;
    player_save["Max Hitpoints"] = p->max_hitpoints;
    player_save["Defense"] = p->defense;
    player_save["Evasion"] = p->evasion;
    player_save["Mana"] = p->mana;
    player_save["Max Mana"] = p->max_mana;

    Json skills;

    // Iterate over skills
    for(uint8_t skill : p->skills)
    {
        skills.push_back(skill);
    }

    player_save["skills"] = skills;

    Json p_items = Json::array(); // Json List of items to be saved
    Json item_instance; // Json Obj for each individual item
    Json item_attributes; // Json List of attributes for each item

    // Iterate over items
    for(Item* i : p->items)
    {
        item_instance.clear();
        item_attributes.clear();

        // Emplace the item name
        item_instance["Name"] = i->name;

        // Iterate through the attributes of this item
        for(std::string attrib : i->attributes)
        {
            // Emplace this attribute
            item_attributes.push_back(attrib);
        }

        // Emplace the item attributes
        item_instance["Attributes"] = item_attributes;

        // Add this item to the list of items to be saved
        p_items.push_back(item_instance);
    }

    // Save player items
    player_save["Items"] = p_items;

    std::string player_save_directory = p->save_path;

    // Save player to a new file
    if(player_save_directory.size() == 0)
    {
        std::string player_save_directory = saves_directory + "\\" + p->name
            + ".json";

    }

    Debug::log("Saving player: " + p->name + " to directory : " + 
            player_save_directory);

    JsonLoader::dump(player_save, player_save_directory.c_str());
}

const std::vector<std::string>* PlayerHandler::get_player_saves() 
{ return &known_save_paths; }

Player* PlayerHandler::load_player(std::string save_file_path) 
{
    Json player_save = JsonLoader::get(save_file_path.c_str());

    Player* new_p = new Player;

    new_p->save_path = save_file_path;

    new_p->name = player_save.at("Name");

    Debug::log("Loading player: " + new_p->name);

    // Load normal attributes
    new_p->hitpoints = player_save.at("Hitpoints");
    new_p->max_hitpoints = player_save.at("Max Hitpoints");
    new_p->defense = player_save.at("Defense");
    new_p->evasion = player_save.at("Evasion");
    new_p->mana = player_save.at("Mana");
    new_p->max_mana = player_save.at("Max Mana");

    uint8_t count = 0;

    Json skills = player_save["skills"];

    // Load skills
    while(count < skills.size())
    {
        new_p->skills.at(count) = skills.at(count);
        ++count;
    }

    Json::iterator start_it = player_save.at("Items").begin();
    Json::iterator end_it = player_save.at("Items").end();

    // Load items
    while(start_it != end_it)
    {
        Item* i = new Item;

        i->name = start_it->at("Name");

        for(std::string attrib : start_it->at("Attributes"))
        {
            i->attributes.push_back(attrib);
        }

        new_p->items.push_back(i);

        ++start_it;
    }

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

