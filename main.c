#include <stdio.h>

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
