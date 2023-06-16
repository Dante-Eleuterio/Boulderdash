/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "headers.h"
#define KEY_SEEN     1
#define KEY_RELEASED 2

void keyboard_init(unsigned char key[ALLEGRO_KEY_MAX]);
void keyboard_update(ALLEGRO_EVENT* event,unsigned char key[ALLEGRO_KEY_MAX]);
