#include "ColorString.h"
#include "LSDLE.h"

#include "SkillsOverlayMenu.h"
#include "Settingsmenu.h"
#include "MenuHandler.h"
#include "Simulator.h"
#include "LRandom.h"


// Constructors / Deconstructor

SkillsOverlayMenu::SkillsOverlayMenu(uint16_t start_x, uint16_t start_y, 
    uint16_t end_x, uint16_t end_y) : Menu(start_x, start_y, end_x, end_y,
    "SkillsOverlay")
{
    lsdc.content.push_back(ColorString("Modify Skills", "White"));
    lsdc.content.push_back(ColorString("Back", "Red"));

    player = Simulator::get_player();

    // alchemy_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 0, 0, 8,
    //     11, 8, 11);
    // anim_han_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 8, 0, 8,
    //     11, 8, 11);
    // appraising_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 16, 0, 8,
    //     11, 8, 11);
    // arcanary_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 24, 0, 8,
    //     11, 8, 11);
    // athletics_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 32, 0, 8,
    //     11, 8, 11);
    // cooking_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 0, 11, 8,
    //     11, 8, 11);
    // crafting_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 8, 11, 8,
    //     11, 8, 11);
    // intel_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 16, 11, 8,
    //     11, 8, 11);
    // medicine_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 24, 11, 8,
    //     11, 8, 11);
    // percep_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 32, 11, 8,
    //     11, 8, 11);
    // speech_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 0, 22, 8,
    //     11, 8, 11);
    // stealth_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 8, 22, 8,
    //     11, 8, 11);
    // strength_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 16, 22, 8,
    //     11, 8, 11);
    // survival_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 24, 22, 8,
    //     11, 8, 11);
    // slight_of_hand_sprite = SpriteHandler::create_sprite("assets/Skill_Icons.png", 32, 22, 8,
    //     11, 8, 11);
}


// Public

void SkillsOverlayMenu::init_menu()
{
    cursor_color = static_cast<SettingsMenu*>(
        MenuHandler::get_menu("Settings"))->get_cursor_color();

    reset_cursor_color();
}

void SkillsOverlayMenu::reset_cursor_color()
{
    lsdc.cursor_color = *cursor_color;
}

void SkillsOverlayMenu::start() 
{
    lsdc.cursor_pos = 0;
    lsdc.item_has_been_selected = false;
}

void SkillsOverlayMenu::update()
{
    window->add_str("[ Player Menu / View Skills ]\n\n");

    render_skills();

    window->add_str("\n\n-- Make a Selection--\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    switch(lsdc.cursor_pos)
    {
        // Modify Skills
        case 0:

            MenuHandler::activate_menu("SkillModification");
            return;

        case 1:

            MenuHandler::deactivate_menu(this);
            return;
    }
}   


// Private

void SkillsOverlayMenu::render_skills()
{
    window->add_str("Alchemy: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(0), 0, 10);
    window->add_str("\nAnimal handling: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(1), 0, 10);
    window->add_str("\nAppraising: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(2), 0, 10);
    window->add_str("\nArcanary: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(3), 0, 10);
    window->add_str("\nAthletics: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(4), 0, 10);
    window->add_str("\nCooking: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(5), 0, 10);
    window->add_str("\nIntelligence: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(6), 0, 10);
    window->add_str("\nMedicine: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(7), 0, 10);
    window->add_str("\nPerception: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(8), 0, 10);
    window->add_str("\nSpeech: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(9), 0, 10);
    window->add_str("\nStealth: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(10), 0, 10);
    window->add_str("\nStrength: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(11), 0, 10);
    window->add_str("\nSurvival: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(12), 0, 10);
    window->add_str("\nSlight of Hand: ", "LightGray");
    menu_tools->render_colored_number(player->skills.at(13), 0, 10);
}
