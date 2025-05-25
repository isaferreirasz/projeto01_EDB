#include "cozinha.h"

void iniciaFila(Fila *f){
  f->inicio = NULL;
  f->fim = NULL;
}

bool filaEstaVazia(Fila *f){  
  return f->inicio == NULL;
}

void adicionaPedidoCozinha(Fila *f, int idPedido, Prato *pratosSalao){
  PedidoCozinha *novo_pedidoCozinha = (PedidoCozinha *)malloc(sizeof(PedidoCozinha));

  if(!novo_pedidoCozinha){
    printf("  => Erro ao enviar pedido para cozinha!\n");
    return;
  }
 
  novo_pedidoCozinha->idPedido = idPedido;
  novo_pedidoCozinha->pratos = NULL;
  novo_pedidoCozinha->proximo = NULL;
   Prato *pratoAtual = pratosSalao;  // Começa no primeiro prato do pedido do salão
    PratoPedido *ultimoPratoPedido = NULL;  // Para manter o fim da lista
    
    while (pratoAtual != NULL) {
        // Aloca memória para cada prato na cozinha
        PratoPedido *novoPrato = (PratoPedido *)malloc(sizeof(PratoPedido));
        if (!novoPrato) {
            printf("  => Erro ao copiar pratos!\n");
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