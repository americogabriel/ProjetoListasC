#include <stdio.h>
#include <stdlib.h>
#define MAX 60

// ~~~~~~~~~~STRUCTS~~~~~~~~~~~~~~~~
typedef struct Lista_disciplina{ // Struct da lista encadeada das disciplinas
    char disciplina[20];
    float nota; 
    struct Lista * proximo;// e um ponteiro que apontaria para a proxima disciplina
}lista_disciplina;

typedef struct Aluno{ // Struct de Aluno que seu RGM e suas disciplinas
    char RGM[15];
    lista_disciplina * disciplinas_lista; // um ponteiro que irá armazenar uma lista encadeada do tipo struct Lista que contém as disciplinas desse aluno
}aluno;

typedef struct Lista_aluno{ // Struct que guarda a lista sequencial para armazenar os alunos e o ULTIMO aluno que foi adicionado a lista
    aluno alunos[MAX];
    int ultimo_aluno;// ultimo aluno adicionado 
}lista_aluno;

// ~~~~~~~~~~FUNÇÕES~~~~~~~~~~~~~~~~

lista_aluno criar_listasequencial(){ // inicializa a lista que guarda os alunos
    lista_aluno listasequencial; // inicializa a lista
    listasequencial.ultimo_aluno = -1; // define o ultimo aluno como -1(significa que a lista está vazia)

    return listasequencial; // retorna lista criada
}

int main(){
    lista_aluno lista_alunos = criar_listasequencial(); // variável guarda o retorno da função

    return 0;
}