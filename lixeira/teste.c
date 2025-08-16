#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura básica de produto (com campos essenciais)
typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
} Produto;

// Variáveis globais (com alocação dinâmica)
Produto *produtos = NULL;
int totalProdutos = 0;
int capacidade = 0;

// Função para limpar o buffer do teclado
void limparBuffer() {
    while (getchar() != '\n');
}

// Função para pausar a execução
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

// Função para cadastrar novo produto (COM ALOCAÇÃO DINÂMICA)
void cadastrarProduto() {
    // Aumenta a capacidade se necessário (alocação dinâmica)
    if (totalProdutos >= capacidade) {
        capacidade = (capacidade == 0) ? 5 : capacidade * 2;
        Produto *temp = realloc(produtos, capacidade * sizeof(Produto));
        if (temp == NULL) {
            printf("Erro ao alocar memoria!\n");
            pausar();
            return;
        }
        produtos = temp;
    }

    printf("\n--- Cadastro de Produto ---\n");

    // Lê os dados do novo produto
    printf("Codigo: ");
    scanf("%d", &produtos[totalProdutos].codigo);

    // Verifica se o código já existe
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == produtos[totalProdutos].codigo) {
            printf("Erro: Codigo ja existe!\n");
            pausar();
            return;
        }
    }

    printf("Nome: ");
    limparBuffer();
    fgets(produtos[totalProdutos].nome, 50, stdin);
    produtos[totalProdutos].nome[strcspn(produtos[totalProdutos].nome, "\n")] = '\0';

    printf("Preco: ");
    scanf("%f", &produtos[totalProdutos].preco);

    printf("Estoque: ");
    scanf("%d", &produtos[totalProdutos].estoque);

    totalProdutos++;
    printf("\nProduto cadastrado com sucesso!\n");
    pausar();
}

// Função para listar todos os produtos
void listarProdutos() {
    printf("\n--- Lista de Produtos ---\n");

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        pausar();
        return;
    }

    for (int i = 0; i < totalProdutos; i++) {
        printf("\nProduto %d:\n", i + 1);
        printf("Codigo: %d\n", produtos[i].codigo);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Preco: R$ %.2f\n", produtos[i].preco);
        printf("Estoque: %d\n", produtos[i].estoque);
    }
    pausar();
}

// Menu principal simplificado
void menuPrincipal() {
    int opcao;
    do {
        printf("\n=== SISTEMA PADARIA ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 3);
}

// Função principal
int main() {
    printf("Sistema de Gerenciamento de Padaria\n");

    menuPrincipal();

    // Libera a memória alocada (OBRIGATÓRIO com alocação dinâmica)
    free(produtos);

    return 0;
}