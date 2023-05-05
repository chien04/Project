#ifndef CONST_H
#define CONST_H

const int TILE_WIDTH = 48;
const int TILE_HEIGHT = 48;
const int TOTAL_TILES = 380*50;

const int WIDTH_MAP = 380*48;
const int HEIGHT_MAP = 50*48;

const int TILES_CLIP = 100;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 75;

const int PLAYER_WIDTH_ATTACK = 192;
const int PLAYER_HEIGHT_ATTACK = 160;

const int PLAYER_WIDTH_JUMP = 128;
const int PLAYER_HEIGHT_JUMP = 128;
const int PLAYER_MAX_JUMP = 70;
const int PLAYER_VEL = 3;
const int ATTACK_SKILL = 9;
enum textureID{
    BACKGROUND_TEXTURE,
    MAP_TEXTURE,
    PLAYER_TEXTURE,
    SKILL_TEXTURE,
    MONSTER_TEXTURE,
    WIZARD_TEXTURE,
    HEALTH_TEXTURE,
    HP_ENEMY_TEXTURE,
    MENU_TEXTURE,
    BOSS_TEXTURE,
    BOSS_HP_TEXTURE,
    TOTAL_TEXTURE
};

const int PLAYER_IDLE = 4;
const int PLAYER_RUN = 8;
const int PLAYER_JUMP = 15;
const int PLAYER_ATTACK = 8;
const int PLAYER_TAKEHIT = 3;
const int PLAYER_DEATH = 8;
const int PLAYER_HEALTH = 6;
const int PLAYER_EXP = 7;
const int  EFFECT_CLIP = 60;

const int MONSTER_WIDTH = 60;
const int MONSTER_HEIGHT = 72;


const int MONSTER_VEL_X = 1;
const int MONSTER_VEL_Y = 5;
const int MONSTER_IDLE = 2;
const int MONSTER_RUN = 8;
const int MONSTER_ATTACK = 6;

const int MONSTER_KNOCKBACK = 1;
const int MONSTER_DEATH = 2;
const int TOTAL_FRAME = 5;

const int FRAME_IDLE = 0;
const int FRAME_RUN = 1;
const int FRAME_ATTACK = 2;
const int FRAME_KNOCKBACK = 3;
const int FRAME_DEATH = 4;

const int MONSTER_HP = 5;
const int TOTAL_MONSTER = 3;

const int WIZARD_WIDTH = 60;
const int WIZARD_HEIGHT = 75;
const int TOTAL_WIZARD = 3;

const int WIZARD_IDLE = 13;
const int WIZARD_ATTACK = 10;
const int WIZARD_TAKE_HIT = 4;
const int WIZARD_DEATH = 10;
const int WIZARD_HP = 4;
enum wizardId{
    IDLE,
    ATTACK,
    TAKE_HIT,
    DEATH,
    WIZARD_FRAME
};

const int BULLET_VEL = 3;


const int BOSS_WIDTH = 170;
const int BOSS_HEIGHT = 210;

const int BOSS_VEL = 2;
const int BOSS_HP = 26;
const int BOSS_IDLE = 7;
const int BOSS_RUNNING = 8;
const int BOSS_TAKEHIT = 5;
const int BOSS_ATTACK1 = 17;
const int BOSS_ATTACK2 = 13;
const int BOSS_SKILL2 = 11;
const int BOSS_DEATH = 9;

const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;

enum statesMenu{
    PLAY_STATE,
    QUIT_STATE,
    TOTAL_STATE
};
enum stateReload{
    RELOAD_STATE,
    MENU_STATE,
    TOTAL_STATERELOAD
};

enum statePause{
    RELOAD_STATEPAUSE,
    MENU_STATEPAUSE,
    CONTINUTE_STATE,
    TOTAL_STATEPAUSE
};
const int RESTART_GAME_WIDTH = 600;
const int RESTART_GAME_HEIGHT = 400;

enum music{
    MUSIC_HOME,
    MUSIC_BATTLE,
    TOTAL_MUSIC
};

enum sound{
    PRESS_BUTTON,
    PLAYER_RUNSOUND,
    PLAYER_ATTACKSOUND,
    PLAYER_JUMPSOUND,
    PLAYER_ATTACKMISSSOUND,
    PLAYER_DAMAGESOUND,
    PLAYER_DEATHSOUND,
    PLAYER_ATTACKSKILLSOUND,
    PLAYER_HEALINGSOUND,

    MONSTER_ATTACKSOUND,
    MONSTER_TAKEHITSOUND,
    MONSTER_DEATHSOUND,

    WIZARD_ATTACKSOUND,
    WIZARD_TAKEHITSOUND,
    WIZARD_DEATHSOUND,

    BOSS_LIGHTNINGSOUND,
    BOSS_FIRESOUND,
    BOSS_SOUND,
    BOSS_DEATHSOUND,

    TOTAL_SOUND
};
#endif // CONST_H
