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
#include "pilha.c"

void menu()
{
	printf("1 - Iniciar partida;\n");
	printf("2 - Gerar novo arquivo rouba-monte.txt;\n");
	printf("3 - SAIR;\n");
}

int outrosMontes(int qtdJogadores, PILHA *jogador, int mao, int jAtual)
{
    int j;
	for(j = 0; j < qtdJogadores; j++)
	{
		if(jAtual != j)
		{
			//Consultar no monte dos outros
			if(mao == getTopItem(&jogador[j]))
			{
				//printf("\tPegou monte do jogador %d\n", j+1);
				pegarMonte(&jogador[j]);
				push(&jogador[jAtual], mao);
				return 1;
				break;
			}
		}
	}
	return 0;
}

int meuMonte(PILHA *jogador, int mao, int jAtual)
{
	//Consultar com meu monte;
	if(mao == getTopItem(&jogador[jAtual]))
	{
		//printf("\tInseriu no proprio monte\n");
		push(&jogador[jAtual], mao);
		return 1;
	}
	return 0;
}

int noDescarte(int *descarte, PILHA *jogador, int mao, int jAtual)
{
    int j;
	//Consultar no discarte
	for(j = 1; j <= descarte[0]; j++)
	{
		if(mao == descarte[j])
		{
			//printf("\tPegou do descarte\n");
			push(&jogador[jAtual], mao);
			descarte[j] = 0;
			return 1;
			break;
		}
	}
	return 0;
}

int prox(int achou, int *descarte, int mao, int qtdJogadores, PILHA *monte, int jAtual)
{
    if(achou == 0)
    {
        descarte[descarte[0]+1] = mao;
        descarte[0] = descarte[0] + 1;
        //printf("\tDescartou a mao: descarte[%d] = %d;\n", 0, descarte[0]);
        if(getTopo(&monte) != 0)
        {
            //printf("\t%d = %d\n", i, qtdJogadores-1);
            if(jAtual >= qtdJogadores-1)
                jAtual = 0;
            else
                jAtual++;
        }
    }
    else
    {
        //printf("\tAchou\n");
        if(getTopo(&monte) != 0)
        {
            jAtual=jAtual;
        }
    }
    return jAtual;
}

int vencedor(int qtdJogadores, PILHA *jogador)
{
    int ganhador = 0, i;
    for(i=0; i < qtdJogadores; i++)
    {
        if(getTopo(&jogador[ganhador]) < getTopo(&jogador[i]))
            ganhador = i;
    }
    return ganhador;
}
int main()
{
    int cartas, qtdJogadores, itens[TAMPILHA], jAtual, i, j, k, mao, achou, descarte[TAMPILHA+1];

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

    setTopo(&monte);
    //monte.topo = 0;

    for(i=0; i<cartas; i++)
    {
        fscanf (Arquivo, "%d", &itens[i]);
    }

    fclose (Arquivo);

    for(i=0; i<qtdJogadores; i++)
    {
        setTopo(&jogador[i].topo);
        //jogador[i].topo = 0;
    }

    for(i=0; i<cartas; i++)
    {
        printf(" %d ", itens[i] );
        //push(&monte, itens[i]); // coloca cartas na pilha monte
    }

    for(i=cartas-1; i>=0; i--)
    {
        //printf(" %d ", itens[i] );
        push(&monte, itens[i]); // coloca cartas na pilha monte
    }
    printf("\n---------------------\n");
    jAtual = 0;
    int repet = 1;
    while(repet)
    {
        mao = pop(&monte);

        achou = 0;

        achou = outrosMontes(qtdJogadores, jogador, mao, jAtual);

        if(achou != 1)
            achou = meuMonte(jogador, mao, jAtual);

        if(achou != 1)
            achou = noDescarte(descarte, jogador, mao, jAtual);

        jAtual = prox(achou, descarte, mao, qtdJogadores, &monte, jAtual);

        if(getTopo(&monte) == 0)
            repet = 0;
    }

    printf("Ganhador jogador %d", vencedor(qtdJogadores, &jogador)+1);
    /*
    int ganhador = 0;
    for(i=0; i < qtdJogadores; i++)
    {
        printf("Monte jogador[%d] = %d\n", i+1, getTopo(&jogador[i]));
        if(getTopo(&jogador[ganhador]) < getTopo(&jogador[i]))
            ganhador = i;
    }
    printf("---------------------\n");
    printf("Ganhador jogador %d", ganhador+1);
    */
    //system("pause");
    return 0;
}

/**
 * Sortear uma carta ou seja um numero de 1 a 13;
 */
int carta(void)
{
    int carta = rand() % 14;

    if(carta == 0)
    {
        carta++;
    }
    return carta;
}
