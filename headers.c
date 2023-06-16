/*Dante Eleutério dos Santos GRR20206686 UFPR Curitiba*/

#include "headers.h"

/*Função para conferir se o objeto foi devidamente inicializado*/
void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

/*Le o arquivo txt com a matriz do mapa*/
void scan_matrix(int matriz[22][40])
{
    int x;
    int i=0;
    int j=0;
    FILE * arq;
    arq =fopen( "Resources/matriz.txt","r");
    if (!arq)
    {
        perror("Erro");
        exit(1);
    }
        
    for(int k=0;k<880;k++)
    {
        fscanf(arq,"%d",&x);
        matriz[i][j]=x;
        j++;
        if(j==40)
        {
            j=0;
            i++;
        }
    }
    fclose(arq);
}
