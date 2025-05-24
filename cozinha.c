#include "cozinha.h"

void iniciaFila(Fila *f){
  f->inicio = NULL;
  f->fim = NULL;
}

bool filaEstaVazia(Fila *f){  
  return f->inicio == NULL;
}

void adicionaPedidoCozinha(Fila *f, int idPedido){
  PedidoCozinha *novo_pedidoCozinha = (PedidoCozinha *)malloc(sizeof(PedidoCozinha));

  if(!novo_pedidoCozinha){
    printf("  => Erro ao enviar pedido para cozinha!\n");
    return;
  }
 
  novo_pedidoCozinha->idPedido = idPedido;
  novo_pedidoCozinha->proximo = NULL;

  if(filaEstaVazia(f)){
    f->inicio = novo_pedidoCozinha;
  }else{
    f->fim->proximo = novo_pedidoCozinha;
  }

  f->fim = novo_pedidoCozinha;
    
  printf("  => Novo pedido processado: %d\n", idPedido);
}

void listarPedidosCozinha(Fila *f){
  if(filaEstaVazia(f)){
    printf("  => Não tem pedidos na cozinha!\n");
    return;
  }
  
  PedidoCozinha *temp = f->inicio;

  printf("  => Pedidos na: ");
  while(temp != NULL){
    printf("%d ", temp->idPedido);
    temp = temp->proximo;
  }

  printf("\n");
}