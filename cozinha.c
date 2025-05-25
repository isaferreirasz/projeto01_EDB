#include "cozinha.h"

void iniciaFila(Fila *f){
  f->inicio = NULL;
  f->fim = NULL;
}

bool filaEstaVazia(Fila *f){  
  return f->inicio == NULL;
}

void adicionarPedidoCozinha(Fila *f, int idPedido, Prato *pratosSalao, const char *cardapio[]){
  PedidoCozinha *novo_pedidoCozinha = (PedidoCozinha *)malloc(sizeof(PedidoCozinha));

  if(!novo_pedidoCozinha){
    printf("Erro ao enviar pedido para cozinha!\n");
    return;
  }
 
  novo_pedidoCozinha->idPedido = idPedido;
  novo_pedidoCozinha->pratos = NULL;
  novo_pedidoCozinha->proximo = NULL;
  
   Prato *pratoAtual = pratosSalao;  
   PratoPedido *ultimoPratoPedido = NULL;  
    
    while (pratoAtual != NULL) {
        PratoPedido *novoPrato = (PratoPedido *)malloc(sizeof(PratoPedido));
        if (!novoPrato) {
            printf("Erro ao anotar pratos do pedido!\n");
            break;
        }
        
        novoPrato->item = pratoAtual->item;
        novoPrato->proximo = NULL;
        

        if (novo_pedidoCozinha->pratos == NULL) {
            novo_pedidoCozinha->pratos = novoPrato; 
        } else {
            ultimoPratoPedido->proximo = novoPrato; 
        }
        ultimoPratoPedido = novoPrato;  
        
        pratoAtual = pratoAtual->proximo;  
    }

      if(filaEstaVazia(f)){
        f->inicio = novo_pedidoCozinha;
        f->fim = novo_pedidoCozinha;
      } else{
        f->fim->proximo = novo_pedidoCozinha;
        f->fim = novo_pedidoCozinha;
      }
        printf("\nPedido %d adicionado a cozinha:\n", idPedido);
          PratoPedido *pratoPedido = novo_pedidoCozinha->pratos;
          while (pratoPedido != NULL) {
              printf("  - [%d]: %s\n",pratoPedido -> item, cardapio[pratoPedido->item - 1]);
              pratoPedido = pratoPedido->proximo;
          }
      }

void listarPedidosCozinha(Fila *f, const char *cardapio[]) {
    if(filaEstaVazia(f)) {
        printf("Nao tem pedidos na cozinha!\n");
        return;
    }
    
    PedidoCozinha *pedidoAtual = f->inicio;  
    int contador = 1;
    
    printf("\nPedidos na cozinha:\n");

    while(pedidoAtual != NULL) {
        printf("\n  %d. Pedido: %d\n", contador++, pedidoAtual->idPedido);
        
        PratoPedido *pratoAtual = pedidoAtual->pratos;  

        while(pratoAtual != NULL) {
            printf("     - [%d] %s\n", 
                  pratoAtual->item, 
                  cardapio[pratoAtual->item - 1]);
            pratoAtual = pratoAtual->proximo;
        }
        
        pedidoAtual = pedidoAtual->proximo; 
    }
}

int removerPedidoPronto(Fila *f, const char *cardapio[]) {
    if(filaEstaVazia(f)) {
        printf("Nao tem pedidos na cozinha!\n");
        return -1;
    }

    PedidoCozinha *pedidoPronto = f->inicio;
    int idPedido = pedidoPronto->idPedido;

    printf("\nPedido pronto saindo da cozinha: %d\n", idPedido);
    PratoPedido *pratoAtual = pedidoPronto->pratos;
    while(pratoAtual != NULL) {
        printf("  - [%d] %s\n", pratoAtual->item, cardapio[pratoAtual->item - 1]);
        pratoAtual = pratoAtual->proximo;
    }

    pratoAtual = pedidoPronto->pratos;
    while(pratoAtual != NULL) {
        PratoPedido *proximoPrato = pratoAtual->proximo;
        free(pratoAtual);
        pratoAtual = proximoPrato;
    }

    f->inicio = pedidoPronto->proximo;
    if(f->inicio == NULL) {
        f->fim = NULL;  
    }

    free(pedidoPronto);

    return idPedido;
}