#ifndef COZINHA_H
#define COZINHA_H
#include "salao.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct PratoPedido{
  int item;
  struct PratoPedido *proximo;
} PratoPedido;

typedef struct pedidoCozinha{
  int idPedido;
  PratoPedido *pratos;
  struct pedidoCozinha *proximo;
}PedidoCozinha;

typedef struct Fila{
  PedidoCozinha *inicio;
  PedidoCozinha *fim;
}Fila;


void iniciaFila(Fila *f);
bool filaEstaVazia(Fila *f);
void adicionaPedidoCozinha(Fila *f, int idPedido, Prato *pratosSalao, const char *cardapio[]);
void listarPedidosCozinha(Fila *f);
int removerPedidoPronto(Fila *f);

#endif