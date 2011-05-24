/**
 * Grupo:       G4
 * Projeto:     Rouba Monte
 * Integrantes: "Allan Cezar Geraldo" <1011086@sumare.edu.br>,
 *              "Guilherme Mangabeira Gregio" <1012466@sumare.edu.br>
 *              "Marcio Barbosa de Melo" <1012689@sumare.edu.br>,
 *              "Matheus Borba Cezar" <1011022@sumare.edu.br>,
 *              "Rafael Antonio Lucio" <1010671@sumare.edu.br>,
**/
#include<stdio.h>
#include<stdlib.h>
#define TAMPILHA 52

typedef struct {
    int topo;
    int cartas[TAMPILHA];
} PILHA;

void push(PILHA *ps, int x);
int pop(PILHA *ps); //*ps=ponteiro para a estrutura da pilha

int main()
{
    int cartas, jogadoresMax, itens[TAMPILHA], i, j, k;

    FILE * Arquivo;
    Arquivo = fopen ("roubaMonte.txt","r"); // Abre arquivo de texto com parâmetros

    if (Arquivo==NULL) // Se arquivo não existir criar
    {
        Arquivo = fopen ("roubaMonte.txt","w"); // Cria arquivo
        fprintf (Arquivo, "%d %d\n", 6, 3);
        fprintf (Arquivo, "%d %d %d %d %d %d\n", 1, 10, 2, 3, 3, 5);
        fclose (Arquivo);
        Arquivo = fopen ("roubaMonte.txt","r"); // Abre arquivo de texto com parâmetros
    }


    fscanf (Arquivo, "%d", &cartas); // leitura do número de cartas
    fscanf (Arquivo, "%d", &jogadoresMax); // leitura da quantidade de jogadores
    printf("Nr de jogadores: %d\n", jogadoresMax);
    printf("Nr de cartas: %d\n", cartas);
    printf("---------------------\n");

    PILHA jogadores[jogadoresMax];
    PILHA monte;

    monte.topo=0;

    for(i=0; i<cartas; i++)
    {
        fscanf (Arquivo, "%d", &itens[i]);
    }

    fclose (Arquivo);

    for(i=0; i<jogadoresMax; i++)
    {
        printf("Jogador %d\n", i);
    }

    for(i=cartas-1; i>=0; i--)
    {
        push(&monte, itens[i]); // coloca cartas na pilha monte
    }

    i = 0;
    while(monte.topo)
    {
        for(j = 0; j < jogadoresMax; j++)
        {
            printf("\nJogador %d:\n", j);
            for(k = 0; k < jogadoresMax; k++)
            {
                if(k != j)
                    printf("Comparar carta com topo do jogador %d\n", k);
            }
        }
        printf("Ordem: %d\tCarta: %d\n", i+1, pop(&monte)); // retira cartas da pilha
        i++;
    }

    system("pause");
    return 0;
}

void push(PILHA *ps, int x)
{
    if (ps->topo > TAMPILHA) {
        printf("Pilha Cheia\n");
        system("pause");
        exit(1);
    } else
        ps->cartas[ps->topo++] = x;
}


int pop(PILHA *ps)
{
    if (ps->topo <= 0) {
        printf("Pilha vazia\n");
        system("pause");
        exit(1);
    } else
        return ps->cartas[--ps->topo];
}



