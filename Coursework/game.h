#pragma once
#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_level_select.h"
#include "scenes/scene_options.h"
#include "BGSpriteLoader.h"
#include "soundManager.h"
#include "scenes/scene_splash.h"
#include "GameManager.h"
#include "scenes/scene_volume.h"
#include "scenes/scene_res.h"

//extern int gameX = 720;
//extern int gameY = 1080;

extern BGSpriteLoader spriteLoader;
extern SoundManager sounds;
extern SplashScene splash;
extern GameManager gManager;
extern MenuScene menu;
extern LevelMenuScene levelSelect;
extern OptionsMenuScene optionsScene;
extern VolumeMenuScene volScene;
extern ResMenuScene resScene;
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;
