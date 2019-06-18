#ifndef __TADS_H__
#define __TADS_H__

#define TAM 100

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



// Imprimir lista com os nomes das disciplinas cadastradas
void imprimir_nome_disciplinas(Lista_Disciplinas *lista_disciplinas);


// Variáveis
// cod = código da disciplina
// depto = departamento da disciplina
// nome = nome da disciplina
// cred_teor = créditos teoria
// cred_prat = créditos prática
// cred_ext = créditos extensão
// cred_est = créditos estudo
// nome_a = nome aluno

void imprimir_alunos_matriculados(LISTA_DISCIPLINAS *lista_disciplinas, int cod);

Disciplina *buscar_disciplina(Lista_Disciplinas *lista_disciplinas, int cod);

void inserir_disciplina(Lista_Disciplinas *lista_disciplinas, int cod, char depto[50], char nome[50], int cred_teor, int cred_prat, int cred_ext, int cred_est);
void matricular_aluno(Lista_Disciplinas *lista_disciplinas, int cod, char nome_a[50]);

int remover_disciplina(Lista_Disciplinas *lista_disciplinas, int cod);
int desmatricular_aluno(Lista_Disciplinas *lista_disciplinas, int cod);

#endif

// Dúvidas
// 1- Ordenar lista na inserção?;
// 2- Como ordenar alunos matriculados?;
// 3- Limitar int no scanf?