#ifndef COZINHA_H
#define COZINHA_H
#include "salao.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct PratoPedido{
  int item;
  struct PratoPedido *proximo;
} PratoPedido;

typedef struct PedidoCozinha{
  int idPedido;
  PratoPedido *pratos;
  struct PedidoCozinha *proximo;
}PedidoCozinha;

typedef struct Fila{
  PedidoCozinha *inicio;
  PedidoCozinha *fim;
}Fila;


void iniciaFila(Fila *f);
bool filaEstaVazia(Fila *f);
void adicionarPedidoCozinha(Fila *f, int idPedido, Prato *pratosSalao, const char *cardapio[]);
void listarPedidosCozinha(Fila *f, const char *cardapio[]);
int removerPedidoPronto(Fila *f, const char *cardapio[]);

#endif