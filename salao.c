
#include "salao.h"

int proximoID = 1;

Prato* criarPrato(int item, const char *cardapio[]) {
    Prato *novo = (Prato*)malloc(sizeof(Prato));
    novo->item = item;
    strcpy(novo->nome, cardapio[item - 1]);
    novo->proximo = NULL;
    return novo;
}

void adicionarPedido(Pedido **salao, int qtd, int itens[], const char *cardapio[]) {
    Pedido *novoPedido = (Pedido*)malloc(sizeof(Pedido));
    novoPedido->id = proximoID++;
    novoPedido->pratos = NULL;
    novoPedido->proximo = NULL;

    for (int i = 0; i < qtd; i++) {
        Prato *novo = criarPrato(itens[i], cardapio);
        novo->proximo = novoPedido->pratos;
        novoPedido->pratos = novo;
    }

    novoPedido->proximo = *salao;
    *salao = novoPedido;

    printf("Pedido %d adicionado com %d prato(s).\n", novoPedido->id, qtd);
}

void adicionarPratoPedido(Pedido *salao, int id, int item, const char *cardapio[]) {
    while (salao && salao->id != id)
        salao = salao->proximo;

    if (salao == NULL) {
        printf("Pedido %d não encontrado.\n", id);
        return;
    }

    Prato *novo = criarPrato(item, cardapio);
    novo->proximo = salao->pratos;
    salao->pratos = novo;

    printf("Prato adicionado ao pedido %d.\n", id);
}

void removerPedido(Pedido *salao, int id, int item) {
    while (salao && salao->id != id)
        salao = salao->proximo;

    if (salao == NULL) {
        printf("Pedido %d não encontrado.\n", id);
        return;
    }

    Prato *atual = salao->pratos;
    Prato *anterior = NULL;

    while (atual && atual->item != item) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Prato %d não encontrado no pedido %d.\n", item, id);
        return;
    }

    if (anterior)
        anterior->proximo = atual->proximo;
    else
        salao->pratos = atual->proximo;

    free(atual);
    printf("Prato %d removido do pedido %d.\n", item, id);
}

void listarPedidos(Pedido *salao) {
    if (salao == NULL) {
        printf("Nenhum pedido no salão.\n");
        return;
    }

    while (salao) {
        printf("Pedido %d:\n", salao->id);
        Prato *p = salao->pratos;
        while (p) {
            printf("  - [%d] %s\n", p->item, p->nome);
            p = p->proximo;
        }
        salao = salao->proximo;
    }
}

