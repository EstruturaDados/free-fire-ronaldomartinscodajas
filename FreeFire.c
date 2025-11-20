#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ---------------------------------------------
// Struct Item: representa os itens da mochila
// ---------------------------------------------
typedef struct {
    char nome[30];   // Nome do item (ex: AK-47, Kit Médico)
    char tipo[20];   // Tipo do item (arma, munição, cura, etc.)
    int quantidade;  // Quantidade do item
} Item;

// ---------------------------------------------
// Inserir novo item
// ---------------------------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n🎒 Adicionando item ao inventário:\n");

    printf("Nome do item: ");
    scanf(" %29[^\n]", mochila[*total].nome);

    printf("Tipo (arma, munição, cura...): ");
    scanf(" %19[^\n]", mochila[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;

    printf("\n✔️ Item adicionado com sucesso!\n");
}

// ---------------------------------------------
// Remover item pelo nome
// ---------------------------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n📦 A mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\n🗑️ Digite o nome do item para remover: ");
    scanf(" %29[^\n]", nomeRemover);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("\n✔️ Item removido com sucesso!\n");
            return;
        }
    }
    printf("\n❌ Item não encontrado!\n");
}

// ---------------------------------------------
// Listar todos os itens cadastrados
// ---------------------------------------------
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\n📦 Nenhum item na mochila!\n");
        return;
    }

    printf("\n📋 Itens armazenados:\n");
    printf("----------------------------------------------\n");
    printf("%-15s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("----------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-15s %-15s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("----------------------------------------------\n");
}

// ---------------------------------------------
// Buscar item pelo nome (busca sequencial)
// ---------------------------------------------
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\n📦 Mochila vazia! Nada para buscar.\n");
        return;
    }

    char nomeBusca[30];
    int encontrado = 0;

    printf("\n🔎 Digite o nome do item para buscar: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🎯 Item encontrado!\n");
            printf("--------------------------------------\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("--------------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado! Continue explorando!\n");
    }
}

// ---------------------------------------------
// Função Principal (menu)
// ---------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        system("clear || cls"); // Limpa a tela no Windows e Linux

        printf("====================================\n");
        printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("====================================\n");
        printf("Itens na Mochila: %d/%d\n\n", totalItens, MAX_ITENS);

        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("------------------------------------\n");
        printf("Escolha sua opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(mochila, &totalItens); break;
            case 2: removerItem(mochila, &totalItens); break;
            case 3: listarItens(mochila, totalItens); break;
            case 4: buscarItem(mochila, totalItens); break;
            case 0: printf("\n🏝️ Mochila fechada! Boa sorte na ilha!\n"); break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

        printf("\nPressione ENTER para voltar ao menu...");
        getchar(); getchar();

    } while (opcao != 0);

    return 0;
}
