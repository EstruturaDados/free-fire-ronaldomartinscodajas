#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// -------------------------------
// Struct que representa um item do inventário
// -------------------------------
typedef struct {
    char nome[30];   // Nome do item (ex: MP40)
    char tipo[20];   // Tipo (ex: arma, munição, cura)
    int quantidade;  // Quantidade do item
} Item;

// -------------------------------
// Função: Inserir novo item na mochila
// -------------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n⚠️ Limite máximo de itens atingido!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %29[^\n]", mochila[*total].nome);

    printf("Digite o tipo do item (arma, munição, cura, etc): ");
    scanf(" %19[^\n]", mochila[*total].tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;

    printf("\n✔️ Item adicionado com sucesso!\n");
}

// -------------------------------
// Função: Remover item pelo nome
// -------------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n📦 A mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %29[^\n]", nomeRemover);

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Move os itens seguintes para "preencher" o espaço
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("\n🗑️ Item removido com sucesso!\n");
            return;
        }
    }

    printf("\n❌ Item não encontrado!\n");
}

// -------------------------------
// Função: Listar todos os itens cadastrados
// -------------------------------
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\n📦 Nenhum item cadastrado!\n");
        return;
    }

    printf("\n📋 Itens na Mochila:\n");
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

// -------------------------------
// Função: Buscar item pelo nome (busca sequencial)
// -------------------------------
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\n📦 A mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    scanf(" %29[^\n]", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔎 Item encontrado!\n");
            printf("----------------------------------------------\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            printf("----------------------------------------------\n");
            return;
        }
    }

    printf("\n❌ Item não encontrado!\n");
}

// -------------------------------
// Função principal: Menu do sistema
// -------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n========== MENU ==========\n");
        printf("1️⃣  Adicionar item\n");
        printf("2️⃣  Remover item\n");
        printf("3️⃣  Listar itens\n");
        printf("4️⃣  Buscar item\n");
        printf("0️⃣  Sair\n");
        printf("==========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("\n🏝️ Mochila fechada! Boa sorte na ilha!\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
