#include <stdio.h>
#include "salao.h"

void adicionarPedidoSalao(No **salao, const char *prato, int item) {
    No *novo = malloc(sizeof(No));
    novo->item = item;
    strcpy(novo->prato, prato);
    novo->proximo = *salao;
    *salao = novo;
}

void removerInicio(No **salao){
    if(*salao == NULL){
      printf("A lista está vazia!\n");
      return;
    }
  
    No *temp = *salao;
    *salao = (*salao)->proximo;
    free(temp);
  }

int removerFim(No **salao, int item) {
    if(*salao == NULL || (*salao)->proximo == NULL){
        removerInicio(salao);
        return;
      }
    
      No *anterior = NULL;
      No *atual = *salao;
    
      while(atual->proximo != NULL){
        anterior = atual;
        atual = atual->proximo;
      }
    
      anterior->proximo = NULL;
    
      free(atual);
      return 1;
    }

void listarPedidosSalao(No *salao) {
    if(salao == NULL){
      printf("Nenhum pedido no salão.\n");
      return;
    }
  
    No *atual = salao;
    
    while(atual != NULL){
        printf(" ==== Pedidos do Salão ==== \n ");
            printf(" - Prato %d: %s\n", atual->item, salao->prato);
            atual = atual->proximo;

        
    }
    printf("\n");
  }
  

No* enviarPedidoCozinha(No **salao) {
    if (!*salao) return NULL;

    No *pedido = *salao;
    *salao = pedido->proximo;
    pedido->proximo = NULL;
    return pedido;
}
