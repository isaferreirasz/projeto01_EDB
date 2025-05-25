#include "cozinha.h"

void iniciaFila(Fila *f){
  f->inicio = NULL;
  f->fim = NULL;
}

bool filaEstaVazia(Fila *f){  
  return f->inicio == NULL;
}

void adicionaPedidoCozinha(Fila *f, int idPedido, Prato *pratosSalao, const char *cardapio[]){
  PedidoCozinha *novo_pedidoCozinha = (PedidoCozinha *)malloc(sizeof(PedidoCozinha));

  if(!novo_pedidoCozinha){
    printf("  => Erro ao enviar pedido para cozinha!\n");
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
            printf("  => Erro ao anotar pratos do pedido!\n");
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
        printf("\n=> Pedido %d adicionado à cozinha:\n", idPedido);
          PratoPedido *pratoPedido = novo_pedidoCozinha->pratos;
          while (pratoPedido != NULL) {
              printf("  - [%d]: %s\n",pratoPedido -> item, cardapio[pratoPedido->item - 1]);
              pratoPedido = pratoPedido->proximo;
          }
      }

void listarPedidosCozinha(Fila *f, const char *cardapio[]) {
    if(filaEstaVazia(f)) {
        printf("  => Não há pedidos na cozinha!\n");
        return;
    }
    
    PedidoCozinha *pedidoAtual = f->inicio;  
    int contador = 1;
    
    printf("\n=> Pedidos na cozinha:\n");

    while(pedidoAtual != NULL) {
        printf("\n  %d. Pedido ID: %d\n", contador++, pedidoAtual->idPedido);
        
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

int removerPedidoPronto(Fila *f){
  if(filaEstaVazia(f)){
    printf("  => Não tem pedidos na cozinha!\n");
    return -1;
  }
 
  PedidoCozinha *temp = f->inicio;

  int valor = temp->idPedido;

  f->inicio = f->inicio->proximo;

  if(f->inicio == NULL)
    f->fim = NULL;

  free(temp);

  printf("  => Pedido pronto saindo da cozinha: %d\n", valor);
 
  return valor;
}