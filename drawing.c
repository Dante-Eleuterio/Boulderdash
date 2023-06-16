/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "drawing.h"

/*Percorre a matriz e imprime o sprite baseado no número da posição*/
void draw_map(SPRITES *sprites,int matriz[22][40],player* miner)
{
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
        {   
            switch (matriz[i][j])
            {
            case BEDROCK:
                al_draw_bitmap(sprites->bedrock, j*32, i*32+50, 0);
                break;
            case DIRT:
                al_draw_bitmap(sprites->dirt,    j*32, i*32+50, 0);
                break;
            case DIAMOND:
                al_draw_bitmap(sprites->diamond, j*32, i*32+50, 0);
                break;
            case FALLEN_DIAMOND:
                al_draw_bitmap(sprites->diamond, j*32, i*32+50, 0);
                break;
            case TO_FALL_DIAMOND:
                al_draw_bitmap(sprites->diamond, j*32, i*32+50, 0);
                break;
            case BOULDER:
                al_draw_bitmap(sprites->boulder, j*32, i*32+50, 0);
                break;
            case FALLEN_BOULDER:
                al_draw_bitmap(sprites->boulder, j*32, i*32+50, 0);
                break;
            case TO_FALL_BOULDER:
                al_draw_bitmap(sprites->boulder, j*32, i*32+50, 0);
                break;
            case TO_ROLL_BOULDER:
                al_draw_bitmap(sprites->boulder, j*32, i*32+50, 0);
                break;
            case BRICK:
                al_draw_bitmap(sprites->brick,   j*32, i*32+50, 0);
                break;
            case PLAYER_S:
                al_draw_bitmap(sprites->player_still, (miner->x)*32, (miner->y)*32+50,0);
                break;
            case PLAYER_R0:
                al_draw_bitmap(sprites->RIGHT_0, (miner->x)*32, (miner->y)*32+50,0);
                break;
            case PLAYER_R1:
                al_draw_bitmap(sprites->RIGHT_1, (miner->x)*32, (miner->y)*32+50,0);
                break;
            case PLAYER_L0:
                al_draw_bitmap(sprites->LEFT_0, (miner->x)*32, (miner->y)*32+50,0);
                break;
            case PLAYER_L1:
                al_draw_bitmap(sprites->LEFT_1, (miner->x)*32, (miner->y)*32+50,0);
                break;
            case CLOSED_EXIT:
                al_draw_bitmap(sprites->closed_exit, j*32, i*32+50, 0);
                break;
            case OPEN_EXIT:
                al_draw_bitmap(sprites->open_exit, j*32, i*32+50, 0);
                break;
            default:
                break;
            }
        }
}



/*Imprime a tela de ajuda */
void draw_help(SPRITES *sprites,ALLEGRO_FONT *small_font,ALLEGRO_FONT *font,hud *HUD)
{

    al_draw_textf(font,al_map_rgb(255, 255, 255),600,350,0,"PAUSE");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),0,42,0,"DIAMANTES NECESSARIOS PARA A SAIDA/");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),0,60,0,"VALOR DE CADA DIAMANTE");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),285,50,0,"DIAMANTES COLETADOS");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),960,50,0,"TEMPO");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),1120,50,0,"PONTOS");

    al_draw_textf(small_font,al_map_rgb(255, 255, 255),25,110,0,"Use as setas do teclado para direcionar o personagem evitando ser ");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),25,130,0,"esmagado enquanto coleta os diamantes. Ao coletar o numero ");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),25,150,0,"mínimo de diamantes vá para a saida");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),25,180,0,"Produzido por Dante Eleutério dos Santos -UFPR CURITIBA");
    
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),1215,512,0,"SAÍDA");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),1230,530,0,"|");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),1228,548,0,"V");
    al_draw_bitmap(sprites->closed_exit,1215,570,0);
    
    al_draw_textf(font,al_map_rgb(255, 255, 255),25,230,0,"High Scores");
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),180,250,0,"(Aperte R para resetar TODOS OS SCORES)");
    
    for (int i = 0; i < 10; i++)
    {
        al_draw_textf(small_font,al_map_rgb(255, 255, 255),25,280+i*30,0,"%d.",i+1);
        al_draw_textf(small_font,al_map_rgb(255, 255, 255),45,280+i*30,0,"%d",HUD->scores[i]);
    }
    
}

/*Escreve a pontuação no arquivo de high scores*/
void write_scores(hud *HUD)
{
    FILE *arq=fopen("Resources/high_scores.txt","w+");
    if (!arq)
    {
        perror("Erro");
        exit(1);
    }
    for (int i=0; i<10; i++)
        fprintf(arq,"%d\n",HUD->scores[i]);
    fclose(arq);
}

/*Confere se a pontuação é um novo high score*/
void check_scores(hud* HUD)
{
    for (int i = 0; i < 10; i++)
    {
        if(HUD->scores[i]<HUD->points)/*Se achou onde guardar,reorganiza o vetor, coloca o novo high score e chama a função para mudar o arquivo*/
        {
            for (int j = 9; j > i; j--)
            {
                HUD->scores[j]=HUD->scores[j-1];
            }
            HUD->scores[i]=HUD->points;
            write_scores(HUD);
            return;
        }    
    }
    
}

void reset_scores(hud *HUD)
{
    for (int i = 0; i < 10; i++)
        HUD->scores[i]=0;
    write_scores(HUD);
}
/*Lê o arquivo txt para pegar os high scores*/
void scan_scores(hud *HUD)
{
    FILE *arq =fopen( "Resources/high_scores.txt","r");
    if (!arq)
    {
        perror("Erro");
        exit(1);
    }
    for (int i=0; i<10; i++)
        fscanf(arq,"%d",&HUD->scores[i]);
    fclose(arq);
}

/*Inicializa o hud*/
void init_hud(hud *HUD)
{
    HUD->diamonds_required=12;
    HUD->diamonds_value=10;
    HUD->diamonds_caught=0;
    HUD->clock=150;
    HUD->points=0;
    scan_scores(HUD);
}

/*Imprime o hud*/
void draw_hud(SPRITES *sprites,hud *HUD,ALLEGRO_FONT *font,ALLEGRO_FONT *small_font)
{
    al_draw_textf(font,al_map_rgb(255, 255, 255),32,4,0,"%d",HUD->diamonds_required);
    al_draw_bitmap(sprites->diamond,64 ,16, 0);
    al_draw_textf(font,al_map_rgb(255, 255, 255),96,4,0,"%d",HUD->diamonds_value);
    al_draw_textf(font,al_map_rgb(255, 255, 255),285,4,0,"%d",HUD->diamonds_caught);
    al_draw_textf(small_font,al_map_rgb(255, 255, 255),400,25,0,"F1 OR H FOR HELP");
    al_draw_textf(font,al_map_rgb(255, 255, 255),960,4,0,"%d",HUD->clock);
    al_draw_textf(font,al_map_rgb(255, 255, 255),1120,4,0,"%d",HUD->points);
}

/*Imprime a tela de vitoria*/
void player_won(AUDIOS *audios,ALLEGRO_FONT *font,ALLEGRO_FONT *small_font,hud *HUD)
{
    al_play_sample(audios->victory_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_draw_textf(font,al_map_rgb(255, 255, 255),500,350,0,"CONGRATULATIONS! YOU WON");
    al_draw_textf(font,al_map_rgb(255, 255, 255),450,400,0,"PRESS ESC TO EXIT OR R TO RESTART");
    al_draw_textf(font,al_map_rgb(255, 255, 255),25,230,0,"High Scores");
    for (int i = 0; i < 10; i++)
    {
        al_draw_textf(small_font,al_map_rgb(255, 255, 255),25,280+i*30,0,"%d.",i+1);
        al_draw_textf(small_font,al_map_rgb(255, 255, 255),45,280+i*30,0,"%d",HUD->scores[i]);
    }
}

/*Imprime a tela de derrota*/
void player_died(AUDIOS *audios,ALLEGRO_FONT *font)
{
    al_play_sample(audios->death_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_play_sample(audios->boulder_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_draw_textf(font,al_map_rgb(255, 255, 255),600,350,0,"YOU DIED");
    al_draw_textf(font,al_map_rgb(255, 255, 255),450,400,0,"PRESS ESC TO EXIT OR R TO RESTART");
}

/*Reinicia o jogo e reinicializa tudo*/
void restart(hud *HUD,player *miner,int matriz[22][40],int *done,int *redraw,int *PAUSE,int *DEAD,int *VICTORY,int *clock)
{
    *done=0;
    *redraw=1;
    *clock=0;
    *PAUSE=-1;
    *DEAD=0;
    *VICTORY=0;
    init_hud(HUD);
    init_player(miner);
    scan_matrix(matriz);

}
