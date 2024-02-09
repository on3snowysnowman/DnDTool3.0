

#include "MenuHandler.h"
#include "LMath.h"
#include "ColorString.h"
#include "EventSystem.h"

#include "HitpointManaModificationMenu.h"
#include "MenuHandler.h"
#include "MainSimMenu.h"
#include "SettingsMenu.h"


// Constructors / Deconstructor

HitpointManaModificationMenu::HitpointManaModificationMenu(uint16_t start_x, 
    uint16_t start_y, uint16_t end_x, uint16_t end_y) : 
    Menu(start_x, start_y, end_x, end_y, "HitpointManaModification")
{
    CallbackManager::subscribe<HitpointManaModificationMenu>
        ("reset cursor color", this, reset_cursor_color);

    increase_hitpoints_button = new MenuToolButton(window, "Increment", "Blue", 
        "Green");

    decrease_hitpoints_button = new MenuToolButton(window, "Decrement", "Blue",
        "Red");

    back_button = new MenuToolButton(window, "Back", "Blue", "Red");

    delta_amount = new MenuToolVariable(window, MenuToolItem::INT, 
        "Blue", "Amount to Change", "1");

    modification_choice = new MenuToolChoice(window, "Blue", "What to Modify", 0);
    modification_choice->choices.push_back(ColorString("Hitpoints", "Green"));
    modification_choice->choices.push_back(ColorString("Mana", "Blue"));

    msdc.content.push_back(modification_choice);
    msdc.content.push_back(delta_amount);
    msdc.content.push_back(increase_hitpoints_button);
    msdc.content.push_back(decrease_hitpoints_button);
    msdc.content.push_back(back_button);

    msdc.block_enter_key = false;

    player = static_cast<MainSimMenu*>(
        MenuHandler::get_menu("MainSim"))->get_player();
}


// Public

void HitpointManaModificationMenu::init_menu()
{
    cursor_color = static_cast<SettingsMenu*>(
        MenuHandler::get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();
}

void HitpointManaModificationMenu::reset_cursor_color()
{
    increase_hitpoints_button->set_cursor_color(*cursor_color);
    decrease_hitpoints_button->set_cursor_color(*cursor_color);
    back_button->set_cursor_color(*cursor_color);
    delta_amount->set_cursor_color(*cursor_color);
    modification_choice->set_cursor_color(*cursor_color);
}

void HitpointManaModificationMenu::start() 
{
    msdc.cursor_pos = 0;
    msdc.selected_pos = -1;
}

void HitpointManaModificationMenu::update() 
{
    window->add_str("[ Main Menu / Modify Hitpoints & Mana ]\n\n");

    window->add_str("Hitpoints: ", "LightGray");
    menu_tools->render_multi_colored_meter(player->hitpoints, 0, 
        player->max_hitpoints);
    window->add_str("\nMana: ", "LightGray");
    menu_tools->render_single_color_meter(player->mana, 0, 
        player->max_mana, "Blue");

    window->add_str("\n\n-- Make a Selection --\n\n");

    menu_tools->simulate_menu(msdc);

    if(msdc.selected_pos == -1) return;

    switch(msdc.selected_pos)
    {
        // Increment
        case 2:
            
            handle_increment();
            input_handler->set_delay(SDLK_RETURN, 8);
            break;

        // Decrement 
        case 3:

            handle_decrement();
            input_handler->set_delay(SDLK_RETURN, 8);
            break;

        // Back
        case 4:

            input_handler->block_key_until_released(SDLK_RETURN);
            MenuHandler::deactivate_menu(this);
            return;
    }
}


// Private

#include <iostream>

void HitpointManaModificationMenu::handle_increment()
{
    uint16_t increment_amount = delta_amount->fetch_int();

    // Check if mana or hitpoints has been selected for modification
    switch(modification_choice->choice_index)
    {
        // Hitpoints
        case 0:

            player->hitpoints = LMath::handle_uint16_addition(
                player->hitpoints, increment_amount);

            // Round the hitpoints to the max hitpoints if it exceeds it
            player->hitpoints = LMath::round_num_to_maximum(player->hitpoints,
                player->max_hitpoints);
            return;

        // Mana
        case 1:

            player->mana = LMath::handle_uint16_addition(
                player->mana, increment_amount);

            // Round the hitpoints to the max hitpoints if it exceeds it
            player->mana = LMath::round_num_to_maximum(player->mana,
                player->max_mana);
            return;
    }
}

void HitpointManaModificationMenu::handle_decrement()
{
    uint16_t increment_amount = delta_amount->fetch_int();

    // Check if mana or hitpoints has been selected for modification
    switch(modification_choice->choice_index)
    {

        // Hitpoints
        case 0:

            if(player->hitpoints - increment_amount < 0) 
            {
                player->hitpoints = 0;
                return;
            }
            

            player->hitpoints -= increment_amount;
            return;

        // Mana
        case 1:

            if(player->mana - increment_amount < 0) 
            {
                player->mana = 0;
                return;
            }

            player->mana -= increment_amount;
            return;
    }
}
