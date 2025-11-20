#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Struct representando um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 = baixa | 5 = altíssima
} Item;

// Vetor de Itens
Item mochila[MAX_ITENS];
int totalItens = 0;

// Flag para saber se está ordenado por nome (necessário para a busca binária)
bool ordenadoPorNome = false;

// -------- Funções Utilitárias -------- //

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// -------- CRUD do Inventário -------- //

void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia! Remova algo antes.\n");
        return;
    }

    Item novo;

    printf("\nDigite o nome do item: ");
    scanf(" %29[^\n]", novo.nome);

    printf("Digite o tipo (arma, munição, cura, etc): ");
    scanf(" %19[^\n]", novo.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    do {
        printf("Digite a prioridade (1 a 5): ");
        scanf("%d", &novo.prioridade);
    } while (novo.prioridade < 1 || novo.prioridade > 5);

    mochila[totalItens++] = novo;
    ordenadoPorNome = false;

    printf("\n✔️ Item adicionado com sucesso!\n");
}

void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️ A mochila está vazia!\n");
        return;
    }

    char busca[30];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %29[^\n]", busca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, busca) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("🗑️ Item removido!\n");
            return;
        }
    }

    printf("❌ Item não encontrado!\n");
}

void listarItens() {
    if (totalItens == 0) {
        printf("\n📭 Mochila vazia!\n");
        return;
    }

    printf("\n🎒 Itens na Mochila (%d/%d):\n", totalItens, MAX_ITENS);
    for (int i = 0; i < totalItens; i++) {
        printf("\n[%d] Nome: %s\n   Tipo: %s\n   Quantidade: %d\n   Prioridade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
}

// -------- Ordenação (Insertion Sort) -------- //

int insertionSort(int criterio) {
    int comparacoes = 0;
    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            int cmp = 0;

            if (criterio == 1)
                cmp = strcmp(chave.nome, mochila[j].nome);
            else if (criterio == 2)
                cmp = strcmp(chave.tipo, mochila[j].tipo);
            else
                cmp = chave.prioridade - mochila[j].prioridade;

            if (cmp < 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else break;
        }

        mochila[j + 1] = chave;
    }
    return comparacoes;
}

void ordenarItens() {
    if (totalItens == 0) {
        printf("\n⚠️ Nada para ordenar!\n");
        return;
    }

    int opcao;
    printf("\nOrdenar por:\n1. Nome\n2. Tipo\n3. Prioridade\n> ");
    scanf("%d", &opcao);

    int comparacoes = insertionSort(opcao);

    ordenadoPorNome = (opcao == 1);

    printf("\n✔️ Mochila ordenada com sucesso!\n");
    printf("📊 Comparações realizadas: %d\n", comparacoes);
}

// -------- Busca Binária -------- //

void buscarBinaria() {
    if (!ordenadoPorNome) {
        printf("\n⚠️ A lista precisa estar ordenada por NOME para usar busca binária!\n");
        return;
    }

    char busca[30];
    printf("\nDigite o nome do item para buscar: ");
    scanf(" %29[^\n]", busca);

    int ini = 0, fim = totalItens - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(busca, mochila[meio].nome);

        if (cmp == 0) {
            printf("\n🔎 Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo,
                   mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        }
        else if (cmp > 0) ini = meio + 1;
        else fim = meio - 1;
    }

    printf("❌ Item não encontrado!\n");
}

// -------- MENU -------- //

int main() {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("  MOCHILA DE SOBREVIVÊNCIA - NIVEL MESTRE\n");
        printf("====================================\n");
        printf("Itens na Mochila: %d/%d\n\n", totalItens, MAX_ITENS);
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Ordenar Mochila\n");
        printf("5. Buscar Item (Binária)\n");
        printf("0. Sair\n------------------------------------\n> ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: adicionarItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: ordenarItens(); break;
            case 5: buscarBinaria(); break;
            case 0: printf("\nSaindo... Até a próxima missão! 🌴\n"); break;
            default: printf("\n⚠️ Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
