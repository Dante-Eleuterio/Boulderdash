/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "headers.h"
#include "map.h"

void draw_map(SPRITES *sprites,int matriz[22][40],player *miner);
void draw_hud(SPRITES *sprites,hud *HUD,ALLEGRO_FONT *font,ALLEGRO_FONT *small_font);
void init_hud(hud *HUD);
void draw_help(SPRITES *sprites,ALLEGRO_FONT *small_font,ALLEGRO_FONT *font,hud *HUD);
void restart(hud *HUD,player *miner,int matriz[22][40],int *done,int *redraw,int *PAUSE,int *DEAD,int *VICTORY,int *clock);
void player_died(AUDIOS *audios,ALLEGRO_FONT *font);
void player_won(AUDIOS *audios,ALLEGRO_FONT *font,ALLEGRO_FONT *small_font,hud *HUD);
void scan_scores(hud *HUD);
void check_scores(hud* HUD);
void reset_scores(hud *HUD);
