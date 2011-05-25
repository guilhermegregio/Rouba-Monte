/**
 * pilha.c
 * biblioteca com todas as fun��es necess�rias
 * para manipular a pilha
**/

/**
* Daclara��o de Constantes
*/
#define TAMPILHA 52

/**
* Cria��o de estrutura
*/
typedef struct {
    int topo;
    int cartas[TAMPILHA];
} PILHA;

/**
* Fun��o para inserir na pilha
* <params>PILHA</params>
* <params type="int">x</params>
*/
void push(PILHA *ps, int x)
{
    if (ps->topo > TAMPILHA) {
        printf("%s\n", "Pilha Cheia");
        system("pause");
        exit(1);
    } else
        ps->cartas[ps->topo++] = x;
}

/**
* Fun��o para retirar da pilha
* <params>PILHA</params>
*/
int pop(PILHA *ps)
{
    if (ps->topo <= 0) {
        printf("%s\n", "Pilha vazia");
        system("pause");
        exit(1);
    } else
        return ps->cartas[--ps->topo];
}

/**
* Fun��o para zerar monte
* <params>PILHA</params>
*/
void pegarMonte(PILHA *ps)
{
    ps->topo = 0;
}

/**
* Fun��o para mostrar primeiro item da pilha
* <params>PILHA</params>
*/
int getTopItem(PILHA *ps)
{
    if(ps->topo > 0)
    {
        return ps->cartas[ps->topo-1];
    }
    return -1;
}

/**
* Fun��o para mostrar topo
* <params>PILHA</params>
*/
int getTopo(PILHA *ps)
{
	return ps->topo;
}

/**
* Fun��o para setar o topo como zero.
* <params>PILHA</params>
*/
void setTopo(PILHA *ps)
{
    ps->topo = 0;
}
