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
typedef struct data{
    int dia;
    int mes;
    int ano;
}

typedef struct {
    int codigoProd;
    char[100] nomeProd;
    float preco;
    int estoque;
    char nomeFornecedor;
    long int foneFornecedor;
}produto;

typedef struct {
    int matricula;
    char[100] nomeFunc;
    char[100] cargo;
    float salario;
    char[100] login;
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
