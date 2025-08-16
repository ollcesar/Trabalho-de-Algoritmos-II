#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} data;

typedef struct {
    int codigoProd;
    char nomeProd[100];
    float preco;
    int estoque;
    char nomeFornecedor[100];
    long int foneFornecedor;
} produto;

typedef struct {
    int matricula;
    char nomeFunc[100];
    char cargo[100];
    float salario;
    char login[100];
    char senha[50];
} funcionario;

typedef struct {
    int codigoVenda;
    int prodVendido;
    int vendedor;
    data diaDaVenda;
    int quantidadeVendida;
} venda;

produto *listaProdutos = NULL;
int qtdProdutos = 0;
int capProdutos = 0;

funcionario *listaFuncionarios = NULL;
int qtdFuncionarios = 0;
int capFuncionarios = 0;

venda *listaVendas = NULL;
int qtdVendas = 0;
int capVendas = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarProduto() {
    if (qtdProdutos >= capProdutos) {
        capProdutos = (capProdutos == 0) ? 1 : capProdutos * 2;
        produto *temp = realloc(listaProdutos, capProdutos * sizeof(produto));
        if (temp == NULL) {
            printf("ERRO: Memoria insuficiente!\n");
            return;
        }
        listaProdutos = temp;
    }

    printf("\n--- Cadastro de Produto ---\n");
    printf("Codigo: ");
    scanf("%d", &listaProdutos[qtdProdutos].codigoProd);

    for (int i = 0; i < qtdProdutos; i++) {
        if (listaProdutos[i].codigoProd == listaProdutos[qtdProdutos].codigoProd) {
            printf("ERRO: Codigo ja existe!\n");
            return;
        }
    }

    printf("Nome: ");
    limparBuffer();
    fgets(listaProdutos[qtdProdutos].nomeProd, 100, stdin);
    listaProdutos[qtdProdutos].nomeProd[strcspn(listaProdutos[qtdProdutos].nomeProd, "\n")] = '\0';

    printf("Preco: ");
    scanf("%f", &listaProdutos[qtdProdutos].preco);

    printf("Estoque: ");
    scanf("%d", &listaProdutos[qtdProdutos].estoque);
    limparBuffer();

    printf("Fornecedor: ");
    fgets(listaProdutos[qtdProdutos].nomeFornecedor, 100, stdin);
    listaProdutos[qtdProdutos].nomeFornecedor[strcspn(listaProdutos[qtdProdutos].nomeFornecedor, "\n")] = '\0';

    printf("Telefone fornecedor: ");
    scanf("%ld", &listaProdutos[qtdProdutos].foneFornecedor);

    qtdProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos() {
    printf("\n--- Lista de Produtos ---\n");
    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdProdutos; i++) {
        printf("\nProduto %d:\n", i+1);
        printf("Codigo: %d\n", listaProdutos[i].codigoProd);
        printf("Nome: %s\n", listaProdutos[i].nomeProd);
        printf("Preco: %.2f\n", listaProdutos[i].preco);
        printf("Estoque: %d\n", listaProdutos[i].estoque);
        printf("Fornecedor: %s\n", listaProdutos[i].nomeFornecedor);
        printf("Telefone: %ld\n", listaProdutos[i].foneFornecedor);
    }
}

void excluirProduto() {
    if (qtdProdutos == 0) {
        printf("Nenhum produto para excluir.\n");
        return;
    }

    int codigo;
    printf("Codigo do produto a excluir: ");
    scanf("%d", &codigo);

    int pos = -1;
    for (int i = 0; i < qtdProdutos; i++) {
        if (listaProdutos[i].codigoProd == codigo) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    for (int i = pos; i < qtdProdutos - 1; i++) {
        listaProdutos[i] = listaProdutos[i + 1];
    }

    qtdProdutos--;

    produto *temp = realloc(listaProdutos, qtdProdutos * sizeof(produto));
    if (qtdProdutos > 0 && temp == NULL) {
        printf("Aviso: Nao foi possivel reduzir a memoria!\n");
    } else {
        listaProdutos = temp;
        capProdutos = qtdProdutos;
    }

    printf("Produto excluido com sucesso!\n");
}

void menuProdutos() {
    int opcao;
    do {
        printf("\n=== MENU PRODUTOS ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Excluir produto\n");
        printf("4. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: excluirProduto(); break;
            case 4: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 4);
}

int main() {
    printf("Sistema Padaria - Carregado\n");

    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Produtos\n");
        printf("2. Funcionarios\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: menuProdutos(); break;
            case 2: break;
            case 3: printf("Encerrando sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 3);

    free(listaProdutos);
    free(listaFuncionarios);
    free(listaVendas);

    return 0;
}