#include <MenuToolText.h>
#include <EventSystem.h>
#include <InputHandler.h>

#include "Simulator.h"


// Constructors / Deconstructor

Simulator::Simulator() : LSDLE("C:/Users/on3sn/LSDLE") 
{
    CallbackManager::subscribe<Simulator>("quit", this, stop_engine);

    int screen_width = get_screen_width();
    int screen_height = get_screen_height();

    main_sim_menu = new MainSimMenu(0, 0, screen_width, 
        screen_height);

    hit_mod_menu = new HitpointManaModificationMenu(0, 0, screen_width, 
        screen_height);

    stat_menu = new StatsOverlayMenu(0, 0, screen_width, screen_height);

    settings_menu = new SettingsMenu(0, 0, screen_width, screen_height);

    main_sim_menu->init_menu();
    hit_mod_menu->init_menu();
    stat_menu->init_menu();

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

void Simulator::process_keys()
{
    for(uint16_t key : input_handler->get_all_pressed_keys())
    {
        if(key_to_callbacks.find(key) == key_to_callbacks.end()) continue;

        CallbackManager::trigger_callback(key_to_callbacks[key]);
    }
}

void Simulator::stop_engine()
{
    quit();
}
