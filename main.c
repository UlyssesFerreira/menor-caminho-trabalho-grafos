#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include "biblioteca.c"

#define VERTICES 11

int main(){

    setlocale(LC_ALL, "Portuguese");

    int i, opcao, origem, destino, *custos=NULL;

//iniciar matriz de custos
    if (!custos)
        free(custos);
    custos=(int *) malloc(sizeof(int)*VERTICES*VERTICES);
    for (i=0;i<=VERTICES*VERTICES;i++)
    {
        custos[i]=-1;
    }

    preencheMatriz(custos);

    do
    {
        opcao = menu();

        switch(opcao)
        {
            case 1:

                tabelaCidades();
                printf("\nDigite o N° da cidade de origem e do destino\n");
                do
                {
                  printf("Cidade origem (entre 1 e %d): ",VERTICES);
                  scanf("%d",&origem);
                }while (origem<1 || origem>VERTICES);

                do
                {
                  printf("Cidade destino (entre 1 e %d, exceto %d): ",VERTICES,origem);
                  scanf("%d",&destino);
                }while (destino<1 || destino>VERTICES || destino==origem);

                dijkstra(VERTICES,origem,destino,custos);

                break;

            case 0:
                opcao = 0;
                break;

            default:
                printf("Digite uma opção válida!!!\n\n");
                break;
        }
    }while (opcao!=0);

    printf("\nEncerrando programa...\n\n");
    return 0;
}
