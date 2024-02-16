#include "LSDLE.h"
#include "MenuHandler.h"
#include "SettingsMenu.h"
#include "LRandom.h"

#include "SkillModificationMenu.h"
#include "Simulator.h"

// Constructors / Deconstructor

SkillModificationMenu::SkillModificationMenu() : 
    Menu(0, 0, LSDLE::get_screen_width(), LSDLE::get_screen_height(), 
    "SkillModification")
{
    alchemy_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Alchemy", "");
    anim_han_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Animal Handling", "");
    appraising_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Apraising", "");
    arcanary_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Arcanary", "");
    athletics_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Athletics", "");
    cooking_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Cooking", "");
    intelligence_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Intelligence", "");
    medicine_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Medicine", "");
    perception_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Percpeption", "");
    speech_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Speech", "");
    stealth_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Stealth", "");
    strength_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Strength", "");
    survival_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Survival", "");
    sl_of_hand_skill = new MenuToolVariable(window, MenuToolItem::INT, "White", 
        "Slight of Hand", "");

    randomize_skill_button = new MenuToolButton<SkillModificationMenu>
        (this, randomize_skills, window, "Randomize Skills", "White", "Purple");
    save_changes_button = new MenuToolButton<SkillModificationMenu>
        (this, update_player_skills, window, "Save Changes", "White", "Green");
    cancel_button = new MenuToolButton<SkillModificationMenu>
        (this, deactivate_menu, window, "Cancel", "White", "Red");

    msdc.content.push_back(alchemy_skill);
    msdc.content.push_back(anim_han_skill);
    msdc.content.push_back(appraising_skill);
    msdc.content.push_back(arcanary_skill);
    msdc.content.push_back(athletics_skill);
    msdc.content.push_back(cooking_skill);
    msdc.content.push_back(intelligence_skill);
    msdc.content.push_back(medicine_skill);
    msdc.content.push_back(perception_skill);
    msdc.content.push_back(speech_skill);
    msdc.content.push_back(stealth_skill);
    msdc.content.push_back(strength_skill);
    msdc.content.push_back(survival_skill);
    msdc.content.push_back(sl_of_hand_skill);
    msdc.content.push_back(randomize_skill_button);
    msdc.content.push_back(save_changes_button);
    msdc.content.push_back(cancel_button);

    player = Simulator::get_player();
}


// Public

void SkillModificationMenu::init_menu()
{
    cursor_color = static_cast<SettingsMenu*>(
        MenuHandler::get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();
}

void SkillModificationMenu::reset_cursor_color()
{
    alchemy_skill->set_cursor_color(*cursor_color);
    anim_han_skill->set_cursor_color(*cursor_color);
    appraising_skill->set_cursor_color(*cursor_color);
    arcanary_skill->set_cursor_color(*cursor_color);
    athletics_skill->set_cursor_color(*cursor_color);
    cooking_skill->set_cursor_color(*cursor_color);
    intelligence_skill->set_cursor_color(*cursor_color);
    medicine_skill->set_cursor_color(*cursor_color);
    perception_skill->set_cursor_color(*cursor_color);
    speech_skill->set_cursor_color(*cursor_color);
    stealth_skill->set_cursor_color(*cursor_color);
    strength_skill->set_cursor_color(*cursor_color);
    survival_skill->set_cursor_color(*cursor_color);
    sl_of_hand_skill->set_cursor_color(*cursor_color);
    randomize_skill_button->set_cursor_color(*cursor_color);
    save_changes_button->set_cursor_color(*cursor_color);
    cancel_button->set_cursor_color(*cursor_color);
}

void SkillModificationMenu::start()
{
    msdc.cursor_pos = 0;
    msdc.selected_pos = -1;

    load_player_skills();
}

void SkillModificationMenu::update()
{
    window->add_str("[ Player Menu / View Skills / Modify Skills ]\n\n");

    window->add_str("-- Make a Selection --\n\n");

    menu_tools->simulate_menu(msdc);

    // if(msdc.selected_pos == -1) return;

    // switch(msdc.selected_pos)
    // {
    //     // Randomize Skills
    //     case 14:

    //         randomize_skills();
    //         return;

    //     // Save Changes
    //     case 15:

    //         update_player_skills();
            
    //         // This switch case is intended to fall through

    //     // Cancel
    //     case 16:
        
    //         MenuHandler::deactivate_menu(this);
    //         return;
    // }
}

// Private

void SkillModificationMenu::update_player_skills()
{
    for(uint8_t i = 0; i < 14; ++i)
    {
        player->skills.at(i) = static_cast<MenuToolVariable*>(
            msdc.content.at(i))->fetch_int();
    }

    deactivate_menu();
}

void SkillModificationMenu::load_player_skills()
{
    for(uint8_t i = 0; i < 14; ++i)
    {
        static_cast<MenuToolVariable*>(msdc.content.at(i))->content = 
            std::to_string(player->skills.at(i));
    }
}

#include <iostream>

void SkillModificationMenu::randomize_skills()
{
    for(uint8_t i = 0; i < msdc.content.size() - 3; ++i)
    {
        static_cast<MenuToolVariable*>(msdc.content.at(i))->content
            = std::to_string(LRandomGenerator::get_random_num(2, 12));
    }
}
