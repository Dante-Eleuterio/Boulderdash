/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "headers.h"

/*Defines para os sprites do mapa*/
#define EMPTY 0
#define BEDROCK 1
#define DIRT 2
#define DIAMOND 3
#define FALLEN_DIAMOND -3
#define TO_FALL_DIAMOND 12
#define TO_ROLL_DIAMOND -12
#define BOULDER 4
#define FALLEN_BOULDER -4
#define TO_FALL_BOULDER 11
#define TO_ROLL_BOULDER -11
#define BRICK 5
#define PLAYER_S 6
#define PLAYER_L0 7
#define PLAYER_L1 -7
#define PLAYER_R0 8
#define PLAYER_R1 -8
#define CLOSED_EXIT 9
#define OPEN_EXIT 10

/*Struct para os audios*/
typedef struct AUDIOS
{
    ALLEGRO_SAMPLE* death_sound;
    ALLEGRO_SAMPLE* boulder_sound;
    ALLEGRO_SAMPLE* diamond_sound;
    ALLEGRO_SAMPLE* victory_sound;
    ALLEGRO_SAMPLE* door_sound;
    ALLEGRO_SAMPLE* creeper_sound;


}AUDIOS;

/*Struct para os sprites*/
typedef struct SPRITES
{
    ALLEGRO_BITMAP* sheet;
    ALLEGRO_BITMAP* boulder;
    ALLEGRO_BITMAP* player_still;
    ALLEGRO_BITMAP* LEFT_0;
    ALLEGRO_BITMAP* LEFT_1;
    ALLEGRO_BITMAP* RIGHT_0;
    ALLEGRO_BITMAP* RIGHT_1;
    ALLEGRO_BITMAP* bedrock;
    ALLEGRO_BITMAP* diamond;
    ALLEGRO_BITMAP* diamond_font;
    ALLEGRO_BITMAP* brick;
    ALLEGRO_BITMAP* dirt;
    ALLEGRO_BITMAP* closed_exit;
    ALLEGRO_BITMAP* open_exit;
    ALLEGRO_BITMAP* creeper;

} SPRITES;

/*Struct para o hud*/
typedef struct hud
{
    int diamonds_required;
    int diamonds_value;
    int diamonds_caught;
    int clock;
    int points;
    int scores[10];
} hud;

/*Struct para o player*/
typedef struct player
{
    int x;
    int y;
    int moving_animation;
    int alive;
    int won;
} player;


ALLEGRO_BITMAP* sprite_grab(SPRITES *sprites,int x, int y, int w, int h);
void sprites_init();
void sprites_denit();
void player_update(int matriz[22][40],SPRITES *sprites,unsigned char key[ALLEGRO_KEY_MAX],player *miner,hud *HUD,AUDIOS *audios);
void init_player(player *miner);
void detect_fall(int matriz[22][40],SPRITES *sprites,player *miner);
void map_update(int matriz[22][40],SPRITES *sprites,player *miner,hud *HUD,AUDIOS *audios);
void audios_init(AUDIOS *audios);
void audios_denit(AUDIOS *audios);
void kill_player(player *miner,int y,int x,int matriz[22][40]);
