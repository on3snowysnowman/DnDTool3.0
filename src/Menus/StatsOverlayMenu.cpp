#include <ColorString.h>
#include <MenuHandler.h>
#include <EventSystem.h>

#include "StatsOverlayMenu.h"
#include "MainSimMenu.h"
#include "SettingsMenu.h"
#include "MenuHandler.h"


// Constructors / Deconstructor 

StatsOverlayMenu::StatsOverlayMenu(uint16_t start_x, uint16_t start_y, 
    uint16_t end_x, uint16_t end_y) :
    Menu(start_x, start_y, end_x, end_y, "StatsOverlay")
{
    CallbackManager::subscribe<StatsOverlayMenu>
        ("reset cursor color", this, reset_cursor_color);

    lsdc.cursor_color = "Blue";

    lsdc.content = std::vector<ColorString> {
        ColorString("Modify Stats", "White"),
        ColorString("Back", "Red")
    };

    player = static_cast<MainSimMenu*>(
        MenuHandler::get_menu("MainSim"))->get_player();
}


// Public

void StatsOverlayMenu::init_menu()
{
    cursor_color = static_cast<SettingsMenu*>(
        MenuHandler::get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();
}

void StatsOverlayMenu::reset_cursor_color()
{
    lsdc.cursor_color = *cursor_color;
}

void StatsOverlayMenu::start() 
{
    lsdc.cursor_pos = 0;
}

void StatsOverlayMenu::update()
{
    window->add_str("[ Main Menu / Stats Overlay ]\n\n");

    render_stats();

    window->add_str("\n\n-- Make a Selection --\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    std::string selected_item = lsdc.content.at(lsdc.cursor_pos).content;

    if(selected_item == "Modify Stats")
    {
        return ;
    }

    // Selected item == "Back"

    MenuHandler::deactivate_menu(this);
}


// Private

void StatsOverlayMenu::render_stats()
{
    window->add_str("Name: ", "DarkGray");
    window->add_str(player->name + "\n");
    window->add_str("Hitpoints: ", "DarkGray");
    window->add_str(std::to_string(player->hitpoints) + " / " + 
        std::to_string(player->max_hitpoints) + '\n');
    window->add_str("Mana: ", "DarkGray");
    window->add_str(std::to_string(player->mana) + " / " + 
        std::to_string(player->max_mana) + '\n');
    window->add_str("Defense: ", "DarkGray");
    window->add_str(std::to_string(player->defense) + '\n');
    window->add_str("Evasion: ", "DarkGray");
    window->add_str(std::to_string(player->evasion) + '\n');
}
