#ifndef __pessoa__
#define __pessoa__

typedef void* Pessoa; 

Pessoa criarPessoa(char cpf[], char nome[], char sobrenome[], char sexo, char dataNascimento[]);
// "constructor" da estrutura pessoa

char* getCpf(Pessoa pessoa);
// retorna o valor do cpf

char* getNome(Pessoa pessoa);
// retorna o nome da pessoa

char* getSobrenome(Pessoa pessoa);
// retorna o sobrenome da pessoa

char getSexo(Pessoa pessoa);
// retorna o sexo da pessoa

char* getDataNascimento(Pessoa pessoa);
// retorna a data de nascimento da pessoa

#endif