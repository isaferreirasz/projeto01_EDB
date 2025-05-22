#ifndef SALAO_H
#define SALAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prato {
    int item;
    char nome[60];
    struct prato *proximo;
} Prato;

typedef struct pedido {
    int id;
    Prato *pratos;
    struct pedido *proximo;
} Pedido;


void adicionarPedido(Pedido **salao, int qtd, int itens[], const char *cardapio[]);
void adicionarPratoPedido(Pedido *salao, int id, int item, const char *cardapio[]);
void removerPedido(Pedido *salao, int id, int item);
void listarPedidos(Pedido *salao);

#endif
