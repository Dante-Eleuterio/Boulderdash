/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "keyboard.h"
/*Cria um vetor para guardar as teclas pressionadas*/
void keyboard_init(unsigned char key[ALLEGRO_KEY_MAX])
{
    memset(key, 0,227 );
}

/*Atualiza o imput do teclado*/
void keyboard_update(ALLEGRO_EVENT* event,unsigned char key[ALLEGRO_KEY_MAX])
{
    
    switch(event->type)
    {
        case ALLEGRO_EVENT_TIMER:
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] &= KEY_RELEASED;
            break;
    }
}