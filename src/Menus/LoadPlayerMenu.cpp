#include <vector>

#include "ColorString.h"
#include "MenuHandler.h"
#include "EventSystem.h"
#include "LStringManip.h"

#include "LoadPlayerMenu.h"
#include "SettingsMenu.h"
#include "MainSimMenu.h"
#include "Simulator.h"


// Constructors / Deconstructor

LoadPlayerMenu::LoadPlayerMenu(uint16_t start_x, uint16_t start_y, 
    uint16_t end_x, uint16_t end_y) : 
    Menu(start_x, start_y, end_x, end_y, "LoadPlayer")
{
    CallbackManager::subscribe<LoadPlayerMenu>
        ("reset cursor color", this, reset_cursor_color);

    player = Simulator::get_player();
}


// Public

void LoadPlayerMenu::init_menu() 
{
    cursor_color = static_cast<SettingsMenu*>(MenuHandler::
        get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();

    const std::vector<std::string>* player_saves = 
        player_handler->get_player_saves();

    if(player_saves->size() > 0)
    {
        player_saves_found = true;

        for(std::string _str : *player_saves)
        {
            std::string file_name = 
                LStringManip::get_str_after_char(_str, '\\');

            file_names_to_paths[file_name] = _str;

            lsdc.content.push_back(ColorString(file_name, "White"));
        }
    }

    lsdc.content.push_back(ColorString("Back", "Red"));
}

void LoadPlayerMenu::reset_cursor_color() 
{
    lsdc.cursor_color = *cursor_color;
}

void LoadPlayerMenu::start() 
{
    lsdc.cursor_pos = 0;
    lsdc.item_has_been_selected = false;
}

void LoadPlayerMenu::update() 
{
    window->add_str("[ Main Menu / Load Player ]\n\n");

    if(!player_saves_found)
        window->add_str("No player saves found\n\n", "Red");

    window->add_str("-- Make a Selection --\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    std::string* selected_item = 
        &lsdc.content.at(lsdc.cursor_pos).content;

    if(!player_saves_found || *selected_item == "Back")
    {
        MenuHandler::deactivate_menu(this);
        return;
    }

    Player* loaded_player = player_handler->load_player(
        file_names_to_paths.at(*selected_item));

    *player = *loaded_player;

    delete loaded_player;

    MenuHandler::activate_menu("MainSim");
    MenuHandler::deactivate_menu(this);
}

void LoadPlayerMenu::set_player_handler(PlayerHandler* _player_handler)
{ player_handler = _player_handler; }


// Private
