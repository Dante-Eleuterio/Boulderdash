/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "headers.h"
#include "display.h"
#include "drawing.h"
#include "keyboard.h"




int main(int argc, char const *argv[])
{
    player miner;
    unsigned char key[ALLEGRO_KEY_MAX];
    SPRITES sprites;
    AUDIOS audios;
    hud HUD;
    int clock=0;
    int PAUSE=-1;
    int DEAD=0;
    int VICTORY=0;
    int matriz [22][40];
    scan_matrix(matriz);

    /*Inicizaliza funções da Allegro*/
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");
    must_init(al_init_image_addon(), "image addon");
    
    /*Inicializa os timers*/
    ALLEGRO_TIMER* fps_timer = al_create_timer(1.0 / 60.0);
    must_init(fps_timer, "fps_timer");
    
    ALLEGRO_TIMER* player_timer = al_create_timer(1.0 / 10);
    must_init(player_timer, "player_timer");
    
    ALLEGRO_TIMER* map_timer = al_create_timer(1.0 / 8);
    must_init(map_timer, "map_timer");
    
    ALLEGRO_TIMER* detect_fall_timer = al_create_timer(1.0 / 4);
    must_init(detect_fall_timer, "detect_fall_timer");


    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");
    
    /*Inicializa funções do código*/
    disp_init();
    sprites_init(&sprites);
    audios_init(&audios);
    init_hud(&HUD);
    init_player(&miner);

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT* font = al_load_font("Resources/Oswald-Medium.ttf",32,0);
    must_init(font, "font");
    ALLEGRO_FONT* small_font = al_load_font("Resources/Oswald-Medium.ttf",16,0);
    must_init(small_font, "small_font");

   
    
   
    /*Adiciona os eventos à fila*/
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(fps_timer));
    al_register_event_source(queue, al_get_timer_event_source(player_timer));
    al_register_event_source(queue, al_get_timer_event_source(map_timer));
    al_register_event_source(queue, al_get_timer_event_source(detect_fall_timer));

    keyboard_init(key);

    int done = 0;
    int redraw = 1;
    ALLEGRO_EVENT event;

    /*Inicia os timers*/
    al_start_timer(fps_timer);
    al_start_timer(player_timer);
    al_start_timer(map_timer);
    al_start_timer(detect_fall_timer);
    
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if(PAUSE!=1 && DEAD!=1 &&VICTORY!=1)
                {
                    if(event.timer.source==player_timer)/*Atualiza o player*/
                    {
                        player_update(matriz,&sprites,key,&miner,&HUD,&audios);
                        clock++;
                    }
                    if(event.timer.source==map_timer) /*Atualiza o mapa*/
                        map_update(matriz,&sprites,&miner,&HUD,&audios);

                    if(event.timer.source==detect_fall_timer)
                        detect_fall(matriz,&sprites,&miner);/*Detecta as pedras e diamantes a serem marcadas para cair*/
                    
                    redraw=1;
                }
                break;
            case ALLEGRO_EVENT_KEY_DOWN:

                /*Se o player apertar "R", reinicia o jogo*/
                if(PAUSE!=1 && event.keyboard.keycode==ALLEGRO_KEY_R)
                    restart(&HUD,&miner,matriz,&done,&redraw,&PAUSE,&DEAD,&VICTORY,&clock);

                /*Se o player apertar "R" enquanto pausado, zera os scores*/
                if(PAUSE==1 && event.keyboard.keycode==ALLEGRO_KEY_R)
                {
                    al_play_sample(audios.creeper_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); 
                    reset_scores(&HUD);
                    disp_pre_draw();
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(sprites.creeper,300,570,0);
                    draw_hud(&sprites,&HUD,font,small_font);
                    draw_help(&sprites,small_font,font,&HUD);
                    disp_post_draw();

                }
                
                /*Se o player apertar "F1" ou "H" pausa o jogo*/    
                if(DEAD!=1 && VICTORY!=1 &&(event.keyboard.keycode==ALLEGRO_KEY_H || event.keyboard.keycode==ALLEGRO_KEY_F1 ))
                {
                        PAUSE*=-1;
                        disp_pre_draw();
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        draw_hud(&sprites,&HUD,font,small_font);
                        draw_help(&sprites,small_font,font,&HUD);
                        disp_post_draw();
                        if(PAUSE==1)
                            redraw=0;
                        else
                            redraw=1;
                }
                
                /*Se apertar ESC fecha o jogo*/
                if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
                    done=1;
                break;

            /*Fecha o jogo se o player fechar o display do ALLEGRO*/
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = 1;
                break;
        }

        /*A cada 10 ciclos conta um segundo*/
        if(clock==10)
        {
            HUD.clock--;
            clock=0;
        }

        /*Se o tempo acabar o player morre*/
        if(HUD.clock==0)
            kill_player(&miner,miner.y,miner.x,matriz);/*Se o contador chegar a zero mata o player*/
        
        /*Tela de morte*/
        if(DEAD!=1 && !miner.alive) 
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_hud(&sprites,&HUD,font,small_font);
            draw_map(&sprites,matriz,&miner);
            player_died(&audios,font);
            disp_post_draw();
            DEAD=1;
            redraw=0;
        }        
        
        /*Tela de vitoria*/
        if(VICTORY!=1 && miner.won)
        {
            HUD.points+= HUD.clock;
            check_scores(&HUD);
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_hud(&sprites,&HUD,font,small_font);
            draw_map(&sprites,matriz,&miner);
            player_won(&audios,font,small_font,&HUD);
            disp_post_draw();
            redraw=0;
            VICTORY=1;
        }
        if(done)
            break;
        
        keyboard_update(&event,key);

        /*Reimprime tudo*/
        if(redraw && al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_hud(&sprites,&HUD,font,small_font);
            draw_map(&sprites,matriz,&miner);
            disp_post_draw();
            redraw = 0;
        }
    }

    
    
    audios_denit(&audios);
    sprites_denit(&sprites);
    disp_deinit();
    al_destroy_font(font);
    al_destroy_timer(fps_timer);
    al_destroy_timer(player_timer);
    al_destroy_timer(map_timer);
    al_destroy_timer(detect_fall_timer);

    al_destroy_event_queue(queue);

    return 0;
}