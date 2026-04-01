#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 60

// ~~~~~~~~~~STRUCTS~~~~~~~~~~~~~~~~

// Estrutura disciplina, que armazena a variável nome e nota, além do *prox que é um ponteiro que aponta para o próximo nó (disciplina).
typedef struct disciplina {
    char nome[50];
    float nota;
    struct disciplina *prox;
} Disciplina;

typedef struct Aluno{ // Struct de Aluno que seu RGM e suas disciplinas
    char RGM[15];
    Disciplina *disciplinas; // um ponteiro que irá armazenar uma lista encadeada do tipo struct Lista que contém as disciplinas desse aluno
}aluno;

typedef struct Lista_aluno{ // Struct que guarda a lista sequencial para armazenar os alunos e o ULTIMO aluno que foi adicionado a lista
    aluno alunos[MAX];
    int ultimo_aluno;// ultimo aluno adicionado 
}lista_aluno;

// ~~~~~~~~~~FUNÇÕES~~~~~~~~~~~~~~~~

// A função criaDisciplina cria um nó (estrutura Disciplina) e retorna um ponteiro para ele (nó).
Disciplina *criaDisciplina(char nome[], float nota) {
	
	// Estrutura Disciplina é apontada por d.
	// O tamanho da Estrutura é definido pelo sizeof, e a ação de alocar dinamicamente é do malloc.
    Disciplina *d = (Disciplina *) malloc(sizeof(Disciplina));

	// É verificado se o ponteiro d é diferente de NULL, se for a alocação foi realizada corretamente e ele copia o nome recebido como parâmetro para a nova estrutura, 
	// além de definir a nota dessa estrutura como a nota inserida na função inserirDisciplina.
	// O prox é definido como NULL, por causa que não está ligado a nenhuma estrutura (nó) da lista, por ter sido criada recentemente.
    if (d != NULL) {
        strcpy(d->nome, nome);
        d->nota = nota;
        d->prox = NULL;
    }

	// Retorna um ponteiro para o nó criado.
    return d;
}


// A função inserirDisciplina permite acessar e modificar a lista, pois recebe o endereço da lista (**l). 
// Se fosse só *l, seria acessado somente a cópia do ponteiro da lista, permitindo somente acessar a lista, mas não alterar o seu início.
int inserirDisciplina(Disciplina **l, char nome[], float nota) {
	
	// O ponteiro novo recebe o nó criado pela função criarDisciplina,
	// e o aux serve para percorrer a lista da forma correta.
    Disciplina *novo = criaDisciplina(nome, nota);
    Disciplina *aux;


	// Verifica se a Disciplina foi criada corretamente.
    if (novo == NULL)
        return 0;

    // Verifica se *l (ínicio da lista) é NULL, se for ele define *l como o nó (Disciplina) criado.
    if (*l == NULL) {
        *l = novo;
        return 1;
    }

	// Define aux como *l (início da lista), já que a lista encadeada só pode ser percorrida pelo começo.
    aux = *l;
    
    // Enquanto a lista não chegar ao final, a lista é percorrida (por exemplo, de A (aux) para B (aux->prox), de B (aux) para C (aux->prox), etc.
    while (aux->prox != NULL)
        aux = aux->prox;

    // Após percorrer até o final da lista, define o aux->prox como o novo nó.
    aux->prox = novo;
    return 1;
}


// A função mostrarDisciplinas exibe as informações presentes na lista.
void mostrarDisciplinas(Disciplina *l) {
	// Percorre a lista enquanto não chegar ao final.
    while (l != NULL) {
        printf("   %s - %.2f\n", l->nome, l->nota);
        l = l->prox;
    }
}

lista_aluno criar_listasequencial(){ // inicializa a lista que guarda os alunos
    lista_aluno listasequencial; // inicializa a lista
    listasequencial.ultimo_aluno = -1; // define o ultimo aluno como -1(significa que a lista está vazia)
    
    return listasequencial; // retorna lista criada
}

int main(){
    lista_aluno lista_alunos = criar_listasequencial(); // variável guarda o retorno da função

    return 0;
}