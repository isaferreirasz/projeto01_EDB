#include <stdio.h>
#include <stdlib.h>
#include "salao.h"
#include "cozinha.h"


//Vetor com poteiro respons�vel por armazenar os nomes dos pratos do card�pio
const char *cardapio[] = {
    "Sopa de Cebola", "Salada Caesar", "Bruschetta", "Carpaccio de Carne", "Camarao ao Alho",
"Lasanha a Bolonhesa", "File Mignon com Fritas", "Frango Grelhado com Legumes", "Bacalhau a Gomes de Sa", "Risoto de Cogumelos",
"Tiramisu", "Cheesecake de Frutas Vermelhas", "Mousse de Chocolate", "Pudim de Leite", "Sorvete de Baunilha com Calda de Morango"
};

//Utilizando o vetor implentamos a fun��o, que usa uma estrutura de repeti��o para percorrer o vetor de moto a exibir os pratos em categorias
void listarCardapio() {
    printf("\n=*=*= Card�pio =*=*=\n ==== Entradas ====\n");
    for (int i = 0; i < 5; i++) printf("%2d. %s\n", i+1, cardapio[i]);
    printf("==== Pratos Principais ==== \n");
    for (int i = 5; i < 10; i++) printf("%2d. %s\n", i+1, cardapio[i]);
    printf("==== Sobremesas ====\n ");
    for (int i = 10; i < 15; i++) printf("%2d. %s\n", i+1, cardapio[i]);
}

int main() {
    //Iniciando a lista de pedido com NULL (vazia)
    Pedido *salao = NULL;
    Fila filaCozinha;
    iniciaFila(&filaCozinha); 
    
    int opcao;

    /*Toda a estrutura do do while se utilizando do switch case foi implemntada para funcionar como um menu para o usu�rio, nela cada escolha
    gera um "resultado" para quem usa, � uma implenta��o simples que chama as fun��oes anteriomente impletandas nos outros arquivos.c */
    do {
        printf("\n==== GERENCIAMENTO DE PEDIDOS ====\n");
        printf("1. Adicionar pedido\n");
        printf("2. Adicionar prato a um pedido\n");
        printf("3. Remover prato de um pedido\n");
        printf("4. Listar pedidos no salao\n");
        printf("5. Enviar pedido para a cozinha\n");
        printf("6. Listar pedidos na cozinha\n");
        printf("7. Verificar qual pedido esta pronto\n");
        printf("0. Sair\n");
        printf("Escolha a acao que deseja realizar: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                listarCardapio();
                int qtd;
                printf("Quantos pratos deseja adicionar ao pedido? ");
                scanf("%d", &qtd);

                if (qtd <= 0) {
                    printf("Quantidade invalida.\n");
                    break;
                }

                int itens[qtd];
                int valido = 1;

                for (int i = 0; i < qtd; i++) {
                    printf("Digite o numero do prato (1 a 15): ");
                    scanf("%d", &itens[i]);
                    if (itens[i] < 1 || itens[i] > 15) {
                        printf("Prato invalido.\n");
                        valido = 0;
                        break;
                    }
                }

                if (valido)
                    adicionarPedido(&salao, qtd, itens, cardapio);

                break;
            }

            case 2: {
                int id, item;
                printf("ID do pedido: ");
                scanf("%d", &id);
                printf("Numero do novo prato: ");
                scanf("%d", &item);
                if (item >= 1 && item <= 15){
                    adicionarPratoPedido(salao, id, item, cardapio);
                }else{
                    printf("Prato invalido.\n");
                }
                break;
            }

            case 3: {
                int id, item;
                printf("ID do pedido: ");
                scanf("%d", &id);
                printf("Numero do prato a remover: ");
                scanf("%d", &item);
                removerPedido(salao, id, item);
                break;
            }

            case 4:
                listarPedidos(salao);
                break;

            case 5: {
             int idPedido;
             printf("Digite o ID do pedido para enviar a cozinha: ");
             scanf("%d", &idPedido);
             Pedido *pedidoNoSalao = salao;
                while (pedidoNoSalao != NULL && pedidoNoSalao->id != idPedido) {
                     pedidoNoSalao = pedidoNoSalao->proximo;
                }
    
                if (pedidoNoSalao != NULL) {
                adicionarPedidoCozinha(&filaCozinha, idPedido, pedidoNoSalao->pratos, cardapio);
                removerPedidoLista(&salao, idPedido);
                } else {
                     printf("Pedido %d nao encontrado no salao!\n", idPedido);
                }
                break;
            }
            case 6: {
                listarPedidosCozinha(&filaCozinha, cardapio);
                break;
            }
            case 7: {
                removerPedidoPronto(&filaCozinha, cardapio);
                break;
            }

            case 0:
                printf("Encerrado.\n");
                break;

            default:
                printf("Op��o invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
