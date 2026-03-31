#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{ // Struct da lista encadeada das disciplinas
    char disciplina[20]; // aqui o nome da disciplina
    struct Lista * proximo;// e um ponteiro que apontaria para a proxima disciplina
}lista;

typedef struct Aluno{ // Struct de Aluno que guarda suas disciplinas
    int RGM;
    Lista * disciplinas_lista; // um ponteiro que irá armazenar uma lista encadeada do tipo struct Lista que contém as disciplinas desse aluno
}aluno;

int main(){

    return 0;
}