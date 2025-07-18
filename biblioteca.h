#define VERTICES 11

int menu();
void tabelaCidades();
void preencheMatriz(int *custos, FILE *arq);
void mostraFonteiras(int m[VERTICES][VERTICES], FILE *arq);
void dijkstra(int vertices,int origem,int destino,int *custos);
