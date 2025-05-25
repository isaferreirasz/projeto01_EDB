#include "cozinha.h"

void iniciaFila(Fila *f){ //Função que inicializa a fila
  f->inicio = NULL; //Define que o início da fila está vazio
  f->fim = NULL; //Define que o fim da fila está vazio
}

bool filaEstaVazia(Fila *f){  //Função verifica se a fila está vazia
  return f->inicio == NULL; //Compara se o início da fila está vazio, se sim a fila está vazia
}

void adicionarPedidoCozinha(Fila *f, int idPedido, Prato *pratosSalao, const char *cardapio[]){ //Função que adiciona um novo pedido à cozinha
  //Cria um ponteiro do tipo PedidoCozinha que vai apontar para um novo pedido da cozinha e aloca esse pedido com memória dinâmica
    PedidoCozinha *novo_pedidoCozinha = (PedidoCozinha *)malloc(sizeof(PedidoCozinha)); 

  if(!novo_pedidoCozinha){ //Se o novo pedido for nulo, significa que a alocação de memória falhou, então o pedido não foi enviado para a cozinha
    printf("Erro ao enviar pedido para cozinha!\n");
    return;
  }
 
  novo_pedidoCozinha->idPedido = idPedido; //Define que o id do novo pedido da cozinha recebe o id do pedido digitado pelo usuário
  novo_pedidoCozinha->pratos = NULL; //Define os pratos do novo pedido da cozinha como nulos
  novo_pedidoCozinha->proximo = NULL; //Define o próximo pedido como nulo
  
   Prato *pratoAtual = pratosSalao; //Define um ponteiro do tipo Prato que será usado para percorrer a lista de pratos do pedido que está no salão
   PratoPedido *ultimoPratoPedido = NULL;  //Define um ponteiro do tipo PratoPedido que irá apontar para o último prato do pedido
    
    while (pratoAtual != NULL) { //Enquanto o pratoAtual for diferente de nulo...
        PratoPedido *novoPrato = (PratoPedido *)malloc(sizeof(PratoPedido)); //Aloca dinacamente um novo prato à lista de pratos do pedido
        if (!novoPrato) { //Se o novoPrato for nulo, significa que a alocação de memória falhou, então o prato não foi adicionado ao pedido
            printf("Erro ao anotar pratos do pedido!\n");
            break;
        }
        
        novoPrato->item = pratoAtual->item; //Define que o item do novo prato recebe o item do prato atual
        novoPrato->proximo = NULL; //Define o próximo prato como nulo 
        

        if (novo_pedidoCozinha->pratos == NULL) { //Se o novo pedido estiver sem pratos...
            novo_pedidoCozinha->pratos = novoPrato;  //Adiciona o novo prato como o primeiro da lista
        } else { //Se a novo pedido já estiver com pratos...
            ultimoPratoPedido->proximo = novoPrato; //Adiciona o novo prato ao final da lista
        }
        ultimoPratoPedido = novoPrato; //Atualiza o último prato do pedido como o prato atual 
        
        pratoAtual = pratoAtual->proximo;  //Avança para o próximo prato
    }

      if(filaEstaVazia(f)){ //Se a fila estiver vazia...
        f->inicio = novo_pedidoCozinha; //Define o novo pedido da cozinha como início da fila
        f->fim = novo_pedidoCozinha; //Define o novo pedido como o final da fila
      } else{ //Se a fila não estiver vazia...
        f->fim->proximo = novo_pedidoCozinha; //Adiciona o novo pedido ao final da fila
        f->fim = novo_pedidoCozinha; //Define o novo pedido como o final da fila
      }
        printf("\nPedido %d adicionado a cozinha:\n", idPedido); //Avisa que o pedido foi adicionado à cozinha 
          PratoPedido *pratoPedido = novo_pedidoCozinha->pratos; //Acessa os pratos do pedidos adicionado à cozinha
          while (pratoPedido != NULL) { //Enquanto pratoPedido for diferente de nulo, imprime todos os pratos do pedido 
              printf("  - [%d]: %s\n",pratoPedido -> item, cardapio[pratoPedido->item - 1]); //Imprime o prato do pedido mostrando seu item e nome correspondente do cardápio 
              pratoPedido = pratoPedido->proximo; //Avança para o próximo prato
          }
      }

void listarPedidosCozinha(Fila *f, const char *cardapio[]) { //Função que lista todos os pedidos da cozinha
    if(filaEstaVazia(f)) { //Verifica se a fila está vazia, se sim avisa que não tem pedidos na cozinha
        printf("Nao tem pedidos na cozinha!\n");
        return;
    }
    
    PedidoCozinha *pedidoAtual = f->inicio;  //Define um ponteiro do tipo PedidoCozinha que aponta para o início da fila
    int contador = 1; //Inicializa um contador 
    
    printf("\nPedidos na cozinha:\n");

    while(pedidoAtual != NULL) { //Enquanto o pedidoAtual for diferente de nulo...
        printf("\n  %d. Pedido: %d\n", contador++, pedidoAtual->idPedido); //Imprime o pedido com seu id e itera o contador 
        
        PratoPedido *pratoAtual = pedidoAtual->pratos;  //Define um ponteiro que irá percorrer todos os pratos do pedido atual que está sendo listado

        while(pratoAtual != NULL) { //Enquanto tiver pratos no pedido...
            printf("     - [%d] %s\n", pratoAtual->item, cardapio[pratoAtual->item - 1]); //Imprime o prato do pedido mostrando seu item e nome correspondente do cardápio 
            pratoAtual = pratoAtual->proximo; //Avança para o próximo prato
        }
        
        pedidoAtual = pedidoAtual->proximo;  //Define que o pedidoAtual como o próximo da fila para que ele também seja impresso
    }
}

int removerPedidoPronto(Fila *f, const char *cardapio[]) { //Função que remove o primeiro pedido da fila
    if(filaEstaVazia(f)) { //Verifica se a fila está vazia, se sim avisa que não tem pedidos na cozinha
        printf("Nao tem pedidos na cozinha!\n");
        return -1; //Retorna -1 pois nenhum pedido foi removido da fila
    }

    PedidoCozinha *pedidoPronto = f->inicio; //Define uma ponteiro do tipo PedidoCozinha que aponta para o "pedido pronto", ou seja, para o primeiro pedido da fila
    int idPedido = pedidoPronto->idPedido; //Define que o id do pedido como o id do pedido pronto que irá ser removido da fila

    printf("\nPedido pronto saindo da cozinha: %d\n", idPedido); //Avisa qual pedido está saindo da fila mostrando seu id
    PratoPedido *pratoAtual = pedidoPronto->pratos; //Define um ponteiro que irá percorrer todos os pratos do pedido que está sendo removido
    while(pratoAtual != NULL) { //Enquanto tiver pratos no pedido...
        printf("  - [%d] %s\n", pratoAtual->item, cardapio[pratoAtual->item - 1]); //Imprime o prato do pedido mostrando seu item e nome correspondente do cardápio 
        pratoAtual = pratoAtual->proximo; //Avança para o próximo prato para que ele também seja impresso
    }

    pratoAtual = pedidoPronto->pratos; //Define pratoAtual como os pratos do pedido pronto
    while(pratoAtual != NULL) { //Enquanto tiver pratos no pedido...
        PratoPedido *proximoPrato = pratoAtual->proximo; //Define um ponteiro do tipo PratoPedido que aponta para o próximo prato 
        free(pratoAtual); //Libera a memória do prato do pedido
        pratoAtual = proximoPrato; //Define o pratoAtual como o próximo prato para que ele também possa ser liberado
    }

    f->inicio = pedidoPronto->proximo; //Define o próximo pedido como o novo início para fila
    if(f->inicio == NULL) { //Se o início estiver vazio...
        f->fim = NULL;  //Define o fim como vazio também, pois significa que a fila está vazia
    }

    free(pedidoPronto); //Libera a memória alocada para o pedido pronto que foi removido 

    return idPedido; //Retorna o id do pedido removido
}