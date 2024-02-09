#pragma once

#include <LSDLE.h>
#include <MenuToolText.h>
#include <ConsoleOutputHandler.h>
#include <unordered_map>

#include "MainSimMenu.h"
#include "HitpointManaModificationMenu.h"
#include "StatsOverlayMenu.h"
#include "SettingsMenu.h"


class Simulator : public LSDLE
{

public:

    Simulator();

    void start();

private:

    void update() final;
    void render() final;

    void process_keys();

    void stop_engine();

    std::unordered_map<char, std::string> key_to_callbacks
    {
        {SDLK_ESCAPE, "quit"}
    };

    MainSimMenu* main_sim_menu;
    HitpointManaModificationMenu* hit_mod_menu;
    StatsOverlayMenu* stat_menu;
    SettingsMenu* settings_menu;
};
