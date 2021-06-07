#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

typedef struct {
    char cpf[20];
    char nome[30];
    char sobrenome[30];
    char sexo;
    char dataNascimento[11];
}PessoaStruct;

Pessoa criarPessoa(char cpf[], char nome[], char sobrenome[], char sexo, char dataNascimento[]){
    PessoaStruct* pessoa = (PessoaStruct*)malloc(sizeof(PessoaStruct));
    strcpy(pessoa->cpf,cpf);
    strcpy(pessoa->nome,nome);
    strcpy(pessoa->sobrenome,sobrenome);
    pessoa->sexo = sexo;
    strcpy(pessoa->dataNascimento,dataNascimento);
    return pessoa;
}

char* getCpf(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->cpf;
}

char* getNome(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->nome;
}

char* getSobrenome(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->sobrenome;
}

char getSexo(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->sexo;
}

char* getDataNascimento(Pessoa pessoa){
    PessoaStruct* p = (PessoaStruct*)pessoa;
    return p->dataNascimento;

}