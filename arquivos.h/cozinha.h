#ifndef COZINHA_H
#define COZINHA_H
#include "salao.h"
#include <stdio.h>
#include <stdbool.h>

//Definindo uma estrutura PratoPedido que representa a lista de pratos pertencentes a um único pedido.
typedef struct PratoPedido{ 
  int item; //Recebe o id do item do cardápio correspondente ao prato 
  struct PratoPedido *proximo; //Ponteiro para o próximo prato do pedido
} PratoPedido;

//Definindo uma estrutura PedidoCozinha que representa uma lista de pedidos da cozinha
typedef struct PedidoCozinha{
  int idPedido; //Recebe o id do pedido
  PratoPedido *pratos; //Ponteiro do tipo PratoPedido que guarda todos os pratos do pedido
  struct PedidoCozinha *proximo; //Ponteiro para o próximo pedido da cozinha
}PedidoCozinha;

//Definindo uma estrutura Fila que representa a fila que vai ser implementada do tipo FIFO
typedef struct Fila{
  PedidoCozinha *inicio; // Ponteiro para o primeiro pedido da fila
  PedidoCozinha *fim; // Ponteiro para o último pedido da fila
}Fila;

//Função responsável por inicializar a fila
void iniciaFila(Fila *f); //Recebe como parâmetro um ponteiro do tipo Fila

//Função responsável por verificar se a fila está vazia
bool filaEstaVazia(Fila *f); //Recebe como parâmetro um ponteiro do tipo Fila

//Função responsável por adicionar um novo pedido ao final da fila da cozinha
//Recebe como parâmetros um ponteiro do tipo Fila, o id do pedido que vai ser adicionado à cozinha, uma lista do tipo Prato com os pratos do pedido e um vetor representando o cardápio
void adicionarPedidoCozinha(Fila *f, int idPedido, Prato *pratosSalao, const char *cardapio[]);

//Função responsável por listar todos os pedidos da cozinha
void listarPedidosCozinha(Fila *f, const char *cardapio[]); //Recebe como parâmetro um ponteiro do tipo Fila e um vetor representando o cardápio

//Função responsável por remover um pedido do início da fila da cozinha
int removerPedidoPronto(Fila *f, const char *cardapio[]); //Recebe como parâmetro um ponteiro do tipo Fila e um vetor representando o cardápio

#endif