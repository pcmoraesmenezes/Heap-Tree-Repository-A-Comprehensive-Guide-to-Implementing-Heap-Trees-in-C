#include <stdio.h> // incluindo a biblioteca basica de C
#include <stdlib.h>  // biblioteca que permite o uso das funções free e malloc
#define MAX_SIZE 100 // definindo o tamanho maximo da arvore
typedef struct arvoreHeap // criando uma struct 
{
    int tamanho; // variavel que representa o tamanho atual da arvore
    int heap[MAX_SIZE]; // criando um array com a capacidade maxima determinada da arvore
}arvoreHeap; // nome da struct

void insereHeap(int valor, arvoreHeap * p) // função de inserção na arvore heap, recebe dois parametros, o valor a ser inserido e uma variavel do tipo arvoreHeap
{
    if(p->tamanho == MAX_SIZE) // verifica se a arvore esta cheia
    {
        printf("Arvore cheia!\n"); // mensagem na tela
        return; // encerra a função
    }
    p->heap[p->tamanho] = valor; // atribui o valor a arvore no local determinado pelo tamanho da arvore
    int index = p->tamanho; // cria uma variavel que recebe o tamanho da arvore
    p->tamanho = p->tamanho+1; // incrementa a arvore em 1
    int pai = (index - 1) /2;  // calcula o índice do nó pai do nó atual, que é representado por index
    while(index > 0 && p->heap[index] > p->heap[pai]) // verifica se o tamanho da arvore antes da inserção é maior que 0 e verifica se o elemento da arvore no indice e maior que o elemento da arvore no nó pai
    {
        int temp = p->heap[index]; // criando uma variavel temporaria que recebe o elemento na posição do indice
        p->heap[index] = p->heap[pai]; // fazendo o elemento na posição do indice receber o elemento na posição do pai
        p->heap[pai] = temp; // fazendo com que o elemento na posição do pai receba o elemento na posição do indice
        index = pai; // fazendo com que o indice receba o pai
        pai = (index - 1) / 2; // formula para determinar a posição do pai
    }
}

void imprimeArvoreHeap(arvoreHeap * p, int indice, int nivel)//Função recursiva que recebe tres parametros, o primeiro e um ponteiro para a struct, o segundo e o indice que representa o indice atual do nó da arvore a ser impresso e o terceiro e o nivel que a arvore representa, começando por 0
{
    if (indice >= p->tamanho) // verifica se o indice e maior que o tamanho atual da arvore, para evitar possiveis erros de acesso a posições invalidas da arvore
        return; // encerra a função

    imprimeArvoreHeap(p, 2 * indice + 2, nivel + 1); // chamando a função recursivamente para imprimir o nó do filho da direita do nó atual, segue a logica de indexação de arvores binarias

    for (int i = 0; i < nivel; i++) // formatação da arvore baseado no nivel maximo dela
        printf("\t"); // formatando a saida

    printf("%d\n", p->heap[indice]); // imprime o valor armazenado na arvore

    imprimeArvoreHeap(p, 2 * indice + 1, nivel + 1); // chama a função recursivamente para imprimir o nó a esquerda do nó atual
}

void imprimeHeap(arvoreHeap * p)// função que iremos chamar no main
{
    if (p->tamanho == 0) // verifica se a arvore está vazia
    {
        printf("Arvore vazia!\n"); // mensagem na tela
        return; // encerra a função
    }

    imprimeArvoreHeap(p, 0, 0); // chama a função que irá imprimir, recebe um ponteiro para a struct e o indice e o nivel começando por 0
}

int busca(arvoreHeap *p, int valor) // função de busca, recebe dois parametros, um ponteiro para a struct e o valor a ser buscado
{
    if(p->tamanho == 0) // verifica se a arvore está vazia
    {
        printf("Não há elementos nessa arvore !\n"); // mensagem na tela
        return 0; // encerra a função retornando 0
    }
    for(int i = 0; i < p->tamanho; i++) // percorrendo todos os elementos da arvore
    {
        if(p->heap[i] == valor) // verifica se o elemento na posição da variavel 'i' e equivalente ao valor
        {
            printf("Achou!\n"); // mensagem na tela informando que encontrou o elemento
            return i; // retorna a posição que o elemento foi encontrada
        }
    }
    printf("Valor não encontrado!\n"); // mensagem na tela informando que não encontrou o elemento
    return 2;   // retorna 2
}

int removeHeap(arvoreHeap * p, int valor) // função para remover elementos de nossa arvore, recebe dois parametros um ponteiro para a struct e o valor a ser removido
{
    if(p->tamanho == 0) // verifica se a arvore está vazia
    {
        printf("Não há elementos nessa arvore!\n"); // mensagem na tela
        return 0; // retorna 0
    }
    int aux = busca(p , valor); // criando uma variavel auxiliar que irá ser responsavel por verificar se o elemento existe naquela arvore
    if(aux == 2) // caso o elemento não exista, a função retornara 2, então o elemento a ser removido não existe
    {
        return 2; // encerrando a função
    }
    p->heap[aux] = p->heap[p->tamanho - 1]; // bom caso o elemento exista, a variavel aux recebera o indice do elemento, então o elemento na posição do aux esta recebendo o penultimo elemento da arvore
    p->tamanho --; // decrementando o tamanho da arvore
    int pai = (aux - 1) / 2; // calcula o indice do nó atual do nó pai
    int filho = 2 * aux + 1; // calcula o indice do primeiro filho
    while(filho < p->tamanho) // verifica se o indice do filho e menor que o tamanho da arvore
    {
        if(filho + 1  < p->tamanho && p->heap[filho+1] > p->heap[filho]) // verifica se o indice do segundo filho e menor que o tamanho da arvore e verifica se a posição do proximo filho e maior que a do filho atual
        {
            filho++; // incrementa o tamanho da variavel filho
        }
        if(p->heap[filho] > p->heap[aux]) // verifica se o elemento na posição do filho e maior que o elemento a ser removido
        {
            int temp = p->heap[filho]; // cria uma variavel temporaria que recebe o elemento na posição do filho
            p->heap[filho] = p->heap[aux]; // o eleemnto na posição do filho recebe o elemento a ser removido
            p->heap[aux] = temp; // o elemento a ser removido recebe uma variavel temporaria
            aux = filho; // o indice recebe o filho
            filho = 2 * aux + 1; // calculo para ir para o proximo nó do filho
        }
        else // senao
        {
            break; // encerra  a função
        }

    }

}

int main() // corpo principal da função
{   
    arvoreHeap * p = (arvoreHeap *) malloc(sizeof(arvoreHeap)); // alocando um espaço na memoria do tamanho da struct e fazendo a varivel ponteiro receber a struct
    p->tamanho = 0; // inicializando a arvore
     int navegador = 0; // essa variavel será responsavel por guiar o usuario na interface
    int adicionar = 0; // variavel responsavel por receber o numero que o usuario gostaria de inserir na fila
    while (true) // essa condição faz com que o laço de repetição seja sempre verdade
   { 
        printf("Bem vindo a sua Arvore Heap!\n Para visualizar a sua Arvore digite '1'\n Para inserir um valor em sua Arvore digite '2'\n Para remover um elemento de sua arvore digite '3'\n Para realizar uma busca digite '4'\n Para sair digite '5'\n"); // mensagem para o usuario
        scanf("%d", &navegador); // está recebendo do usuario um numero para ação
        while (navegador != 1 && navegador != 2 && navegador != 3 && navegador != 4 && navegador != 5) // verifica se o usuario digitou algo além do que esperado
        {
            printf("Você não informou uma opção válida! Tente novamente \n"); // informa que ele não digitou uma opção válida das que foram ofertadas
            scanf("%d", &navegador);// recebe do usuario outra opção
        }
        if (navegador == 1) // verifica se ele escolheu a opção 1
        {
            if(p->tamanho == 0) // verifica se a arvore está vazia
            {
                printf("Arvore vazia ! \n"); // retorna uma mensagem
            }
            else
            { // senao
                printf("Você optou por visualizar a Arvore!\n "); // retorna uma mensagem
                imprimeHeap(p); // imprime a arvore na tela
            }
        }
        if (navegador == 2) // verifica se ele optou pela opção 2
        {
            printf("Você optou por inserir! Por favor insira o numero abaixo: \n"); // retorna uma mensagem
            scanf("%d", &adicionar); // recebe do usuario um numero a ser adicionado
            insereHeap(adicionar, p); // chamando a função que adiciona elementos na arvore
        }
        if (navegador == 3) // verifica se o usuario optou pela opção 3
        {
            if(p->tamanho == 0) // verifica se a arvore está vazia
            {
                printf("Arvore vazia! \n"); // retorna uma mensagem
            }
            else // senao
            {
              printf("Você optou por remover um elemento da arvore!\n "); // imprime uma mensagem na tela
              printf("Informe um valor!\n"); // imprime uma mensagem na tela
              scanf("%d", &adicionar); // pede ao usuario um valor
              removeHeap(p,adicionar);//remove um valor
            }
        }
        if(navegador == 4) // verifica se o usuario optou pela opção 4
        {
            printf("Você optou por realizar uma busca, informe o valor desejado a ser buscado!\n"); // mensagem na tela
            scanf("%d", &adicionar); // pede ao usuario um valor
            busca(p,adicionar); // função de busca
        }
        if (navegador == 5) // verifica se o usuario optou pela opção 5
        {   printf("Você optou por sair do Navegador! \n"); // retorna uma mensagem
            break; // quebra o laço de repetição
        }
    }
}