#include <ColorString.h>
#include <EventSystem.h>
#include <MenuHandler.h>
#include <EventSystem.h>
#include <iostream>

#include "MainSimMenu.h"
#include "SettingsMenu.h"
#include "MenuHandler.h"


// Constructors / Deconstructor

MainSimMenu::MainSimMenu(uint16_t start_x, uint16_t start_y, uint16_t end_x, 
    uint16_t end_y, Player* p) : Menu(start_x, start_y, end_x, end_y, 
    "MainSim") 
{
    CallbackManager::subscribe<MainSimMenu>
        ("reset cursor color", this, reset_cursor_color);

    lsdc.content = std::vector<ColorString> {
        ColorString("Modify Hitpoints & Mana","White"),
        ColorString("View Stats Overlay", "White"), 
        ColorString("Inventory", "White"), 
        ColorString("Settings", "Orange"), 
        ColorString("Quit", "Red")};

    player = p;
}


// Public

void MainSimMenu::init_menu()
{
    cursor_color = static_cast<SettingsMenu*>(MenuHandler::
        get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();
}

void MainSimMenu::reset_cursor_color()
{
    lsdc.cursor_color = *cursor_color;
}

void MainSimMenu::start() {}

void MainSimMenu::update() 
{
    window->add_str("[ Main Menu ]\n\n");

    render_quick_stats();

    window->add_str("-- Make a Selection --\n\n");

    menu_tools->simulate_list_selection(lsdc);

    // Nothing has been selected
    if(lsdc.item_has_been_selected == false) return;

    lsdc.item_has_been_selected = false;

    // A list item has been selected

    std::string selected_item = lsdc.content.at(lsdc.cursor_pos).content;

    if(selected_item == "Modify Hitpoints & Mana") 
        MenuHandler::activate_menu("HitpointManaModification");

    else if(selected_item == "View Stats Overlay")
        MenuHandler::activate_menu("StatsOverlay");

    else if(selected_item == "Inventory")
        MenuHandler::activate_menu("ViewInventory");

    else if(selected_item == "Settings")
        MenuHandler::activate_menu("Settings");

    else if(selected_item == "Quit") CallbackManager::trigger_callback("quit");
}

Player* MainSimMenu::get_player() const { return player; }


// Private

void MainSimMenu::render_quick_stats()
{
    window->add_str(player->name, "LightGray");
    window->add_str("\n\nHitpoints: ", "LightGray");
    menu_tools->render_multi_colored_meter(player->hitpoints, 0, 
        player->max_hitpoints);
    window->add_str("\nMana: ", "LightGray");
    menu_tools->render_single_color_meter(player->mana, 0, player->max_mana,
        "Blue");
    window->add_str("\nDefense: ", "LightGray");
    menu_tools->render_colored_number(player->defense, 5, 15);
    window->add_str("\nEvasion: ", "LightGray");
    menu_tools->render_colored_number(player->evasion, 5, 15);
    window->add_new_line(2);
}
