/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "display.h"
/*Inicializa o display*/
void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

/*Destroi o display*/
void disp_deinit()
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

/*Prepara o display para o tamanho certo*/
void disp_pre_draw()
{
    al_set_target_bitmap(buffer);
}

/*Ajusta o tamanho do display*/
void disp_post_draw()
{
    al_set_target_backbuffer(disp);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

    al_flip_display();
}