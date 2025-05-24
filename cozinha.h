#ifndef COZINHA_H
#define COZINHA_H
#include "salao.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct pedidoCozinha{
  int idPedido;
  Prato *pratos;
  struct pedidoCozinha *proximo;
}PedidoCozinha;

typedef struct Fila{
  PedidoCozinha *inicio;
  PedidoCozinha *fim;
}Fila;


void iniciaFila(Fila *f);
bool filaEstaVazia(Fila *f);
void adicionaPedidoCozinha(Fila *f, int idPedido);
void listarPedidosCozinha(Fila *f);
int removerPedidoPronto(Fila *f);

#endif