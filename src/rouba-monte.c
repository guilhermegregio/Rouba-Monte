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
void pegarMonte(PILHA *ps);
int getTopItem(PILHA *ps);

int main()
{
    int cartas, qtdJogadores, itens[TAMPILHA], i, j, k, mao, achou, descarte[TAMPILHA+1];

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
    fscanf (Arquivo, "%d", &qtdJogadores); // leitura da quantidade de jogadores
    printf("Nr de jogadores: %d\n", qtdJogadores);
    printf("Nr de cartas: %d\n", cartas);
    printf("---------------------\n");

    PILHA jogador[qtdJogadores];
    PILHA monte;



    for(i=0; i<TAMPILHA+1; i++)
    {
        descarte[i] = 0;
    }

    monte.topo = 0;

    for(i=0; i<cartas; i++)
    {
        fscanf (Arquivo, "%d", &itens[i]);
    }

    fclose (Arquivo);

    for(i=0; i<qtdJogadores; i++)
    {
        jogador[i].topo = 0;
    }

    for(i=cartas-1; i>=0; i--)
    {
        printf(" %d ", itens[i] );
        push(&monte, itens[i]); // coloca cartas na pilha monte
    }
    printf("\n---------------------\n");
    i = 0;
    int repet = 1;
    while(repet)
    {
        //printf("Jogador: %d\n", i+1);
        mao = pop(&monte);
        //printf("\tMao: %d\n", mao);
        achou = 0;
        for(j = 0; j < qtdJogadores; j++)
        {
            if(i != j)
            {
                //Consultar no monte dos outros
                if(mao == getTopItem(&jogador[j]))
                {
                    //printf("\tPegou monte do jogador %d\n", j+1);
                    pegarMonte(&jogador[j]);
                    push(&jogador[i], mao);
                    achou = 1;
                    break;
                }
            }
        }

        if(achou != 1)
        {
            //Consultar com meu monte;
            if(mao == getTopItem(&jogador[i]))
            {
                //printf("\tInseriu no proprio monte\n");
                push(&jogador[i], mao);
                achou = 1;
            }
        }

        if(achou != 1)
        {
            //Consultar no discarte
            for(j = 1; j <= descarte[0]; j++)
            {
                if(mao == descarte[j])
                {
                    //printf("\tPegou do descarte\n");
                    push(&jogador[i], mao);
                    descarte[j] = 0;
                    achou = 1;
                    break;
                }
            }
        }

        if(achou == 0)
        {
            descarte[descarte[0]+1] = mao;
            descarte[0] = descarte[0] + 1;
            //printf("\tDescartou a mao: descarte[%d] = %d;\n", 0, descarte[0]);
            if(monte.topo != 0)
            {
                //printf("\t%d = %d\n", i, qtdJogadores-1);
                if(i >= qtdJogadores-1)
                    i = 0;
                else
                    i++;
            }
        }
        else
        {
            //printf("\tAchou\n");
            if(monte.topo != 0)
            {
                i=i;
            }
        }

        if(monte.topo == 0)
        {
            repet = 0;
        }
    }

    int ganhador = 0;
    for(i=0; i < qtdJogadores; i++)
    {
        printf("Monte jogador[%d] = %d\n", i+1, jogador[i].topo);
        if(jogador[ganhador].topo < jogador[i].topo)
            ganhador = i;
    }
    printf("---------------------\n");
    printf("Ganhador jogador %d", ganhador+1);

    //system("pause");
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

void pegarMonte(PILHA *ps)
{
    ps->topo = 0;
}

int getTopItem(PILHA *ps)
{
    if(ps->topo > 0)
    {
        return ps->cartas[ps->topo-1];
    }
    return -1;
}
