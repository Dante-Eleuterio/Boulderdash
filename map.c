/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/
#include "map.h"
/*Pega uma parte especifica do spritesheet*/
ALLEGRO_BITMAP* sprite_grab(SPRITES *sprites,int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites->sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}

/*Inicializa os sprites*/
void sprites_init(SPRITES *sprites)
{
    
    sprites->sheet = al_load_bitmap("Resources/Sprites/player.png");
    must_init(sprites->sheet, "spritesheet");

    sprites->boulder = al_load_bitmap("Resources/Sprites/boulder.png");
    must_init(sprites->boulder, "boulder");
    sprites->bedrock = al_load_bitmap("Resources/Sprites/bedrock.png");
    must_init(sprites->bedrock, "bedrock");
    sprites->dirt = al_load_bitmap("Resources/Sprites/dirt.png");
    must_init(sprites->dirt, "dirt");
    sprites->diamond = al_load_bitmap("Resources/Sprites/diamond.png");
    must_init(sprites->diamond, "diamond");
    sprites->diamond_font = al_load_bitmap("Resources/Sprites/diamond_font.png");
    must_init(sprites->diamond_font, "diamond_font");
    sprites->brick = al_load_bitmap("Resources/Sprites/brick.png");
    must_init(sprites->brick, "brick");
    sprites->creeper = al_load_bitmap("Resources/Sprites/creeper.png");
    must_init(sprites->creeper, "creeper");

    sprites->player_still=sprite_grab(sprites,193,257,32,32);
    must_init(sprites->player_still,"player standing");
    sprites->LEFT_0=sprite_grab(sprites,225,289,32,32);
    must_init(sprites->LEFT_0,"left walk 0");
    sprites->LEFT_1=sprite_grab(sprites,257,289,32,32);
    must_init(sprites->LEFT_1,"left walk 1");
    sprites->RIGHT_0=sprite_grab(sprites,225,321,32,32);
    must_init(sprites->RIGHT_0,"right walk 0");
    sprites->RIGHT_1=sprite_grab(sprites,257,321,32,32);
    must_init(sprites->RIGHT_1,"right walk 1");
    sprites->closed_exit=sprite_grab(sprites,128,0,32,32);
    must_init(sprites->closed_exit,"closed exit");
    sprites->open_exit=sprite_grab(sprites,224,0,32,32);
    must_init(sprites->open_exit,"open exit");
    
}


/*Destroi os sprites*/
void sprites_denit(SPRITES *sprites)
{
    al_destroy_bitmap(sprites->sheet);
    al_destroy_bitmap(sprites->boulder);
    al_destroy_bitmap(sprites->bedrock);
    al_destroy_bitmap(sprites->diamond);
    al_destroy_bitmap(sprites->diamond_font);
    al_destroy_bitmap(sprites->brick);
    al_destroy_bitmap(sprites->dirt);
    al_destroy_bitmap(sprites->player_still);
    al_destroy_bitmap(sprites->LEFT_0);
    al_destroy_bitmap(sprites->LEFT_1);
    al_destroy_bitmap(sprites->RIGHT_0);
    al_destroy_bitmap(sprites->RIGHT_1);
    al_destroy_bitmap(sprites->closed_exit);
    al_destroy_bitmap(sprites->open_exit);
    al_destroy_bitmap(sprites->creeper);
}
/*Inicializa os audios*/
void audios_init(AUDIOS *audios)
{
    audios->creeper_sound = al_load_sample("Resources/audios/creeper-explosion.wav");
    must_init(audios->creeper_sound,"creeper_sound");

    audios->death_sound = al_load_sample("Resources/audios/death_sound.wav");
    must_init(audios->death_sound, "death_sound");
    
    audios->diamond_sound = al_load_sample("Resources/audios/diamond_sound.wav");
    must_init(audios->diamond_sound, "diamond_sound");
    
    audios->boulder_sound = al_load_sample("Resources/audios/boulderslash_sound.wav");
    must_init(audios->boulder_sound, "boulder_sound");

    audios->victory_sound = al_load_sample("Resources/audios/victory_sound.wav");
    must_init(audios->victory_sound, "victory_sound");

    audios->door_sound= al_load_sample("Resources/audios/door_sound.wav");
    must_init(audios->door_sound,"door_sound");

}

/*Destroi os audios*/
void audios_denit(AUDIOS *audios)
{
    al_destroy_sample(audios->creeper_sound);
    al_destroy_sample(audios->death_sound);
    al_destroy_sample(audios->diamond_sound);
    al_destroy_sample(audios->boulder_sound);
    al_destroy_sample(audios->victory_sound);
    al_destroy_sample(audios->door_sound);

}

/*Inicializa a struct do player*/
void init_player(player *miner)
{
    miner->x=3;
    miner->y=2;
    miner->moving_animation=1;
    miner->alive=1;
    miner->won=0;
}

/*Marca o jogador como morto e explode os blocos em volta*/
void kill_player(player *miner,int y,int x,int matriz[22][40])
{
    miner->alive=0;
    y-=1;
    x-=1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if(matriz[y+i][x+j]!=BEDROCK)
                matriz[y+i][x+j]=EMPTY;
}

/*Confere se a posição da matriz é o jogador*/
int is_player(int x)
{
    if (x==PLAYER_S || x==PLAYER_L0 || x==-PLAYER_L1 || x==PLAYER_R0 || x==PLAYER_R1)
        return 1;
    else
        return 0;
}

/*Efetua a rolagem para o lado dos diamantes*/
void diamond_roll(int matriz[22][40],SPRITES *sprites,player *miner,int i,int j)
{
    if(matriz[i][j+1]==EMPTY && matriz[i+1][j+1]==EMPTY)
        {
            matriz[i][j]=EMPTY;
            matriz[i][j+1]=FALLEN_DIAMOND;
        }
        else
        if(matriz[i][j-1]==EMPTY && matriz[i+1][j-1]==EMPTY)
        {
            matriz[i][j]=EMPTY;
            matriz[i][j-1]=FALLEN_DIAMOND;
        }
        else
            matriz[i][j]=DIAMOND;
}

/*Atualiza a posição dos diamantes*/
void diamond_update(int matriz[22][40],SPRITES *sprites,player *miner)
{
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if (matriz[i][j]==FALLEN_DIAMOND)
                matriz[i][j]=TO_FALL_DIAMOND;

    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if (matriz[i][j]==TO_FALL_DIAMOND || matriz[i][j]==TO_ROLL_DIAMOND)
            {
                if (matriz[i+1][j]==EMPTY)
                {
                    matriz[i][j]=EMPTY;
                    matriz[i+1][j]=FALLEN_DIAMOND;
                }
                else
                {
                    if(matriz[i][j]==TO_ROLL_DIAMOND)
                        diamond_roll(matriz,sprites,miner,i,j);
                    else
                        matriz[i][j]=DIAMOND;
                    if(is_player(matriz[i+1][j]))
                        kill_player(miner,i+1,j,matriz);
                }
            }
}

/*Efetua a rolagem para o lado das pedras*/
void boulder_roll(int matriz[22][40],SPRITES *sprites,player *miner,int i, int j)
{    
        if(matriz[i][j+1]==EMPTY && matriz[i+1][j+1]==EMPTY)
        {
            matriz[i][j]=EMPTY;
            matriz[i][j+1]=FALLEN_BOULDER;
        }
        else
        if(matriz[i][j-1]==EMPTY && matriz[i+1][j-1]==EMPTY)
        {
            matriz[i][j]=EMPTY;
            matriz[i][j-1]=FALLEN_BOULDER;
        }
        else
            matriz[i][j]=BOULDER;
}

/*Atualiza a posição das pedras*/
void boulder_update(int matriz[22][40],SPRITES *sprites,player *miner)
{
    /*Se for uma pedra que está em processo de queda, a marca para cair mais uma vez*/
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if(matriz[i][j]==FALLEN_BOULDER)
                matriz[i][j]=TO_FALL_BOULDER;
                    
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if (matriz[i][j]==TO_FALL_BOULDER || matriz[i][j]==TO_ROLL_BOULDER) /*Se for uma pedra marcada para cair ou para rolar a atualiza*/
            {
                if (matriz[i+1][j]==EMPTY)
                {
                    matriz[i][j]=EMPTY;
                    matriz[i+1][j]=FALLEN_BOULDER; /*Se houver espaço, a pedra cai reta e marca como caida*/
                }
                else
                {
                    if(matriz[i][j]==TO_ROLL_BOULDER)
                        boulder_roll(matriz,sprites,miner,i,j);/*Rola a pedra*/
                    else
                        matriz[i][j]=BOULDER;/*Se timer terminado de cair e não puder rolar, volta a ser apenas uma pedra*/
                    if(is_player(matriz[i+1][j]))
                        kill_player(miner,i+1,j,matriz); /*Se o espaço que for cair tiver o player, o mata*/
                }
            }
}                    

/*Confere se a pedra ou o diamante podem rolar*/
int check_roll(int matriz[22][40],SPRITES *sprites,player *miner,int i,int j)
{
    if(matriz[i+1][j]==BOULDER || matriz[i+1][j]==DIAMOND) 
            if(matriz[i-1][j]!=TO_ROLL_BOULDER && matriz[i-1][j]!=TO_ROLL_DIAMOND)
                if((matriz[i][j+1]==EMPTY && matriz[i+1][j+1]==EMPTY) || (matriz[i][j-1]==EMPTY && matriz[i+1][j-1]==EMPTY))
                    return 1;
    return 0;
}

/*Detecta e marca a pedra ou diamante a ser rolada da vez*/
void detect_roll(int matriz[22][40],SPRITES *sprites,player *miner)
{
    int rolled=0;
    
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if(matriz[i][j]==TO_ROLL_BOULDER || matriz[i][j]==TO_ROLL_DIAMOND)
                rolled=1; /*Se ja tiver uma pedra ou diamante a rolar não rola outro*/
    
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if(rolled==0 && matriz[i][j]==BOULDER && check_roll(matriz,sprites,miner,i,j))
            {
                matriz[i][j]=TO_ROLL_BOULDER; /*Marca a pedra para rolar*/
                rolled=1;;
            }
            else
            if(rolled==0 && matriz[i][j]==DIAMOND && check_roll(matriz,sprites,miner,i,j))
            {
                matriz[i][j]=TO_ROLL_DIAMOND; /*Marca o diamante para rolar*/
                rolled=1;
            }
}

/*Detecta as pedras e diamantes a serem marcadas para cair*/
void detect_fall(int matriz[22][40],SPRITES *sprites,player *miner)
{
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if(matriz[i][j]==BOULDER)
                if(matriz[i+1][j]==EMPTY || matriz[i+1][j]==FALLEN_BOULDER || matriz[i+1][j]==FALLEN_DIAMOND)
                    matriz[i][j]=TO_FALL_BOULDER; /*Marca a pedra para cair*/
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if(matriz[i][j]==DIAMOND)
                if(matriz[i+1][j]==EMPTY || matriz[i+1][j]==FALLEN_BOULDER || matriz[i+1][j]==FALLEN_DIAMOND)
                    matriz[i][j]=TO_FALL_DIAMOND; /*Marca o diamante para cair*/
}   

/*Muda o sprite da saída e toca um som de porta se abrindo*/
void open_exit(int matriz[22][40],SPRITES *sprites,hud *HUD,AUDIOS *audios)
{
    for (int i = 0; i < 22; i++)
        for(int j=0;j<40;j++)
            if(matriz[i][j]==CLOSED_EXIT)
            {
                matriz[i][j]=OPEN_EXIT;
                al_play_sample(audios->door_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
}

/*Chama as funções para atualizar os sprites do mapa*/
void map_update(int matriz[22][40],SPRITES *sprites,player *miner,hud *HUD,AUDIOS *audios)
{
    if(HUD->diamonds_caught>=HUD->diamonds_required) /*Se a cota de diamantes foi atingida,abre a saida*/
    {
        HUD->diamonds_value=15;
        open_exit(matriz,sprites,HUD,audios);
    }
    detect_roll(matriz,sprites,miner);
    boulder_update(matriz,sprites,miner);
    diamond_update(matriz,sprites,miner);
}

/*Confere se o movimento desejado do player é válido*/
int check_movement(int matriz[22][40],player *miner,int x,int y)
{
    switch (matriz[miner->y+y][miner->x+x])
    {
        case BEDROCK:
            return 0;
            break;
        case BRICK:
            return 0;
            break;
        case BOULDER:
            return 0;
            break;
        case FALLEN_BOULDER:
            return 0;
            break;
        case TO_FALL_BOULDER:
            return 0;
            break;
        case TO_ROLL_BOULDER:
            return 0;
            break;
        case FALLEN_DIAMOND:
            return 0;
            break;
        case TO_FALL_DIAMOND:
            return 0;
            break;
        case CLOSED_EXIT:
            return 0;
            break;
        default:
            return 1;
            break;
    }
}

/*Atualiza a posição do player com base no imput do teclado*/
void player_update(int matriz[22][40],SPRITES *sprites,unsigned char key[ALLEGRO_KEY_MAX],player *miner,hud *HUD,AUDIOS *audios)
{
    int old_diamonds=HUD->diamonds_caught;/*Salva a quantidade atual de diamantes coletados para comparação futura*/
    
    if(key[ALLEGRO_KEY_UP] && check_movement(matriz,miner,0,-1))
    {
        miner->y-=1;
        if(matriz[miner->y][miner->x]==OPEN_EXIT)/*Se chegou à saida,venceu o jogo*/
            miner->won=1;
        if(matriz[miner->y][miner->x]==DIAMOND)/*Coleta o diamante*/
            HUD->diamonds_caught+=1;
        matriz[miner->y+1][miner->x]=EMPTY;    
        matriz[miner->y][miner->x]=PLAYER_S;    /*Move o player*/
    
    }
    else
    if(key[ALLEGRO_KEY_DOWN] && check_movement(matriz,miner,0,1))
    {
        miner->y+=1;
        if(matriz[miner->y][miner->x]==OPEN_EXIT) /*Se chegou à saida,venceu o jogo*/
            miner->won=1;
        if(matriz[miner->y][miner->x]==DIAMOND) /*Coleta o diamante*/
            HUD->diamonds_caught+=1;
        matriz[miner->y-1][miner->x]=EMPTY;    
        matriz[miner->y][miner->x]=PLAYER_S;      /*Move o player*/
    }
    else
    if(key[ALLEGRO_KEY_LEFT])
    {
        matriz[miner->y][miner->x]=PLAYER_L0*miner->moving_animation; /*Permite a animação de movimento mesmo que o player fique correndo parado*/   
        if(matriz[miner->y][miner->x-1]==BOULDER) /*Confere se é pedra para empurrar*/
            if(matriz[miner->y][miner->x-2]==EMPTY)
            {
                matriz[miner->y][miner->x-1]=EMPTY;
                if(matriz[miner->y+1][miner->x-2]==EMPTY)
                    matriz[miner->y][miner->x-2]=TO_FALL_BOULDER;
                else
                    matriz[miner->y][miner->x-2]=BOULDER;
            }

        if(check_movement(matriz,miner,-1,0)) /*Confere se a casa é válida*/
        {
            miner->x-=1;
            if(matriz[miner->y][miner->x]==OPEN_EXIT) /*Se chegou à saida,venceu o jogo*/
                miner->won=1;
            if(matriz[miner->y][miner->x]==DIAMOND) /*Coleta o diamante*/
                HUD->diamonds_caught+=1;
            matriz[miner->y][miner->x+1]=EMPTY;    
            matriz[miner->y][miner->x]=PLAYER_L0*miner->moving_animation;   /*Move o player*/    
        }
        miner->moving_animation*=-1; /*Atualiza a animação*/
    }
    else
    if(key[ALLEGRO_KEY_RIGHT])
    {
        matriz[miner->y][miner->x]=PLAYER_R0*miner->moving_animation;  /*Permite a animação de movimento mesmo que o player fique correndo parado*/  
        if(matriz[miner->y][miner->x+1]==BOULDER)
            if(matriz[miner->y][miner->x+2]==EMPTY)
            {
                matriz[miner->y][miner->x+1]=EMPTY;
                if(matriz[miner->y+1][miner->x+2]==EMPTY)
                    matriz[miner->y][miner->x+2]=TO_FALL_BOULDER;
                else
                    matriz[miner->y][miner->x+2]=BOULDER;
            }
        if(check_movement(matriz,miner,1,0))
        {
            miner->x+=1;
            if(matriz[miner->y][miner->x]==OPEN_EXIT) /*Se chegou à saida,venceu o jogo*/
                miner->won=1;
            if(matriz[miner->y][miner->x]==DIAMOND)/*Coleta o diamante*/
                HUD->diamonds_caught+=1;
            matriz[miner->y][miner->x-1]=EMPTY;    
            matriz[miner->y][miner->x]=PLAYER_R0*miner->moving_animation;      /*Move o player*/
        }
        miner->moving_animation*=-1; /*Atualiza a animação*/
    }
    else
        matriz[miner->y][miner->x]=PLAYER_S;    /*Mantem o player parado*/

    if(old_diamonds<HUD->diamonds_caught)
    {
        al_play_sample(audios->diamond_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); /*Confere se um diamante foi coletado e toca o som*/
        HUD->points+= HUD->diamonds_value;
    }

}

