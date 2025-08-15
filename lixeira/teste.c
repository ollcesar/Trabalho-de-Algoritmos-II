#include <stdio.h>
#include <stdlib.h>

/*
 Produto
Código (único), nome, preço, quantidade em estoque, nome do fornecedor, contato do fornecedor

Funcionário
Matrícula (única), nome, cargo, salário, login, senha

Venda
Código (único), código do produto, matrícula do funcionário, data, quantidade vendida

Relacionamento: Venda relaciona Produto e Funcionário
                pois uma venda depende de um produto disponível no estoque e de um funcionário que realizou a venda.
*/
typedef struct {
    int dia;
    int mes;
    int ano;
}data;

typedef struct {
    int codigoProd;
    char nomeProd[100];
    float preco;
    int estoque;
    char nomeFornecedor[100];
    long int foneFornecedor;
}produto;

typedef struct {
    int matricula;
    char nomeFunc[100];
    char cargo[100];
    float salario;
    char login[100];
    int senha;//possível alterar para um vetor de char também pra deixar a senha alfa-numerica
}funcionario;

typedef struct{
    int codigoVenda;
    int prodVendido;
    //codigo para a busca em um "vetor" de produtos ao invés de importar a classe toda
    bool produtoDisp;
    int vendedor;
    data diaDaVenda;
    int quantidadeVendida;
}venda;

//Funções

void incializarProdutos() {
    produto *vet;
    printf("Informe quantos produtos deseja cadastrar:");
    scanf("&d", &capacidade);
    vet = (produto*)malloc(capacidade*sizeof(produto));
    if (vet==NULL) {
        printf("ERRO: Memoria Insuficiente!");
        exit(1);
    }
    for (int i=0; i<capacidade; i++) {
        printf("Insira o codigo do produto:");
        scanf("%d", &vet[i].codigoProd);
        printf("Insira o nome do produto:");
        scanf("%[^\n]s", vet[i].nomeProd);
        printf("Insira o preco do produto:");
        scanf("%f", &vet[i].preco);
        printf("Insira o estoque do produto:");
        scanf("%d", &vet[i].estoque);
        printf("Insira o nome do fornecedor:");
        scanf("%[^\n]s", vet[i].nomeFornecedor);
        printf("Insira o telefone do fornecedor:");
        scanf("%[^\n]s", vet[i].foneFornecedor);
    }

};
void incializarFuncionarios() {

};
void incializarVendas() {

};

int main() {


    return 0;
}


