#pragma once

#include "LSDLE.h"
#include "MenuToolText.h"

#include "MainSimMenu.h"
#include "HitpointManaModificationMenu.h"
#include "StatsOverlayMenu.h"
#include "SettingsMenu.h"
#include "PlayerHandler.h"
#include "ViewInventoryMenu.h"
#include "SimulationInitMenu.h"
#include "LoadPlayerMenu.h"
#include "SkillsOverlayMenu.h"
#include "SkillModificationMenu.h"
#include "StatModificationMenu.h"


class Simulator : public LSDLE
{

public:

    Simulator();

    void start();

    static Player* get_player();

private:

    void update() final;
    void render() final;

    void initialize_menus();

    // void process_keys();
    void stop_engine();

    void save_player();

    static Player* player;

    PlayerHandler player_handler;

    MainSimMenu* main_sim_menu {};
    HitpointManaModificationMenu* hit_mana_mod_menu {};
    StatsOverlayMenu* stat_menu {};
    SettingsMenu* settings_menu {};
    ViewInventoryMenu* v_inv_menu {};
    SimulationInitMenu* sim_init_menu {};
    LoadPlayerMenu* load_p_menu {};
    SkillsOverlayMenu* skill_menu {};
    SkillModificationMenu* skill_mod_menu {};
    StatModificationMenu* stat_mod_menu {};
};
