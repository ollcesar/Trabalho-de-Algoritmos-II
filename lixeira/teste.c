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

void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

void cadastrarProduto() {
    if (qtdProdutos >= capProdutos) {
        capProdutos = (capProdutos == 0) ? 1 : capProdutos * 2;
        produto *temp = realloc(listaProdutos, capProdutos * sizeof(produto));
        if (temp == NULL) {
            printf("ERRO: Memoria insuficiente!\n");
            pausar();
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
            pausar();
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
    pausar();
}

void listarProdutos() {
    printf("\n--- Lista de Produtos ---\n");
    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        pausar();
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
    pausar();
}

void editarProduto() {
    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado para editar.\n");
        pausar();
        return;
    }

    printf("\n--- Editar Produto ---\n");
    printf("Digite o codigo do produto: ");
    int codigo;
    scanf("%d", &codigo);

    int posicao = -1;
    for (int i = 0; i < qtdProdutos; i++) {
        if (listaProdutos[i].codigoProd == codigo) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        pausar();
        return;
    }

    printf("\nEditando produto: %s\n", listaProdutos[posicao].nomeProd);
    printf("Deixe em branco para manter o valor atual\n");

    printf("Nome atual: %s\n", listaProdutos[posicao].nomeProd);
    printf("Novo nome: ");
    limparBuffer();
    char novoNome[100];
    fgets(novoNome, 100, stdin);
    if (strlen(novoNome) > 1) {
        novoNome[strcspn(novoNome, "\n")] = '\0';
        strcpy(listaProdutos[posicao].nomeProd, novoNome);
    }

    printf("Preco atual: %.2f\n", listaProdutos[posicao].preco);
    printf("Novo preco: ");
    char entradaPreco[20];
    fgets(entradaPreco, 20, stdin);
    if (strlen(entradaPreco) > 1) {
        listaProdutos[posicao].preco = atof(entradaPreco);
    }

    printf("Estoque atual: %d\n", listaProdutos[posicao].estoque);
    printf("Novo estoque: ");
    char entradaEstoque[20];
    fgets(entradaEstoque, 20, stdin);
    if (strlen(entradaEstoque) > 1) {
        listaProdutos[posicao].estoque = atoi(entradaEstoque);
    }

    printf("Fornecedor atual: %s\n", listaProdutos[posicao].nomeFornecedor);
    printf("Novo fornecedor: ");
    char novoFornecedor[100];
    fgets(novoFornecedor, 100, stdin);
    if (strlen(novoFornecedor) > 1) {
        novoFornecedor[strcspn(novoFornecedor, "\n")] = '\0';
        strcpy(listaProdutos[posicao].nomeFornecedor, novoFornecedor);
    }

    printf("Telefone atual: %ld\n", listaProdutos[posicao].foneFornecedor);
    printf("Novo telefone: ");
    char entradaTelefone[20];
    fgets(entradaTelefone, 20, stdin);
    if (strlen(entradaTelefone) > 1) {
        listaProdutos[posicao].foneFornecedor = atol(entradaTelefone);
    }

    printf("\nProduto atualizado com sucesso!\n");
    pausar();
}

void excluirProduto() {
    if (qtdProdutos == 0) {
        printf("Nenhum produto para excluir.\n");
        pausar();
        return;
    }

    printf("\n--- Excluir Produto ---\n");
    printf("Digite o codigo do produto: ");
    int codigo;
    scanf("%d", &codigo);

    int posicao = -1;
    for (int i = 0; i < qtdProdutos; i++) {
        if (listaProdutos[i].codigoProd == codigo) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Produto nao encontrado!\n");
        pausar();
        return;
    }

    for (int i = posicao; i < qtdProdutos - 1; i++) {
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
    pausar();
}

void menuProdutos() {
    int opcao;
    do {
        printf("\n=== MENU PRODUTOS ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Editar produto\n");
        printf("4. Excluir produto\n");
        printf("5. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: editarProduto(); break;
            case 4: excluirProduto(); break;
            case 5: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
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
            case 2: printf("\nModulo de funcionarios em desenvolvimento...\n"); pausar(); break;
            case 3: printf("\nEncerrando sistema...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 3);

    free(listaProdutos);
    free(listaFuncionarios);
    free(listaVendas);

    return 0;
}