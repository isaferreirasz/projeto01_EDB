#ifndef SALAO_H
#define SALAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estrutura para o prato, contendo o item (1a 15), o nome do prato e uma estrutura de ponteiro que aponta pra o proximo 
typedef struct prato {
    int item;
    char nome[60];
    struct prato *proximo;
} Prato;

/*Estrutura para os pedidos contebdo um identificador (controle de qual pedido foi feito e facilitando a remoção ou adição de um prato).
Dentro da struct pedido, ainda temos a estrutura de pratos anteriormente definida e um contendo um ponteiro que apontará para o procimo elemnto da lista
*/
typedef struct pedido {
    int id;
    Prato *pratos;
    struct pedido *proximo;
} Pedido;


//Função responsável pela adição de um novo pedido
void adicionarPedido(Pedido **salao, int qtd, int itens[], const char *cardapio[]);
//Função responsável pela adição de um novo prtto a um pedido que já existe 
void adicionarPratoPedido(Pedido *salao, int id, int item, const char *cardapio[]);
//Função responsável por remover um prato especifico do pedido, utilizando o id para identificar o pedido e pedindo o numero do item
void removerPedido(Pedido *salao, int id, int item);
//Função responsável por listas os pedidos que existem no sallão
void listarPedidos(Pedido *salao);
//Função responsável por remover pedidos da lista após esses terem sidos enviados para a cozinha
void removerPedidoLista(Pedido **salao, int id);

#endif
