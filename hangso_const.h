#ifndef CONST_H
#define CONST_H

const int TILE_WIDTH = 48;
const int TILE_HEIGHT = 48;
const int TOTAL_TILES = 500*50;

const int WIDTH_MAP = 500*48;
const int HEIGHT_MAP = 50*48;

const int TILES_CLIP = 100;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

const int PLAYER_WIDTH = 64;
const int PLAYER_HEIGHT = 96;

const int PLAYER_WIDTH_ATTACK = 192;
const int PLAYER_HEIGHT_ATTACK = 160;

const int PLAYER_WIDTH_JUMP = 128;
const int PLAYER_HEIGHT_JUMP = 128;
const int PLAYER_MAX_JUMP = 70;
const int PLAYER_VEL = 3;

enum textureID{
    MIDDLE_TEXTURE,
    BACK_TEXTURE,
    MAP_TEXTURE,
    PLAYER_TEXTURE,
    EFFECT_TEXTURE,
    MONSTER_TEXTURE,
    WIZARD_TEXTURE,
    HEALTH_TEXTURE,
    HP_ENEMY_TEXTURE,
    MENU_TEXTURE,
    BOSS_TEXTURE,
    TOTAL_TEXTURE
};

const int PLAYER_IDLE = 4;
const int PLAYER_RUN = 8;
const int PLAYER_JUMP = 15;
const int PLAYER_ATTACK = 8;
const int PLAYER_TAKEHIT = 3;
const int PLAYER_DEATH = 8;
const int PLAYER_HEALTH = 6;
const int  EFFECT_CLIP = 60;

const int MONSTER_WIDTH = 80;
const int MONSTER_HEIGHT = 96;


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

const int WIZARD_WIDTH = 64;
const int WIZARD_HEIGHT = 96;
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


const int BOSS_WIDTH = 150;
const int BOSS_HEIGHT = 150*6/5;

const int BOSS_VEL = 3;

const int BOSS_IDLE = 7;
const int BOSS_TAKEHIT = 5;
const int BOSS_ATTACK1 = 17;
const int BOSS_ATTACK2 = 13;
const int BOSS_SKILL2 = 11;
const int RESTART_GAME_WIDTH = 500;
const int RESTART_GAME_HEIGHT = 400;
#endif // CONST_H
