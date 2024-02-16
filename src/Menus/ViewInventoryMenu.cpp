#include "ColorString.h"

#include "ViewInventoryMenu.h"
#include "MainSimMenu.h"
#include "SettingsMenu.h"
#include "MenuHandler.h"
#include "Item.h"
#include "Simulator.h"


// Constructors / Deconstructors

ViewInventoryMenu::ViewInventoryMenu(uint16_t start_x, uint16_t start_y, 
    uint16_t end_x, uint16_t end_y) : 
    Menu(start_x, start_y, end_x, end_y, "ViewInventory") 
{
    lsdc.content.push_back(ColorString("Modify Hovered Item", "White"));
    lsdc.content.push_back(ColorString("Back", "Red"));

    player = Simulator::get_player();
}


// Public

void ViewInventoryMenu::init_menu()
{
    cursor_color = static_cast<SettingsMenu*>(
        MenuHandler::get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();
}

void ViewInventoryMenu::reset_cursor_color()
{
    lsdc.cursor_color = *cursor_color;
}

void ViewInventoryMenu::handle_keys()
{
    bool shift_pressed = input_handler->is_key_pressed(SDLK_LSHIFT)
        || input_handler->is_key_pressed(SDLK_RSHIFT);

    // If Up Arrow is pressed
    if(input_handler->is_key_pressed_and_available(SDLK_UP))
    {
        input_handler->set_delay(SDLK_UP, 8);

        if(shift_pressed)
        {
            inventory_cursor_pos = 0;
        }

        else
        {
            // Decrease the cursor position by 1 if it is greater than 0
            inventory_cursor_pos != 0 ? --inventory_cursor_pos : 0;
        }

        
    }

    // If Down Arrow is pressed
    else if(input_handler->is_key_pressed_and_available(SDLK_DOWN))
    {
        input_handler->set_delay(SDLK_DOWN, 8);

        if(shift_pressed)
        {
            inventory_cursor_pos = player->items.size() - 1;
        }

        else
        {
            // Increment the cursor position by 1 if it is less than the player's 
            // inventory size
            inventory_cursor_pos != player->items.size() - 1 ? 
                ++inventory_cursor_pos : 0;
        }
    }
}

void ViewInventoryMenu::start()
{
    lsdc.cursor_pos = 0;
    lsdc.item_has_been_selected = false;
}

void ViewInventoryMenu::update()
{
    handle_keys();
    render_inventory();

    window->add_str("[ Player Menu / Inventory ]\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    switch(lsdc.cursor_pos)
    {
        // Modify Hovered Item
        case 0:

            return;

        // Back
        case 1:

            MenuHandler::deactivate_menu(this);
            return;
    }
}


// Private

void ViewInventoryMenu::render_inventory()
{
    window->set_cursor_position(55, 0);
    window->set_anchor(55);

    window->add_str("Inventory:\n\n");

    Item* item {};

    for(uint16_t i = 0; i < player->items.size(); ++i)
    {
        item = player->items.at(i);

        if(i != inventory_cursor_pos) window->add_str("   ");
        else window->add_str(" > ", *cursor_color);

        if(item->attributes.size() == 0)
        {
            window->add_str(item->name + '\n');
            continue;
        }
        
        window->add_str(item->name + "\n    - ");
        window->add_str(item->attributes.at(0) + '\n');
    }

    window->reset_cursor_position();
    window->reset_anchor();
}
