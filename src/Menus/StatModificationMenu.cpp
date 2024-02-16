#include "LSDLE.h"
#include "EventSystem.h"
#include "Menuhandler.h"

#include "StatModificationMenu.h"
#include "Simulator.h"
#include "SettingsMenu.h"


// Constructors / Deconstructor

StatModificationMenu::StatModificationMenu() : 
    Menu(0, 0, LSDLE::get_screen_width(), LSDLE::get_screen_height(), 
    "StatModification")
{
    CallbackManager::subscribe<StatModificationMenu>
        ("reset cursor color", this, reset_cursor_color);

    name_var = new MenuToolVariable(window, MenuToolItem::STRING, "White", 
        "Name", "");
    max_hitpoints_var = new MenuToolVariable(window, MenuToolItem::INT, "White",
        "Max Hitpoints", "");
    max_mana_var = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Max Mana", "");
    defense_var = new MenuToolVariable(window, MenuToolVariable::INT, "White",
        "Defense", "");
    evasion_var = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Evasion", "");
    save_changes_button = new MenuToolButton<StatModificationMenu>
        (this, update_player_stats, window, "Save Changes", "White", "Green");
    cancel_button = new MenuToolButton<StatModificationMenu>
        (this, deactivate_menu, window, "Cancel", "White", "Red");
    
    msdc.content.push_back(name_var);
    msdc.content.push_back(max_hitpoints_var);
    msdc.content.push_back(max_mana_var);
    msdc.content.push_back(defense_var);
    msdc.content.push_back(evasion_var);
    msdc.content.push_back(save_changes_button);
    msdc.content.push_back(cancel_button);

    player = Simulator::get_player();
}


// Public

void StatModificationMenu::init_menu()
{
    cursor_color = static_cast<SettingsMenu*>(
        MenuHandler::get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();
}

void StatModificationMenu::reset_cursor_color()
{
    name_var->set_cursor_color(*cursor_color);
    max_hitpoints_var->set_cursor_color(*cursor_color);
    max_mana_var->set_cursor_color(*cursor_color);
    defense_var->set_cursor_color(*cursor_color);
    evasion_var->set_cursor_color(*cursor_color);
    save_changes_button->set_cursor_color(*cursor_color);
    cancel_button->set_cursor_color(*cursor_color);
}

void StatModificationMenu::start()
{
    msdc.cursor_pos = 0;
    msdc.selected_pos = -1;

    load_player_stats();
}

void StatModificationMenu::update()
{
    window->add_str("[ Player Menu / Modify Stats ]\n\n");
    window->add_str("-- Make a Selection --\n\n");

    menu_tools->simulate_menu(msdc);
}



// Private

void StatModificationMenu::load_player_stats() 
{
    name_var->content = player->name;
    max_hitpoints_var->content = std::to_string(player->max_hitpoints);
    max_mana_var->content = std::to_string(player->max_mana);
    defense_var->content =  std::to_string(player->defense);
    evasion_var->content = std::to_string(player->evasion);
}

void StatModificationMenu::update_player_stats() 
{
    player->name = name_var->content;
    player->max_hitpoints = max_hitpoints_var->fetch_int();

    player->hitpoints = (player->hitpoints > player->max_hitpoints)
        ? player->max_hitpoints : player->hitpoints;

    player->max_mana = max_mana_var->fetch_int();

    player->mana = (player->mana > player->max_mana)
        ? player->max_mana : player->mana;

    player->defense = defense_var->fetch_int();
    player->evasion = evasion_var->fetch_int();

    deactivate_menu();
}
