#include "ColorString.h"
#include "MenuHandler.h"

#include "SimulationInitMenu.h"
#include "SettingsMenu.h"
#include "EventSystem.h"


// Constructors / Deconstructor 

SimulationInitMenu::SimulationInitMenu(uint16_t start_x, 
    uint16_t start_y, uint16_t end_x, uint16_t end_y) :
    Menu(start_x, start_y, end_x, end_y, "SimulationInit")
{
    CallbackManager::subscribe<SimulationInitMenu>
        ("reset cursor color", this, reset_cursor_color);

    lsdc.content.push_back(ColorString("Create New Player", "White"));
    lsdc.content.push_back(ColorString("Load Player", "White"));
    lsdc.content.push_back(ColorString("Access Database", "White"));
    lsdc.content.push_back(ColorString("Settings", "Orange"));
    lsdc.content.push_back(ColorString("Quit", "Red"));
}


// Public

void SimulationInitMenu::init_menu()
{
    cursor_color = static_cast<SettingsMenu*>(MenuHandler::
        get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();
}

void SimulationInitMenu::reset_cursor_color()
{
    lsdc.cursor_color = *cursor_color;
}

void SimulationInitMenu::start() 
{
    lsdc.cursor_pos = 0;
    lsdc.item_has_been_selected = false;
}

void SimulationInitMenu::update() 
{
    window->add_str("[ Main Menu ]\n\n");

    window->add_str("-- Make a Selection --\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    switch(lsdc.cursor_pos)
    {
        // Create New Player
        case 0:

            // MenuHandler::activate_menu("CreatePlayer");
            return;

        // Load Player
        case 1:
        
            MenuHandler::activate_menu("LoadPlayer");
            return;

        // Access Database
        case 2:

            // MenuHandler::activate_menu("DatabaseOverlay")
            return;

        case 3:

            MenuHandler::activate_menu("Settings");
            return;

        // Quit
        case 4:

            CallbackManager::trigger_callback("quit");
            return;
    }
}


// Private

