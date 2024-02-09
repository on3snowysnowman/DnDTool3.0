#include <MenuToolText.h>
#include <EventSystem.h>
#include <InputHandler.h>

#include "Simulator.h"


// Constructors / Deconstructor

Simulator::Simulator() : LSDLE("C:/Users/on3sn/LSDLE") 
{
    CallbackManager::subscribe<Simulator>("quit", this, save_player);
    CallbackManager::subscribe<Simulator>("quit", this, stop_engine);

    int screen_width = get_screen_width();
    int screen_height = get_screen_height();

    p_handler = new PlayerHandler(
        "C:/Users/on3sn/Documents/DnDTool3.0/Player_Saves");

    player = p_handler->load_player(
        "C:/Users/on3sn/Documents/DnDTool3.0/Player_Saves/Logoosal.json");
        
    main_sim_menu = new MainSimMenu(0, 0, screen_width, 
        screen_height, player);

    hit_mod_menu = new HitpointManaModificationMenu(0, 0, screen_width, 
        screen_height);

    stat_menu = new StatsOverlayMenu(0, 0, screen_width, screen_height);

    settings_menu = new SettingsMenu(0, 0, screen_width, screen_height);

    v_inv_menu = new ViewInventoryMenu(0, 0, screen_width, screen_height);

    initialize_menus();

    MenuHandler::activate_menu(main_sim_menu);
}; 


// Public

void Simulator::start()
{
    LSDLE::start();

}


// Private

void Simulator::update() 
{
    process_keys();
}

void Simulator::render() {}

void Simulator::initialize_menus()
{
    main_sim_menu->init_menu();
    hit_mod_menu->init_menu();
    stat_menu->init_menu();
    v_inv_menu->init_menu();
}

void Simulator::process_keys()
{
    for(uint16_t key : input_handler->get_all_pressed_keys())
    {
        if(key_to_callbacks.find(key) == key_to_callbacks.end()) continue;

        CallbackManager::trigger_callback(key_to_callbacks[key]);
    }
}

void Simulator::save_player()
{
    p_handler->save_player(player);
}

void Simulator::stop_engine()
{
    quit();
}
