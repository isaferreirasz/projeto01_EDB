#include "salao.h"

const char *cardapio[] = {
    "Sopa de Cebola", "Salada Caesar", "Bruschetta", "Carpaccio de Carne", "Camarão ao Alho",
    "Lasanha à Bolonhesa", "Filé Mignon com Fritas", "Frango Grelhado com Legumes", "Bacalhau à Gomes de Sá", "Risoto de Cogumelos",
    "Tiramisu", "Cheesecake de Frutas Vermelhas", "Mousse de Chocolate", "Pudim de Leite", "Sorvete de Baunilha com Calda de Morango"
};

void listarCardapio() {
    printf("\n=*=*= Cardápio =*=*=\n ==== Entradas ====\n");
    for (int i = 0; i < 5; i++) printf("%2d. %s\n", i+1, cardapio[i]);
    printf("==== Pratos Principais ==== \n");
    for (int i = 5; i < 10; i++) printf("%2d. %s\n", i+1, cardapio[i]);
    printf("==== Sobremesas ====\n ");
    for (int i = 10; i < 15; i++) printf("%2d. %s\n", i+1, cardapio[i]);
}

void menu() {
    printf("\n==== GERENCIAMENTO DE PEDIDOS ====\n");
    printf("1. Adicionar Pedido (Salão)\n");
    printf("2. Remover Prato (Salão)\n");
    printf("3. Processar Pedido (para Cozinha)\n");
    printf("4. Listar Salão\n");
    printf("5. Listar Cozinha\n");
    printf("0. Sair\n");
    printf("Digite a opção desejada: ");
}

int main() {
    No *salao = NULL;
    No *cozinha = NULL;
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                listarCardapio();
                int item;
                printf("Digite o número do prato: ");
                scanf("%d", &item);
                getchar();
                if (item < 1 || item > 15) {
                    printf("Item inválido!\n");
                    break;
                }
                adicionarPedidoSalao(&salao, cardapio[item-1], item);
                printf("Pedido adicionado.\n");
                break;
            }
            case 2: {
                int item;
                printf("Digite o número do prato a remover: ");
                scanf("%d", &item);
                getchar();
                if (removerFim(&salao, item))
                    printf("Pedido removido.\n");
                else
                    printf("Pedido não encontrado.\n");
                break;
            }
            case 3: {
                No *pedido = enviarPedidoCozinha(&salao);
                if (pedido== NULL) {
                    printf("Nenhum pedido para processar.\n");
                } 
            }
            case 4: 
                listarPedidosSalao(salao); 
                break;
            case 5: 
                printf("Cozinha");
            case 0: 
                printf("Encerrado.\n"); 
                break;
            default: 
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
