/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "headers.h"
#define BUFFER_W 1280
#define BUFFER_H 756
#define DISP_SCALE 1
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)
ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

void disp_init();
void disp_deinit();
void disp_pre_draw();
void disp_post_draw();