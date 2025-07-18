#include <stdio.h>
#include <math.h>
#include "biblioteca.h"

#define MAXVERTICES 100
#define VERTICES 11

int menu()
{
    int opcao;

    printf("================MENU================\n");
    printf("Escolha sua op��o:\n");
    printf("     1. Realizar consulta de rota\n");
    printf("     2. Ver fronteiras\n");
    printf("     0. Sair do programa\n");
    printf("-----------------------------------\n");
    printf("Op��o: ");
    scanf("%d", &opcao);
    printf("-----------------------------------\n");

    return opcao;
}

void tabelaCidades()
{
    printf("\nCidade\t\t\t\t|N�\n");
    printf("--------------------------------|--\n");
    printf("Casa Branca\t\t\t| 1\n");
    printf("Vargem G. do Sul\t\t| 2\n");
    printf("Agua�\t\t\t\t| 3\n");
    printf("S�o Jo�o da Boa Vista\t\t| 4\n");
    printf("�guas da Prata\t\t\t| 5\n");
    printf("Po�os de Calda\t\t\t| 6\n");
    printf("Andradas\t\t\t| 7\n");
    printf("Santo Ant�nio do Jardim\t\t| 8\n");
    printf("Esp�rito Santo do Pinhal\t| 9\n");
    printf("Mogi Gua�u\t\t\t|10\n");
    printf("Estiva Gerbi\t\t\t|11\n");
}

void preencheMatriz(int *custos, FILE *arq)
{
    int i;

    arq = fopen("grafo.txt", "rt");
    int num;
    for (i=0;i<=VERTICES*VERTICES;i++)
    {
        fscanf(arq, "%d", &num);
        custos[i] = num;
    }
}


void mostraFonteiras(int m[VERTICES][VERTICES], FILE *arq)
{
    arq = fopen("grafo.txt", "rt");
    int i, j, num;

    for(i=0; i<VERTICES;i++)
    {
        for(j=0; j<VERTICES;j++)
        {
            fscanf(arq, "%d", &num);
            m[i][j] = num;
        }
    }

    for(i=0; i<VERTICES;i++)
    {
        for(j=0; j<VERTICES;j++)
        {
            if(m[i][j] != -1)
            {
                printf("A cidade %d tem fronteira com a cidade %d.\n", i+1, j+1);
            }
        }
        printf("\n");
    }
}


void dijkstra(int vertices,int origem,int destino,int *custos)
{
    int i,v,
        ant[MAXVERTICES],
        z[MAXVERTICES],
        caminho[VERTICES];

    int c;

    double min,
           dist[MAXVERTICES];



    for(i=0;i<VERTICES;i++)
    {
        caminho[i] = 0;
    }



    for (i=0;i<vertices;i++)
    {
        if(custos[(origem-1)*vertices+i]!=-1)
        {
            ant[i]=origem-1;
            dist[i]=custos[(origem-1)*vertices+i];
        }
        else
        {
            ant[i]=-1;
            dist[i]=HUGE_VAL;
        }
        z[i]=0;
    }
    z[origem-1]=1;
    dist[origem-1]=0;

    do
    {
        /* Encontrando o v�rtice que deve entrar em z */
        min=HUGE_VAL;
        for(i=0;i<vertices;i++)
          if(!z[i])
            if(dist[i]>=0 && dist[i]<min)
            {
                min=dist[i];
                v=i;
            }

        /* Calculando as dist�ncias dos novos vizinhos de z */

        if (min!=HUGE_VAL && v!=destino-1)
        {
            z[v]=1;
            for (i=0;i<vertices;i++)
            if (!z[i])
            {
                if (custos[v*vertices+i]!=-1 && dist[v]+custos[v*vertices+i]<dist[i])
                {
                    dist[i]=dist[v]+custos[v*vertices+i];
                    ant[i]=v;
                }
            }
        }
    }while (v!=destino-1 && min!=HUGE_VAL);


    if (min==HUGE_VAL)
        printf("\nNo digrafo dado n�o existe caminho entre os v�rtices %d e %d !!\n",origem,destino);
    else
    {
        printf("\nO melhor caminho para ir da cidade %d at� a cidade %d �: \n",
            origem,destino);

        c = 0;
        i=destino;

        caminho[c] = i;
        i=ant[i-1];
        while (i!=-1)
        {
            c++;
            caminho[c] = i+1;
            i=ant[i];
        }

        for(i=c;i>=0;i--)
        {
            if(i == 0)
                printf("%d", caminho[i]);
            else
                printf("%d=>", caminho[i]);
        }

        printf("\n\nO dist�ncia deste trajeto �: %d Km.\n",(int) dist[destino-1]);
    }

}
