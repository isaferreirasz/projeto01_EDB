
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

  if (*salao == NULL) {
    *salao = novoPedido;
  } else {
    Pedido *atual = *salao;
    while (atual->proximo != NULL) {
      atual = atual->proximo;
    }
    atual->proximo = novoPedido;
  }

  printf("Pedido %d adicionado com %d prato(s).", novoPedido->id, qtd);
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

void removerPedidoLista(Pedido **salao, int id) {
    if (*salao == NULL) {
        printf("Nenhum pedido no salão.\n");
        return;
    }

    Pedido *atual = *salao;
    Pedido *anterior = NULL;

    //Essa estrutura de repetição vai fazer a buscar do id fornecido na lista do salao
    while (atual && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    //Se caso o id fornecido nao estiver na lista do salao é o caso de que o pedido nao foi feito (nao existe no salao)
    if (atual == NULL) {
        printf("Pedido %d não encontrado.\n", id);
        return;
    }

    //Nesse ponto vai ocorrer a remoção do pedido propriamente sendo considerado o caso do incio, meio e fim
    if (anterior == NULL) {
        *salao = atual->proximo; //salao como a cabeça do no (remocao no incio)
    } else {
        anterior->proximo = atual->proximo; //remocao no meio e fim da lista
    }

    /*Como da pedido tem uma lista de pratos, precisa-se remover (liberar memoria) para cada um, assim usamos um ponteiro auxiliar para percorrer a lista(p)
    e outro para ir recebendo os pratos (temp) e ir liberando o espaço da memoria*/
    Prato *p = atual->pratos;
    while (p) {
        Prato *temp = p;
        p = p->proximo;
        free(temp);
    }

    //Nesse ponto, como os pratos já foram liberados, fazemos a liberação do pedido
    free(atual);
    printf("Pedido %d removido do salão.\n", id);
}
