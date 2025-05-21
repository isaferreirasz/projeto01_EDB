
#ifndef SALAO_H
#define SALAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int item;
    char prato[60];
    struct no *proximo;
} No;

void adicionarPedidoSalao(No **salao, const char *prato, int item);
int removerFim(No **salao, int item);
void listarPedidosSalao(No *salao);
No* enviarPedidoCozinha(No **salao);

#endif