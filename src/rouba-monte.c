/**
 * Grupo:       G4
 * Projeto:     Rouba Monte
 * Integrantes: "Allan Cezar Geraldo" <1011086@sumare.edu.br>,
 *              "Guilherme Mangabeira Gregio" <1012466@sumare.edu.br>
 *              "Marcio Barbosa de Melo" <1012689@sumare.edu.br>,
 *              "Matheus Borba Cezar" <1011022@sumare.edu.br>,
 *              "Rafael Antonio Lucio" <1010671@sumare.edu.br>,
**/

//
/// Bibliotecas
//
#include<stdio.h>
#include<stdlib.h>

//
/// Constantes
//
#define MAX 52 //Quantidades de cartas em um baralho;

//
/// Variaveis globais
//
int pilha[MAX]; //vetor para armazenar pilha;
int tos=0; //armazenar o topo da pilha;

//
/// Protopipação;
//
void push(int);
int pop(void);
int carta(void);
//
/// Função principal;
//
int main()
{
    srand(time(NULL));
    int i;

    //
    /// Preencher pilha com cartas eleatórias;
    //
    for(i=1; i<=52; i++)
    {
        push(carta());
    }

    //
    /// Recuperar cartas da pilha;
    //
    for(i=1; i<=52; i++)
    {
        printf("%d\n", pop());
        if(i % 13 == 0 && i != MAX) // Inserir uma divisão a cade 13 cartas;
        {
            printf("------------------------------------\n");
        }
    }
}

//
/// Inserir um elemento na pilha;
//
void push(int i)
{
    if(tos>=MAX)
    {
        printf("Pilha cheia\n");
        exit(1); //Encerrar programa caso a pilha esteja cheia;
    }
    pilha[tos] = i;
    tos++;
}

//
/// Recuperar o elemento do topo da pilha;
//
int pop(void)
{
    tos--;
    if(tos<0)
    {
        printf("Pilha vazia\n");
        exit(1); //Encerrar programa caso pilha esteja vazia;
    }
    return pilha[tos];
}

//
/// Sortear uma carta ou seja um numero de 1 a 13;
//
int carta(void)
{
    int carta = rand() % 14;

    if(carta == 0)
    {
        carta++;
    }
    return carta;
}
