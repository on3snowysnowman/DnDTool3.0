#include <EventSystem.h>

#include "SettingsMenu.h"
#include "LSDLE.h"
#include "TextureHandler.h"
#include "MenuHandler.h"


// Constructors / Deconstructor

SettingsMenu::SettingsMenu(uint16_t start_x, uint16_t start_y, uint16_t end_x, 
    uint16_t end_y) : Menu(start_x, start_y, end_x, end_y, "Settings")
{
    CallbackManager::subscribe<SettingsMenu>
        ("reset cursor color", this, reset_cursor_color);

    cancel_button = new MenuToolButton(window, "Cancel", cursor_color, "Red");
    apply_button = new MenuToolButton(window, "Apply Changes", cursor_color, 
        "Green");
    
    cursor_color_choice = new MenuToolChoice(window, cursor_color, "Cursor Color",
        0);

    uint8_t count {};

    for(auto _pair : *LSDLE::get_texture_handler()->get_colors())
    {
        cursor_color_choice->choices.push_back(ColorString(_pair.first,
            _pair.first));

        if(_pair.first == cursor_color) 
        {
            cursor_color_choice->choice_index = count;
            cursor_color_index = count;
        }

        ++count;
    }

    msdc.content.push_back(cursor_color_choice);
    msdc.content.push_back(apply_button);
    msdc.content.push_back(cancel_button);
}


// Public

void SettingsMenu::reset_cursor_color()
{
    cursor_color_choice->set_cursor_color(cursor_color);
    apply_button->set_cursor_color(cursor_color);
    cancel_button->set_cursor_color(cursor_color);
}

void SettingsMenu::start() 
{
    msdc.cursor_pos = 0;
    cursor_color_choice->choice_index = cursor_color_index;
    cursor_color_choice->cursor_index = cursor_color_index;
}

void SettingsMenu::update() 
{
    window->add_str("[ Main Menu / Settings ]\n\n");
    window->add_str("-- Make a Selection --\n\n");

    menu_tools->simulate_menu(msdc);

    if(msdc.selected_pos == -1) return;

    switch(msdc.selected_pos)
    {
        // Apply Changes
        case 1:

            cursor_color = cursor_color_choice->get_choice();
            cursor_color_index = cursor_color_choice->choice_index;
            CallbackManager::trigger_callback("reset cursor color");
            return;

        // Back
        case 2:

            MenuHandler::deactivate_menu(this);
            return;
    }
}

std::string* SettingsMenu::get_cursor_color() { return &cursor_color; }


// Private


