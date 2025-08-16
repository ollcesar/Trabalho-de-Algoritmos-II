//ESPERO QUE ESSA COISA FUNCIONE PQ SO DEUS SABE COMO TA A VEIA DA MINHA TESTA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ESTRUTURAS
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
    char foneFornecedor[20];
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

// VARIÁVEIS GLOBAIS ATE QUE SEJA POSSIVEL USAR ARQUIVOOOOOO
produto *listaProdutos = NULL;
int qtdProdutos = 0;
int capProdutos = 0;

funcionario *listaFuncionarios = NULL;
int qtdFuncionarios = 0;
int capFuncionarios = 0;

venda *listaVendas = NULL;
int qtdVendas = 0;
int capVendas = 0;

// FUNÇÃO PARA LIMPAR BUFFER
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// FUNÇÃO PARA PAUSAR
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

// FUNÇÕES PARA PRODUTOS
int buscarProduto(int codigo) {
    for (int i = 0; i < qtdProdutos; i++) {
        if (listaProdutos[i].codigoProd == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarProduto() {
    if (qtdProdutos >= capProdutos) {
        if (capProdutos == 0) {
            capProdutos = 1;
        } else {
            capProdutos = capProdutos + 1;
        }
        produto *temp = realloc(listaProdutos, capProdutos * sizeof(produto));
        if (temp == NULL) {
            printf("ERRO: Falha ao alocar memoria!\n");
            pausar();
            return;
        }
        listaProdutos = temp;
    }

    printf("\n--- Cadastrar Produto ---\n");

    printf("Codigo: ");
    scanf("%d", &listaProdutos[qtdProdutos].codigoProd);

    if (buscarProduto(listaProdutos[qtdProdutos].codigoProd) != -1) {
        printf("ERRO: Codigo ja existe!\n");
        pausar();
        return;
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
    //limparBuffer();
    fgets(listaProdutos[qtdProdutos].foneFornecedor, 20, stdin);  // Alterado para fgets
    listaProdutos[qtdProdutos].foneFornecedor[strcspn(listaProdutos[qtdProdutos].foneFornecedor, "\n")] = '\0';

    qtdProdutos++;
    printf("\nProduto cadastrado com sucesso!\n");
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
        printf("Telefone: %s\n", listaProdutos[i].foneFornecedor);
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

    int pos = buscarProduto(codigo);
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        pausar();
        return;
    }

    printf("\nEditando produto: %s\n", listaProdutos[pos].nomeProd);

    printf("Novo nome (atual: %s): ", listaProdutos[pos].nomeProd);
    limparBuffer();
    char novoNome[100];
    fgets(novoNome, 100, stdin);
    if (strlen(novoNome) > 1) {
        novoNome[strcspn(novoNome, "\n")] = '\0';
        strcpy(listaProdutos[pos].nomeProd, novoNome);
    }

    printf("Novo preco (atual: %.2f): ", listaProdutos[pos].preco);
    float novoPreco;
    if (scanf("%f", &novoPreco) == 1) {
        listaProdutos[pos].preco = novoPreco;
    }
    limparBuffer();

    printf("Novo estoque (atual: %d): ", listaProdutos[pos].estoque);
    int novoEstoque;
    if (scanf("%d", &novoEstoque) == 1) {
        listaProdutos[pos].estoque = novoEstoque;
    }
    limparBuffer();

    printf("Novo fornecedor (atual: %s): ", listaProdutos[pos].nomeFornecedor);
    char novoFornecedor[100];
    fgets(novoFornecedor, 100, stdin);
    if (strlen(novoFornecedor) > 1) {
        novoFornecedor[strcspn(novoFornecedor, "\n")] = '\0';
        strcpy(listaProdutos[pos].nomeFornecedor, novoFornecedor);
    }

    printf("Novo telefone (atual: %s): ", listaProdutos[pos].foneFornecedor);
    char novoTelefone[20];
    //limparBuffer();
    fgets(novoTelefone, 20, stdin);
    if (strlen(novoTelefone) > 1) {
        novoTelefone[strcspn(novoTelefone, "\n")] = '\0';
        strcpy(listaProdutos[pos].foneFornecedor, novoTelefone);
    }

    printf("\nProduto atualizado com sucesso!\n");
    pausar();
}

void excluirProduto() {
    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado para excluir.\n");
        pausar();
        return;
    }

    printf("\n--- Excluir Produto ---\n");
    printf("Digite o codigo do produto: ");
    int codigo;
    scanf("%d", &codigo);

    int pos = buscarProduto(codigo);
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        pausar();
        return;
    }

    printf("\nProduto a ser excluido:\n");
    printf("Codigo: %d\n", listaProdutos[pos].codigoProd);
    printf("Nome: %s\n", listaProdutos[pos].nomeProd);

    printf("\nTem certeza? (s/n): ");
    char confirmacao;
    limparBuffer();
    scanf("%c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Operacao cancelada.\n");
        pausar();
        return;
    }

    for (int i = pos; i < qtdProdutos - 1; i++) {
        listaProdutos[i] = listaProdutos[i + 1];
    }

    qtdProdutos--;

    produto *temp = realloc(listaProdutos, qtdProdutos * sizeof(produto));
    if (qtdProdutos > 0 && temp == NULL) {
        printf("AVISO: Nao foi possivel reduzir a memoria!\n");
    } else {
        listaProdutos = temp;
        capProdutos = qtdProdutos;
    }

    printf("\nProduto excluido com sucesso!\n");
    pausar();
}

// FUNÇÕES PARA FUNCIONÁRIOS
int buscarFuncionario(int matricula) {
    for (int i = 0; i < qtdFuncionarios; i++) {
        if (listaFuncionarios[i].matricula == matricula) {
            return i;
        }
    }
    return -1;
}

void cadastrarFuncionario() {
    if (qtdFuncionarios >= capFuncionarios) {
        if (capFuncionarios == 0) {
            capFuncionarios = 1;
        } else {
            capFuncionarios = capFuncionarios + 1;
        }

        funcionario *temp = realloc(listaFuncionarios, capFuncionarios * sizeof(funcionario));
        if (temp == NULL) {
            printf("ERRO: Falha ao alocar memoria!\n");
            pausar();
            return;
        }
        listaFuncionarios = temp;
    }

    printf("\n--- Cadastrar Funcionario ---\n");

    printf("Matricula: ");
    scanf("%d", &listaFuncionarios[qtdFuncionarios].matricula);

    if (buscarFuncionario(listaFuncionarios[qtdFuncionarios].matricula) != -1) {
        printf("ERRO: Matricula ja existe!\n");
        pausar();
        return;
    }

    printf("Nome: ");
    limparBuffer();
    fgets(listaFuncionarios[qtdFuncionarios].nomeFunc, 100, stdin);
    listaFuncionarios[qtdFuncionarios].nomeFunc[strcspn(listaFuncionarios[qtdFuncionarios].nomeFunc, "\n")] = '\0';

    printf("Cargo: ");
    fgets(listaFuncionarios[qtdFuncionarios].cargo, 100, stdin);
    listaFuncionarios[qtdFuncionarios].cargo[strcspn(listaFuncionarios[qtdFuncionarios].cargo, "\n")] = '\0';

    printf("Salario: ");
    scanf("%f", &listaFuncionarios[qtdFuncionarios].salario);
    limparBuffer();

    printf("Login: ");
    fgets(listaFuncionarios[qtdFuncionarios].login, 100, stdin);
    listaFuncionarios[qtdFuncionarios].login[strcspn(listaFuncionarios[qtdFuncionarios].login, "\n")] = '\0';

    printf("Senha: ");
    fgets(listaFuncionarios[qtdFuncionarios].senha, 50, stdin);
    listaFuncionarios[qtdFuncionarios].senha[strcspn(listaFuncionarios[qtdFuncionarios].senha, "\n")] = '\0';

    qtdFuncionarios++;
    printf("\nFuncionario cadastrado com sucesso!\n");
    pausar();
}

void listarFuncionarios() {
    printf("\n--- Lista de Funcionarios ---\n");
    if (qtdFuncionarios == 0) {
        printf("Nenhum funcionario cadastrado.\n");
        pausar();
        return;
    }

    for (int i = 0; i < qtdFuncionarios; i++) {
        printf("\nFuncionario %d:\n", i+1);
        printf("Matricula: %d\n", listaFuncionarios[i].matricula);
        printf("Nome: %s\n", listaFuncionarios[i].nomeFunc);
        printf("Cargo: %s\n", listaFuncionarios[i].cargo);
        printf("Salario: %.2f\n", listaFuncionarios[i].salario);
        printf("Login: %s\n", listaFuncionarios[i].login);
    }
    pausar();
}

void editarFuncionario() {
    if (qtdFuncionarios == 0) {
        printf("Nenhum funcionario cadastrado para editar.\n");
        pausar();
        return;
    }

    printf("\n--- Editar Funcionario ---\n");
    printf("Digite a matricula do funcionario: ");
    int matricula;
    scanf("%d", &matricula);

    int pos = buscarFuncionario(matricula);
    if (pos == -1) {
        printf("Funcionario nao encontrado!\n");
        pausar();
        return;
    }

    printf("\nEditando funcionario: %s\n", listaFuncionarios[pos].nomeFunc);

    printf("Novo nome (atual: %s): ", listaFuncionarios[pos].nomeFunc);
    limparBuffer();
    char novoNome[100];
    fgets(novoNome, 100, stdin);
    if (strlen(novoNome) > 1) {
        novoNome[strcspn(novoNome, "\n")] = '\0';
        strcpy(listaFuncionarios[pos].nomeFunc, novoNome);
    }

    printf("Novo cargo (atual: %s): ", listaFuncionarios[pos].cargo);
    char novoCargo[100];
    fgets(novoCargo, 100, stdin);
    if (strlen(novoCargo) > 1) {
        novoCargo[strcspn(novoCargo, "\n")] = '\0';
        strcpy(listaFuncionarios[pos].cargo, novoCargo);
    }

    printf("Novo salario (atual: %.2f): ", listaFuncionarios[pos].salario);
    float novoSalario;
    if (scanf("%f", &novoSalario) == 1) {
        listaFuncionarios[pos].salario = novoSalario;
    }
    limparBuffer();

    printf("Novo login (atual: %s): ", listaFuncionarios[pos].login);
    char novoLogin[100];
    fgets(novoLogin, 100, stdin);
    if (strlen(novoLogin) > 1) {
        novoLogin[strcspn(novoLogin, "\n")] = '\0';
        strcpy(listaFuncionarios[pos].login, novoLogin);
    }

    printf("Nova senha (atual: *****): ");
    char novaSenha[50];
    fgets(novaSenha, 50, stdin);
    if (strlen(novaSenha) > 1) {
        novaSenha[strcspn(novaSenha, "\n")] = '\0';
        strcpy(listaFuncionarios[pos].senha, novaSenha);
    }

    printf("\nFuncionario atualizado com sucesso!\n");
    pausar();
}

void excluirFuncionario() {
    if (qtdFuncionarios == 0) {
        printf("Nenhum funcionario cadastrado para excluir.\n");
        pausar();
        return;
    }

    printf("\n--- Excluir Funcionario ---\n");
    printf("Digite a matricula do funcionario: ");
    int matricula;
    scanf("%d", &matricula);

    int pos = buscarFuncionario(matricula);
    if (pos == -1) {
        printf("Funcionario nao encontrado!\n");
        pausar();
        return;
    }

    printf("\nFuncionario a ser excluido:\n");
    printf("Matricula: %d\n", listaFuncionarios[pos].matricula);
    printf("Nome: %s\n", listaFuncionarios[pos].nomeFunc);

    printf("\nTem certeza? (s/n): ");
    char confirmacao;
    limparBuffer();
    scanf("%c", &confirmacao);

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Operacao cancelada.\n");
        pausar();
        return;
    }

    for (int i = pos; i < qtdFuncionarios - 1; i++) {
        listaFuncionarios[i] = listaFuncionarios[i + 1];
    }

    qtdFuncionarios--;

    funcionario *temp = realloc(listaFuncionarios, qtdFuncionarios * sizeof(funcionario));
    if (qtdFuncionarios > 0 && temp == NULL) {
        printf("AVISO: Nao foi possivel reduzir a memoria!\n");
    } else {
        listaFuncionarios = temp;
        capFuncionarios = qtdFuncionarios;
    }

    printf("\nFuncionario excluido com sucesso!\n");
    pausar();
}

// MENUS
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

void menuFuncionarios() {
    int opcao;
    do {
        printf("\n=== MENU FUNCIONARIOS ===\n");
        printf("1. Cadastrar funcionario\n");
        printf("2. Listar funcionarios\n");
        printf("3. Editar funcionario\n");
        printf("4. Excluir funcionario\n");
        printf("5. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarFuncionario(); break;
            case 2: listarFuncionarios(); break;
            case 3: editarFuncionario(); break;
            case 4: excluirFuncionario(); break;
            case 5: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
}

void menuVendas() {
    printf("\n=== MENU VENDAS ===\n");
    printf("(Funcionalidade sera implementada na proxima entrega)\n");
    pausar();
}

// PROGRAMA PRINCIPAL
int main() {
    printf("=== SISTEMA PADARIA ===\n");

    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Produtos\n");
        printf("2. Funcionarios\n");
        printf("3. Vendas\n");
        printf("4. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: menuProdutos(); break;
            case 2: menuFuncionarios(); break;
            case 3: menuVendas(); break;
            case 4: printf("Encerrando sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    free(listaProdutos);
    free(listaFuncionarios);
    free(listaVendas);

    return 0;
}