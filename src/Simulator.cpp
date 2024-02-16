#include "MenuToolText.h"
#include "EventSystem.h"
#include "InputHandler.h"

#include "Simulator.h"

// Static Members

Player* Simulator::player {};


// Constructors / Deconstructor

Simulator::Simulator() : LSDLE("C:/Users/on3sn/LSDLE"), 
    player_handler("C:/Users/on3sn/Documents/DnDTool3.0/Player_Saves")
{
    player = new Player;

    CallbackManager::subscribe<Simulator>("save player", this, save_player);
    CallbackManager::subscribe<Simulator>("quit", this, stop_engine);

    int screen_width = get_screen_width();
    int screen_height = get_screen_height();

    main_sim_menu = new MainSimMenu(0, 0, screen_width, 
        screen_height);

    hit_mana_mod_menu = new HitpointManaModificationMenu(0, 0, screen_width, 
        screen_height);

    stat_menu = new StatsOverlayMenu(0, 0, screen_width, screen_height);

    settings_menu = new SettingsMenu(0, 0, screen_width, screen_height);

    v_inv_menu = new ViewInventoryMenu(0, 0, screen_width, screen_height);

    sim_init_menu = new SimulationInitMenu(0, 0, screen_width, screen_height);

    load_p_menu = new LoadPlayerMenu(0, 0, screen_width, screen_height);
    load_p_menu->set_player_handler(&player_handler);

    skill_menu = new SkillsOverlayMenu(0, 0, screen_width, screen_height);

    skill_mod_menu = new SkillModificationMenu();

    stat_mod_menu = new StatModificationMenu();

    initialize_menus();

    MenuHandler::activate_menu(sim_init_menu);
}; 


// Public

void Simulator::start()
{
    LSDLE::start();

}

Player* Simulator::get_player() { return player; }


// Private

void Simulator::update() 
{
    // process_keys();
}

void Simulator::render() {}

void Simulator::initialize_menus()
{
    main_sim_menu->init_menu();
    hit_mana_mod_menu->init_menu();
    stat_menu->init_menu();
    v_inv_menu->init_menu();
    sim_init_menu->init_menu();
    load_p_menu->init_menu();
    skill_menu->init_menu();
    skill_mod_menu->init_menu();
    stat_mod_menu->init_menu();

    // stat_mod_menu->init_menu();
}

// void Simulator::process_keys()
// {
//     for(uint16_t key : input_handler->get_all_pressed_keys())
//     {
//         if(key_to_callbacks.find(key) == key_to_callbacks.end()) continue;

//         CallbackManager::trigger_callback(key_to_callbacks[key]);
//     }
// }


void Simulator::stop_engine()
{
    quit();
}

void Simulator::save_player()
{
    player_handler.save_player(player);
}
