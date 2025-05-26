
#include "../arquivos.h/salao.h"
int proximoID = 1; //Criação da variavel global para que cada pedido tenha um ID unico e seja incrementado a cada pedido

//Função para criar um prato
Prato* criarPrato(int item, const char *cardapio[]) {
    Prato *novo = (Prato*)malloc(sizeof(Prato)); //aqui temos a alocação dinamica na memoria para que o prato seja armazenado
    novo->item = item; //serve para guardar o numero do prato
    strcpy(novo->nome, cardapio[item - 1]); //faz uma copia do nome do prato do cardapio (vetor)
    novo->proximo = NULL;
    return novo;
}

//Função para criar um novo pedido
void adicionarPedido(Pedido **salao, int qtd, int itens[], const char *cardapio[]) {
  Pedido *novoPedido = (Pedido*)malloc(sizeof(Pedido)); ////aqui temos a alocação dinamica na memoria para que o prato seja armazenado
  novoPedido->id = proximoID++; //atribuição do ID
  novoPedido->pratos = NULL;
  novoPedido->proximo = NULL;

  //Essa estrutura de repetição com o laço i será percorrido o numero de vezes da quantidade de pratos do pedido, pois é desse modo que os pratos serão adicionados
  for (int i = 0; i < qtd; i++) {
    Prato *novo = criarPrato(itens[i], cardapio); //faz a chamada da função criar pratos, rcebe o valor de entrada do usuario com a quantidade de pratos do pedido e recebe o cardapio
    novo->proximo = novoPedido->pratos;
    novoPedido->pratos = novo;
  }

  if (*salao == NULL) { //Se a lista do salão estiver vazia, o novoPedido será o primeiro elemnento da lista
    *salao = novoPedido;
  } else { //caso a lista não estiver vazia, vamos adicionar os pedidos no final lista
    Pedido *atual = *salao;
    while (atual->proximo != NULL) { //repetição que vai percorrendo a lsita até encontara o ultimo elemento
      atual = atual->proximo;
    }
    atual->proximo = novoPedido; //adiciona no fim
  }

  printf("Pedido %d adicionado com %d prato(s).", novoPedido->id, qtd);
}

void adicionarPratoPedido(Pedido *salao, int id, int item, const char *cardapio[]) {
 
    while (salao && salao->id != id) //essa estrutura percorre a lista de pedidos até encontrar o pedido com o ID desejado
        salao = salao->proximo;

    if (salao == NULL) {
        printf("Pedido %d nao encontrado.\n", id);
        return;
    }

    //Cria um novo prato chamando a função (recebe o numero do prato)
    Prato *novo = criarPrato(item, cardapio);
    novo->proximo = salao->pratos;
    salao->pratos = novo; //faz a inserção do prato no pedido

    printf("Prato adicionado ao pedido %d.\n", id);
}

void removerPedido(Pedido *salao, int id, int item) {
    while (salao && salao->id != id) //essa estrutura percorre a lista de pedidos até encontrar o pedido com o ID desejado
        salao = salao->proximo;

    if (salao == NULL) {
        printf("Pedido %d nao encontrado.\n", id);
        return;
    }

    Prato *atual = salao->pratos;
    Prato *anterior = NULL;

    while (atual && atual->item != item) {
        anterior = atual; //Essa esturura vai percorrer todos os pratos do pedido até encontrar o prato com item especificado
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Prato %d nao encontrado no pedido %d.\n", item, id);
        return;
    }

    if (anterior)
        anterior->proximo = atual->proximo; //se o anterior nao for igual a NULL, ela vai ser "ligado ao proximo prato" e o atual vai ser removido
    else
        salao->pratos = atual->proximo; //se o anterior for NULL, o prato era o primeiro da lista

    free(atual);//liberacao da memoria don prato
    printf("Prato %d removido do pedido %d.\n", item, id);
}

void listarPedidos(Pedido *salao) {
    if (salao == NULL) {
        printf("Nenhum pedido no salao.\n");
        return; //se nao houver nenhum pedido
    }

    while (salao) { //o while externo percorre a lista dos pedidos
        printf("Pedido %d:\n", salao->id);
        Prato *p = salao->pratos;
        while (p) {//o while interno percorre todos os pratos do pedido
            printf("  - [%d] %s\n", p->item, p->nome);
            p = p->proximo;
        }
        salao = salao->proximo;
    }
}

void removerPedidoLista(Pedido **salao, int id) {
    if (*salao == NULL) {
        printf("Nenhum pedido no salao.\n");
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
        printf("Pedido %d nao encontrado.\n", id);
        return;
    }

    //Nesse ponto vai ocorrer a remoção do pedido propriamente sendo considerado o caso do incio, meio e fim
    if (anterior == NULL) {
        *salao = atual->proximo; //
    } else {
        anterior->proximo = atual->proximo; 
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
    printf("Pedido %d removido do salao.\n", id);
}
