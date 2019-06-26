#ifndef __TADS_H__
#define __TADS_H__

#define MAX 100

struct CREDITOS {
    int teoria;
    int pratica;
    int extensao;
    int estudo;
}; typedef struct CREDITOS Creditos;

 
struct ALUNO {
    char nome_aluno[50];
    struct ALUNO *prox;
}; typedef struct ALUNO Aluno;

// Fila para Alunos na Fila de Espera
struct FILA_DE_ESPERA {
    Aluno *primeiro_fila;
    Aluno *ultimo_fila;
}; typedef struct FILA_DE_ESPERA Fila_Espera;

// Pilha para Alunos Matriculados
struct MATRICULADOS {
    Aluno *topo_matriculado;
    int numero_matriculados;
}; typedef struct MATRICULADOS Matriculados;



// Lista de Disciplinas
struct DISCIPLINA {
    int codigo_disciplina;
    char departamento[50];
    char nome_disciplina[50];
    Creditos *creditos;
    Fila_Espera *fila_espera;
    Matriculados *matriculados;
}; typedef struct DISCIPLINA Disciplina;

struct LISTA_DISCIPLINAS {
    Disciplina disciplinas[MAX];
    int fim;
}; typedef struct LISTA_DISCIPLINAS Lista_Disciplinas;



// Variáveis
// cod = código da disciplina
// depto = departamento da disciplina
// nome = nome da disciplina
// cred_teor = créditos teoria
// cred_prat = créditos prática
// cred_ext = créditos extensão
// cred_est = créditos estudo
// nome_a = nome aluno

// Criações e Inicializações
Lista_Disciplinas *criar_lista_disciplinas();
Fila_Espera *criar_fila_espera();
Matriculados *criar_pilha_matriculados();
Creditos *criar_codigo_creditos(int cred_teor, int cred_prat, int cred_ext, int cred_est);
Disciplina *criar_disciplina(int cod, char depto[50], char nome[50], int cred_teor, int cred_prat, int cred_ext, int cred_est);

// Impressão
void imprimir_nome_disciplinas(Lista_Disciplinas *lista_disciplinas);
void imprimir_alunos_matriculados(Lista_Disciplinas *lista_disciplinas, int cod);

void imprimir_fila_espera(Lista_Disciplinas *lista_disciplinas, int cod);

// Verificações
int codigo_cadastrado(Lista_Disciplinas *lista_disciplinas, int cod);
int lista_vazia(Lista_Disciplinas *lista_disciplinas);
int lista_cheia(Lista_Disciplinas *lista_disciplinas);
int pilha_vazia(Matriculados *matriculados);
int fila_vazia(Fila_Espera *fila_espera);

// int fila_espera_vazia();

// Buscas
int buscar_posicao(Lista_Disciplinas *lista_disciplinas, int cod);
void buscar_disciplina(Lista_Disciplinas *lista_disciplinas, int cod);

// Inserção
void inserir_disciplina(Lista_Disciplinas *lista_disciplinas, int cod, char depto[50], char nome[50], int cred_teor, int cred_prat, int cred_ext, int cred_est);
void matricular_aluno(Lista_Disciplinas *lista_disciplinas, int cod, char nome_a[50]);
void inserir_aluno_fila_espera(Lista_Disciplinas *lista_disciplinas, int cod, char nome_a[50]);

// Remoção
void remover_disciplina(Lista_Disciplinas *lista_disciplinas, int cod);
void desmatricular_aluno(Lista_Disciplinas *lista_disciplinas, int cod);
void matricular_aluno_fila_espera(Lista_Disciplinas *lista_disciplinas, int cod);

#endif
