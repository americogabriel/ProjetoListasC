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
    Disciplina *aux ;


	// Verifica se a Disciplina foi criada corretamente.
    if (novo == NULL){
        return 0;
    }
    // Verifica se *l (ínicio da lista) é NULL, se for ele define *l como o nó (Disciplina) criado.
    if (*l == NULL) {
        *l = novo;
        return 1;
    }

	// Define aux como *l (início da lista), já que a lista encadeada só pode ser percorrida pelo começo.
    aux = *l;
    
    // Enquanto a lista não chegar ao final, a lista é percorrida (por exemplo, de A (aux) para B (aux->prox), de B (aux) para C (aux->prox), etc.
    while (aux->prox != NULL){
        aux = aux->prox;
    }
    // Após percorrer até o final da lista, define o aux->prox como o novo nó(adiciona a nova discplina ao final da lista).
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
    char entrada[50];

 // Pq usar fgets ao invés de (scanf e getchar)?  scanf para de ler no primeiro espaço, ou seja, se o user colocar "12345-67" ele só vai ler "12345", já o fgets lê a linha inteira até o '\n' e armazena na variável (entrada), por isso é necessário remover o '\n' na linha 115.
    printf("\nDigite o RGM do aluno: ");
    fgets(rgm, 15, stdin); 
    rgm[strcspn(rgm, "\n")] = '\0'; // remove o '\n' que o fgets deixa
 
    // Verifica se o RGM já existe na lista percorrendo todos os alunos cadastrados
    for (int i = 0; i <= lista->ultimo_aluno; i++) {
        if (strcmp(lista->alunos[i].RGM, rgm) == 0) {
            printf("RGM ja cadastrado!\n");
            return;
        }
    }

/* Encontra a posição correta para inserir, mantendo a ordem pelo RGM.
 Enquanto o RGM do aluno anterior for maior que o novo, empurra ele pra direita*/
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
 
    // Cadastra as disciplinas do aluno usando a função inserirDisciplina já criada
    printf("\n-- Cadastro de disciplinas --\n");
    do {
        char nome[50];
        float nota;
 
        printf("Nome da disciplina: ");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = '\0'; // remove o '\n' que o fgets deixa
 
        printf("Nota: ");
        fgets(entrada, 50, stdin);
        nota = atof(entrada);  // (atof) converte a string de variavel (entrada) para float. PROBLEMA se o fdp do user colocar "abc" vai dar 0.0
 
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

/* A função (buscarAluno) percorre a lista sequencial procurando pelo RGM informado.
 Se encontrar, exibe os dados do aluno. Se não, exibe mensagem de "não existe".*/
void buscarAluno(lista_aluno *lista) {
    char rgm[15];
 
    printf("\nDigite o RGM: ");
    fgets(rgm, 15, stdin);
    rgm[strcspn(rgm, "\n")] = '\0';
 
    // Percorre todos os alunos cadastrados comparando o RGM
    for (int i = 0; i <= lista->ultimo_aluno; i++) {
        if (strcmp(lista->alunos[i].RGM, rgm) == 0) {
            printf("\nAluno encontrado!\n");
            printf("RGM: %s\n", lista->alunos[i].RGM);
            printf("Disciplinas:\n");
            mostrarDisciplinas(lista->alunos[i].disciplinas);
            return;
        }
    }
 
    // Se chegou aqui, o aluno não foi encontrado
    printf("Aluno com RGM %s nao existe.\n", rgm);
}

void RemoveAluno(Lista_aluno * lista, int posicao){ // Recebe um ponteiro para a lista de alunos e a posicao do aluno a ser removido, que veio da função:BuscaRGM
    int i;

    if(posicao < 0 || posicao > lista->ultimo_aluno){// caso a posição seja uma posição inválida
        printf("Posição inválida!\n"); 
        return; // sai da função
    }
    for(i = posicao;i<lista->ultimo_aluno;i++){ // for que vai começar do item a ser removido até o penúltimo item da lista
        lista->alunos[i] = lista->alunos[i+1]; // define o aluno do índice atual como o do próximo índice(partindo do aluno a ser removido para não alterar os alunos que vieram antes dele)
    }

    lista->ultimo_aluno--; // ao final atualiza o índice do ultimo_aluno na struct Lista_aluno
    // OBS: caso o aluno a ser o removido seja o último, o for não rodará mas quando decrementar o índice do ultimo_aluno ele será removido da listagem de alunos
    mostrarAlunos(lista); // mostra lista atualizada
};

void BuscaRGM(Lista_aluno *lista){ // Busca a posicao do aluno que será removido
    char rgm_buscado[15];
    int i,pos = -1;

    printf("\nDigite o RGM: ");
    fgets(rgm_buscado, 15, stdin); // salva o RGM digitado pelo usuário
    rgm_buscado[strcspn(rgm_buscado, "\n")] = '\0';

    for(i = 0; i <= lista->ultimo_aluno; i++){ 
        if(strcmp(lista->alunos[i].RGM,rgm_buscado) == 0){ // roda todo os alunos até entrar no if, se econtrar o aluno que possui o RGM buscado
            pos = i; // salva o índice na variável pos
            break;// sai do for
        }
    }
    if (pos == -1){ // se pos continuou como -1, significa que não foi definido com a posicao do RGM buscado
        printf("RGM não encontrado!!");
        return;
    }
    else{
        RemoveAluno(lista,pos); //chama a função que remove o aluno e exibe a nova lista
    }
}

int main() {
    lista_aluno myLista = criar_listasequencial();
    int escolha;


    do {
        printf("\n1 - Inserir aluno\n2 - Mostrar\n3 - Buscar\n4 - Remover\n0 - Sair\n");
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:
                cadastrarAluno(&myLista);
                break;

            case 2:
                mostrarAlunos(&myLista);
                break;

            case 3:
                buscarAluno(&myLista);
                break;

            case 4:
                BuscaRGM(&myLista);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (escolha != 0);

    return 0;
}