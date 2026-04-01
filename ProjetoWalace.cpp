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

/* A função cadastrarAluno insere um aluno na lista sequencial de forma ordenada pelo RGM.
 A inserção ordenada funciona deslocando os alunos com RGM maior uma posição para a direita,
 abrindo espaço na posição correta para o novo aluno.*/
void cadastrarAluno(lista_aluno *lista) {
 
    // Verifica se a lista já está cheia (ultimo_aluno) começa em -1, então MAX-1 é o último índice
    if (lista->ultimo_aluno == MAX - 1) {
        printf("Lista cheia! Nao e possivel cadastrar mais alunos.\n");
        return;
    }
 
    char rgm[15];
    char resp[5];
 
    printf("\nDigite o RGM do aluno: ");
    scanf("%s", rgm);
    getchar();
 
    // Verifica se o RGM já existe na lista percorrendo todos os alunos cadastrados
    for (int i = 0; i <= lista->ultimo_aluno; i++) {
        if (strcmp(lista->alunos[i].RGM, rgm) == 0) {
            printf("RGM ja cadastrado!\n");
            return;
        }
    }

// Encontra a posição correta para inserir mantendo a ordem pelo RGM
// Enquanto o RGM do aluno anterior for maior que o novo, empurra ele pra direita
    int pos = lista->ultimo_aluno + 1;
    while (pos > 0 && strcmp(lista->alunos[pos - 1].RGM, rgm) > 0) {
        lista->alunos[pos] = lista->alunos[pos - 1]; // desloca o aluno para a direita
        pos--;
    }

// Insere o novo aluno na posição certa
    strcpy(lista->alunos[pos].RGM, rgm);
    lista->alunos[pos].disciplinas = NULL; // inicia a lista de disciplinas vazia
    lista->ultimo_aluno++; // atualiza o índice do último aluno
 
    printf("Aluno cadastrado com sucesso!\n");
 
    // Agora cadastra as disciplinas do aluno usando a função inserirDisciplina já criada
    printf("\n-- Cadastro de disciplinas --\n");
    do {
        char nome[50];
        float nota;
 
        printf("Nome da disciplina: ");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = '\0'; // remove o '\n' que o fgets deixa
 
        printf("Nota: ");
        scanf("%f", &nota);
        getchar();
 
        inserirDisciplina(&lista->alunos[pos].disciplinas, nome, nota);
 
        printf("Mais disciplina? (s/n): ");
        fgets(resp, 5, stdin);
 
    } while (resp[0] == 's' || resp[0] == 'S');
}

/* A função mostrarAlunos percorre a lista de alunos do primeiro até o último cadastrado
   e para cada aluno chama mostrarDisciplinas para exibir sua lista encadeada.*/
void mostrarAlunos(lista_aluno *lista) {
 
    // Verifica se não há nenhum aluno cadastrado (último == -1 significa lista vazia)
    if (lista->ultimo_aluno == -1) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
 
    printf("\n----- LISTA DE ALUNOS -----\n");
    for (int i = 0; i <= lista->ultimo_aluno; i++) {
        printf("\nRGM: %s\n", lista->alunos[i].RGM);
        printf("Disciplinas:\n");
        mostrarDisciplinas(lista->alunos[i].disciplinas); // usa a função já criada
    }
    printf("----------------------------\n");
}

int main(){
    lista_aluno lista_alunos = criar_listasequencial(); // variável guarda o retorno da função

    return 0;
}