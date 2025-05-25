#include <stdio.h>
#include <stdlib.h>
#include "salao.h"
#include "cozinha.h"


//Vetor com poteiro responsável por armazenar os nomes dos pratos do cardápio
const char *cardapio[] = {
    "Sopa de Cebola", "Salada Caesar", "Bruschetta", "Carpaccio de Carne", "Camarao ao Alho",
"Lasanha a Bolonhesa", "File Mignon com Fritas", "Frango Grelhado com Legumes", "Bacalhau a Gomes de Sa", "Risoto de Cogumelos",
"Tiramisu", "Cheesecake de Frutas Vermelhas", "Mousse de Chocolate", "Pudim de Leite", "Sorvete de Baunilha com Calda de Morango"
};

//Função que utiliza estrutura de repetição para percorrer o vetor com ponteiro e lista os pratos do cardápio em categorias
void listarCardapio() {
    printf("\n=*=*= Cardapio =*=*=\n ==== Entradas ====\n");
    for (int i = 0; i < 5; i++) printf("%2d. %s\n", i+1, cardapio[i]);
    printf("==== Pratos Principais ==== \n");
    for (int i = 5; i < 10; i++) printf("%2d. %s\n", i+1, cardapio[i]);
    printf("==== Sobremesas ====\n ");
    for (int i = 10; i < 15; i++) printf("%2d. %s\n", i+1, cardapio[i]);
}

int main() {
    Pedido *salao = NULL; //Iniciando a lista de pedido com NULL (vazia)
    Fila filaCozinha; //Definindo uma fila que representará a cozinha do tipo Fila (estrutura definida no cozinha.h)
    iniciaFila(&filaCozinha);  //Chamada de função que inicializa a fila criada (filaCozinha)
    int opcao; //variável para controlar qual opção o usuário seleciona ao usar o menu de gerenciamento de pedidos

    /*Toda a estrutura do do while utilizando do switch case foi implemntada para funcionar como um menu para o usuário, nela cada escolha
    gera um "resultado" para quem usa, é uma implentação simples que chama as funções anteriormente implementadas nos outros arquivos.c */
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
            case 1: { //Na opção 1, adicionamos um pedido ao salão
                listarCardapio(); //Chamada da função que lista o cardápio 
                int qtd; //Variável de controle para quantidade de pratos no pedido
                printf("Quantos pratos deseja adicionar ao pedido? ");
                scanf("%d", &qtd);

                if (qtd <= 0) { //Se a quantidade de pratos for menor ou igual que 0, avisa que a quantidade é inválida
                    printf("Quantidade invalida.\n");
                    break;
                }

                int itens[qtd]; //Cria um vetor para receber os itens do pedido com o tamanho da quantidade de pratos definida pelo usuário
                int valido = 1; //Define a variável valido como verdadeiro 

                for (int i = 0; i < qtd; i++) { //Itera i enquanto i for menor que a quantidade de pratos do pedido
                    printf("Digite o numero do prato (1 a 15): "); //Para cada posição do vetor de itens, é pedido o ID do prato desejado
                    scanf("%d", &itens[i]);
                    if (itens[i] < 1 || itens[i] > 15) { //Verifica se o ID do pedido é válido 
                        printf("Prato invalido.\n"); 
                        valido = 0; //Se não for válido, a variável valido recebe o valor de falso e não adiciona o prato ao pedido 
                        break;
                    }
                }

                if (valido) //Se valido for verdadeiro, o pedido é adicionado
                //Chama a função de adicionar um novo pedindo passando como parâmetro a lista salao, a quantidade de pratos do pedido, o vetor com os pratos do pedido e o cardápio
                    adicionarPedido(&salao, qtd, itens, cardapio); 
                break;
            }

            case 2: { //Na opção dois, adicionamos um novo prato a um pedido já existente
                int id, item; //Declara uma variável para receber o id do pedido e uma variável para receber o id do item do novo prato
                printf("ID do pedido: ");
                scanf("%d", &id); //Recebe o ID do pedido que deseja adicionar um novo prato
                printf("Numero do novo prato: ");
                scanf("%d", &item); //Recebe o id do item do cardápio que deseja inserir no pedido
                if (item >= 1 && item <= 15){ //Verifica se o item é um prato válido
                //Chama a função que adiciona um novo prato ao pedido passando como parâmetros a lista do salao, o id do pedido, o item do cardápio que vai ser adicionado e o cardápio
                    adicionarPratoPedido(salao, id, item, cardapio); 
                }else{
                    printf("Prato invalido.\n"); //Se o item digitado não for um prato válido, retorna essa mensagem
                }
                break;
            }

            case 3: { //Na opção três, removemos um prato de um pedido já existente
                int id, item; //Declara uma variável para receber o id do pedido e uma variável para receber o id do item do prato que vai ser removido
                printf("ID do pedido: ");
                scanf("%d", &id); //Recebe o ID do prato que deseja remover um prato
                printf("Numero do prato a remover: ");
                scanf("%d", &item); //Recebe o id do item do cardápio que vai ser removido do pedido
                //Chama a função que remove o prato do pedido passando como parâmetros a lista do salão, o id do pedido e o item que vai ser removido
                removerPedido(salao, id, item); 
                break;
            }

            case 4: //Na opção 4, listamos todos os pedidos que estão no salão
                listarPedidos(salao); //Chama a função que lista os pedidos passando como parâmetro a lista do salão
                break;

            case 5: { //Na opção cinco, mandamos um pedido do salão para a cozinha
             int idPedido; //Variável pare receber o id do pedido que vai ser mandado para à cozinha
             printf("Digite o ID do pedido para enviar a cozinha: ");
             scanf("%d", &idPedido); //Recebe o id do pedido 
             Pedido *pedidoNoSalao = salao; //Declara um ponteiro do tipo Pedido que recebe os elementos da lista salao que contém os pedidos que estão no salão
            //Percorre a lista dos pedidos do salão enquanto for diferente de nulo e o id do pedido verificado não for igual o id do pedido que o usuário deseja mandar para a cozinha
                while (pedidoNoSalao != NULL && pedidoNoSalao->id != idPedido) {  
                     pedidoNoSalao = pedidoNoSalao->proximo; //Passa para o próximo pedido do salão para fazer a mesma verificação
                }
    
                if (pedidoNoSalao != NULL) { //Se pedidoNoSalao for diferente de vazio,  manda o pedido para a cozinha e remove o pedido do salão
                //Chama a função de adicionar pedido na cozinha passando como parâmetros a fila da cozinha, o id do pedido que vai ser adicionado, os pratos desse pedido e o cardapio
                adicionarPedidoCozinha(&filaCozinha, idPedido, pedidoNoSalao->pratos, cardapio);
                //Chama a função que remove o pedido do salão passando a lista salao e o id do pedido que vai ser removido
                removerPedidoLista(&salao, idPedido);
                } else { //Se pedidoNoSalao for vazio, significa que o id do pedido digitado não foi encontrado no salão
                     printf("Pedido %d nao encontrado no salao!\n", idPedido);
                }
                break;
            }
            case 6: { //Na opção seis, listamos todos os pedidos que estão na cozinha
            //Chama a função de listar os pedidos da cozinha passando como parâmetro a fila que representa a cozinha e o cardápio
                listarPedidosCozinha(&filaCozinha, cardapio); 
                break;
            }
            case 7: { //Na opção sete, mostramos qual pedido está saindo pronto da cozinha 
            //Chama a função de remover o pedido pronto da cozinha passando como parâmetro a fila da cozinha e o cardápio, assim removendo o primeiro elemento da fila
                removerPedidoPronto(&filaCozinha, cardapio); 
                break;
            }

            case 0: //Na opção zero, o programa é encerrado
                printf("Encerrado.\n");
                break;

            default: //Opção inválida para caso o usuário digite um número que não está nas opções disponíveis 
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0); //O while acontece enquanto opção for diferente de zero, pois a opção zero encerra o programa

    return 0;
}
