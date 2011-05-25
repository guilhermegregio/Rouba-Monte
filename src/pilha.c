/**
 * pilha.c
 * biblioteca com todas as funções necessárias
 * para manipular a pilha
**/

/**
* Daclaração de Constantes
*/
#define TAMPILHA 52

/**
* Criação de estrutura
*/
typedef struct {
    int topo;
    int cartas[TAMPILHA];
} PILHA;

/**
* Função para inserir na pilha
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
* Função para retirar da pilha
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
* Função para zerar monte
* <params>PILHA</params>
*/
void pegarMonte(PILHA *ps)
{
    ps->topo = 0;
}

/**
* Função para mostrar primeiro item da pilha
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
* Função para mostrar topo
* <params>PILHA</params>
*/
int getTopo(PILHA *ps)
{
	return ps->topo;
}

/**
* Função para setar o topo como zero.
* <params>PILHA</params>
*/
void setTopo(PILHA *ps)
{
    ps->topo = 0;
}
