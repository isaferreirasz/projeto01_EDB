#ifndef SALAO_H
#define SALAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definindo uma estrutura que representa um prato 
typedef struct prato {
    int item; //Recebe o id do item (1 a 15) que represena o prato no cardápio
    char nome[60]; //Recebe o nome do prato em um char de no máximo 60 caracteres
    struct prato *proximo; //Ponteiro que aponta para o próximo prato
} Prato;

//Definindo uma estrutura que representa um pedido
typedef struct pedido {
    int id; //Recebe o id do pedido
    Prato *pratos; //Recebe uma lista do tipo Prato que contém todos os pratos do pedido
    struct pedido *proximo; //Ponteiro que aponta para o próximo pedido
} Pedido;

//Função responsável pela adição de um novo pedido
//Recebe um ponteiro do tipo Pedido que aponta para lista de pedidos do salão, a quantidade de pratos no pedido, os itens (pratos) do pedido e um vetor representando o cardapio
void adicionarPedido(Pedido **salao, int qtd, int itens[], const char *cardapio[]);

//Função responsável pela adição de um novo prato a um pedido que já existe 
//Recebe um ponteiro do tipo Pedido que aponta para lista de pedidos do salão, o id do pedido que vai ser adicionado um novo prato, o item que corresponde ao novo prato e um vetor representando o cardápio
void adicionarPratoPedido(Pedido *salao, int id, int item, const char *cardapio[]);

//Função responsável por remover um prato especifico do pedido
//Recebe um ponteiro do tipo Pedido que aponta para lista de pedidos do salão, o id do pedido que vai ser removido um prato e o item que corresponde ao prato que vai ser removido
void removerPedido(Pedido *salao, int id, int item);

//Função responsável por listar os pedidos que existem no salão
void listarPedidos(Pedido *salao);

//Função responsável por remover pedidos da lista após esses terem sidos enviados para a cozinha
//Recebe um ponteiro do tipo Pedido que aponta para a lista de pedidos e o id do pedido que vai ser removido da lista
void removerPedidoLista(Pedido **salao, int id);

#endif
