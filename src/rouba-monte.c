/**
 * Grupo:       G4
 * Projeto:     Rouba Monte
 * Integrantes: "Alexandre de Andrade" <0921358@sumare.edu.br>,
 *              "Allan Cezar Geraldo" <1011086@sumare.edu.br>,
 *              "Guilherme Mangabeira Gregio" <1012466@sumare.edu.br>
 *              "Marcio Barbosa de Melo" <1012689@sumare.edu.br>,
 *              "Matheus Borba Cezar" <1011022@sumare.edu.br>,
 *              "Rafael Antonio Lucio" <1010671@sumare.edu.br>,
 *				"Rogerio Benicio dos Santos" <1012478@sumare.edu.br>
**/

#include<stdio.h>
#include<stdlib.h>
#include "pilha.c"
///-------------------------------------------------------------------------------------------
void pause()
{
    fflush(stdin);
    printf("\n\nPressione enter para continuar");
    scanf("%*c");
}
///-------------------------------------------------------------------------------------------
void menu()
{
    clear();
	printf("1 - Iniciar partida;\n");
	printf("2 - Gerar novo arquivo rouba-monte.txt;\n");
	printf("3 - Creditos;\n");
	printf("4 - SAIR;\n");
}
///-------------------------------------------------------------------------------------------
void creditos()
{
    clear();
    printf("Alexandre de Andrade <0921358@sumare.edu.br>;\n");
    printf("Allan Cezar Geraldo <1011086@sumare.edu.br>;\n");
    printf("Guilherme Mangabeira Gregio <1012466@sumare.edu.br>;\n");
    printf("Marcio Barbosa de Melo <1012689@sumare.edu.br>;\n");
    printf("Matheus Borba Cezar <1011022@sumare.edu.br>;\n");
    printf("Rafael Antonio Lucio <1010671@sumare.edu.br>;\n");
    printf("Rogerio Benicio dos Santos <1012478@sumare.edu.br>;\n");
}
///-------------------------------------------------------------------------------------------
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
				pegarMonte(&jogador[j]);
				push(&jogador[jAtual], mao);
				return 1;
				break;
			}
		}
	}
	return 0;
}
///-------------------------------------------------------------------------------------------
int meuMonte(PILHA *jogador, int mao, int jAtual)
{
	//Consultar com meu monte;
	if(mao == getTopItem(&jogador[jAtual]))
	{
		push(&jogador[jAtual], mao);
		return 1;
	}
	return 0;
}
///-------------------------------------------------------------------------------------------
int noDescarte(int *descarte, PILHA *jogador, int mao, int jAtual)
{
    int j;
	//Consultar no discarte
	for(j = 1; j <= descarte[0]; j++)
	{
		if(mao == descarte[j])
		{
			push(&jogador[jAtual], mao);
			descarte[j] = 0;
			return 1;
			break;
		}
	}
	return 0;
}
///-------------------------------------------------------------------------------------------
int prox(int achou, int *descarte, int mao, int qtdJogadores, PILHA *monte, int jAtual)
{
    if(achou == 0)
    {
        descarte[descarte[0]+1] = mao;
        descarte[0] = descarte[0] + 1;
        if(getTopo(&monte) != 0)
        {
            if(jAtual >= qtdJogadores-1)
                jAtual = 0;
            else
                jAtual++;
        }
    }
    else
    {
        if(getTopo(&monte) != 0)
        {
            jAtual=jAtual;
        }
    }
    return jAtual;
}
///-------------------------------------------------------------------------------------------
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
///-------------------------------------------------------------------------------------------
/**
 * Sortear uma carta ou seja um numero de 1 a 13;
 */
int carta(void)
{
    int carta = rand() % 14;
    if(carta == 0)
        carta++;
    return carta;
}
///-------------------------------------------------------------------------------------------
void inicio()
{
    clear();
    //Declaração das variaveis do tipo int
    int cartas,
        qtdJogadores,
        itens[TAMPILHA],
        i,
        j,
        k,
        mao,
        achou,
        descarte[TAMPILHA+1],
        repet = 1,
        jAtual = 0,
        opt;
    FILE * Arquivo;
    PILHA monte;

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

    for(i=0; i<TAMPILHA+1; i++) /// Definir os itens do vetor descarte para zero; ------------
        descarte[i] = 0;

    setTopo(&monte); /// Zerar o topo

    for(i=0; i<cartas; i++) /// Inserir valores do arquivo para o vetor itens; ---------------
        fscanf(Arquivo, "%d", &itens[i]);

    fclose(Arquivo);

    for(i=0; i<qtdJogadores; i++) /// Zerar o topo de todas as pilhas dos jogadores ----------
        setTopo(&jogador[i].topo);

    for(i=cartas-1; i>=0; i--) /// Coloca cartas na pilha monte ------------------------------
        push(&monte, itens[i]);

    for(i=0; i<cartas; i++) /// Imprimir as cartas -------------------------------------------
        printf(" %d ", itens[i] );

    printf("\n---------------------\n");

    while(repet)
    {
        mao = pop(&monte);
        achou = 0;
        /// Verifica o monte dos outros jogadores -------------------------------------------
        achou = outrosMontes(qtdJogadores, jogador, mao, jAtual);
        if(achou != 1) /// Verifica o proprio monte -----------------------------------------
            achou = meuMonte(jogador, mao, jAtual);
        if(achou != 1) /// Verifica o descarte ----------------------------------------------
            achou = noDescarte(descarte, jogador, mao, jAtual);
        /// Retorna quem ira jogar a prox.  -------------------------------------------------
        jAtual = prox(achou, descarte, mao, qtdJogadores, &monte, jAtual);
        ///Verifica se o monte acabou -------------------------------------------------------
        if(getTopo(&monte) == 0)
            repet = 0;
    }

    ///Informa o jogador vencedor -----------------------------------------------------------
    printf("Ganhador jogador %d", vencedor(qtdJogadores, &jogador)+1);
    printf("\n---------------------\n");
}
///-------------------------------------------------------------------------------------------
void criarArq()
{
    clear();
    printf("Arquivo rouba-monte.txt gerado com sucesso!!!");
}
///-------------------------------------------------------------------------------------------
void sair()
{
    clear();
    printf("Saindo!!!");
}
///-------------------------------------------------------------------------------------------
void clear()
{
    system("cls||clear");
}
///-------------------------------------------------------------------------------------------
int main()
{
    int opt;

    do
    {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1: inicio();   pause();    break;
            case 2: criarArq(); pause();    break;
            case 3: creditos(); pause();    break;
            case 4: sair();                 break;
        }
    }
    while(opt != 4);

    //system("pause");
    return 0;
}
