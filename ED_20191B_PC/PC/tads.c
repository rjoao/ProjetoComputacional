#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "tads.h"


// Criaa lista linear sequencial estática de disciplinas
Lista_Disciplinas *criar_lista_disciplinas(){
    Lista_Disciplinas *lista_disciplinas = (Lista_Disciplinas *)malloc(sizeof(Lista_Disciplinas));
    
    // Inicia lista
    lista_disciplinas->fim = -1;
    
    return lista_disciplinas; 
}


// Imprime lista com os nomes das disciplinas cadastradas
void imprimir_nome_disciplinas(Lista_Disciplinas *lista_disciplinas){
    if(!lista_vazia(lista_disciplinas)){
        printf("\nLista de Disciplinas:\n");
        for(int i=0; i<=lista_disciplinas->fim; i++){
            printf("%s", lista_disciplinas->disciplinas[i].nome_disciplina);
            printf("\n");
        }
        printf("\n");
    } else {
        printf("\nNenhuma disciplina cadastrada.\n\n");
    }
}

// Verifica se a lista estática de disciplinas está vazia
int lista_vazia(Lista_Disciplinas *lista_disciplinas){
    return (lista_disciplinas->fim == -1);
}


// Verifica se um código de disciplina já está cadastrado
int codigo_cadastrado(Lista_Disciplinas *lista_disciplinas, int cod){
    return (buscar_posicao(lista_disciplinas, cod) != (-1));
}

// Busca a posição de uma disciplina pelo seu código na lista de disciplinas
int buscar_posicao(Lista_Disciplinas *lista_disciplinas, int cod){
	int i=0;
	while(lista_disciplinas->disciplinas[i].codigo_disciplina != cod && i<=lista_disciplinas->fim){
		i++;
	}
	if(i>lista_disciplinas->fim){
        // Código de disciplina não encontrado
		return -1;
	}
    // Código de disciplina encontrado
    // Retorna a posição da disciplina do código de disciplina na lista de disciplinas
    return i;
}


// Insere uma disciplina na lista lista_disciplinas
void inserir_disciplina(Lista_Disciplinas *lista_disciplinas, int cod, char depto[50], char nome[50], int cred_teor, int cred_prat, int cred_ext,  int cred_est){
    if(!lista_cheia(lista_disciplinas)){
        Disciplina *disciplina = criar_disciplina(cod, depto, nome, cred_teor, cred_prat, cred_ext, cred_est);
             
        lista_disciplinas->fim++;

        // Insere na posição correta
        for(int i=lista_disciplinas->fim; i>=0; i--){
            // Percorrendo a lista na ordem contrária
            if (i==0){
                // Todos os códigos de disciplina da lista são maiores do que o codigo que está sendo inserido
                // Inserir disciplina no início da lista 
                lista_disciplinas->disciplinas[i].codigo_disciplina = disciplina->codigo_disciplina;
                strcpy(lista_disciplinas->disciplinas[i].departamento, disciplina->departamento);
                strcpy(lista_disciplinas->disciplinas[i].nome_disciplina, disciplina->nome_disciplina);
                lista_disciplinas->disciplinas[i].creditos=disciplina->creditos;
                lista_disciplinas->disciplinas[i].fila_espera=disciplina->fila_espera;
                lista_disciplinas->disciplinas[i].matriculados=disciplina->matriculados;
            } else {
                if(lista_disciplinas->disciplinas[i-1].codigo_disciplina>cod){
                    // Código de disciplina da posição [i-1] maior do que o código que está sendo inserido
                    // Copia disciplina da posicao [i-1] para [i]
                    lista_disciplinas->disciplinas[i] = lista_disciplinas->disciplinas[i-1]; 
                } else {
                    // Código de disciplina da posição [i-1] não é maior que o código que está sendo inserido
                    // Insere disciplina na posição atual [i] 
                    lista_disciplinas->disciplinas[i].codigo_disciplina = disciplina->codigo_disciplina;
                    strcpy(lista_disciplinas->disciplinas[i].departamento, disciplina->departamento);
                    strcpy(lista_disciplinas->disciplinas[i].nome_disciplina, disciplina->nome_disciplina);
                    lista_disciplinas->disciplinas[i].creditos=disciplina->creditos;
                    lista_disciplinas->disciplinas[i].fila_espera=disciplina->fila_espera;
                    lista_disciplinas->disciplinas[i].matriculados=disciplina->matriculados;
                    break;
                }
            }
        }

        printf("\nDisciplina inserida com sucesso!\n\n");
    } else {
        printf("\nNão há espaço disponível para cadastrar uma nova disciplina.\n\n");
    }
}

// Verifica se a lista estática está cheia
int lista_cheia(Lista_Disciplinas *lista_disciplinas){
    return (lista_disciplinas->fim >= (MAX-1));
}

Disciplina *criar_disciplina(int cod, char depto[50], char nome[50], int cred_teor, int cred_prat, int cred_ext, int cred_est){
    Disciplina *nova_disciplina = (Disciplina *)malloc(sizeof(Disciplina));
    
    Creditos *creditos = criar_codigo_creditos(cred_teor, cred_prat, cred_ext, cred_est);
    Fila_Espera *fila_espera = criar_fila_espera();
    Matriculados *matriculados = criar_pilha_matriculados();

    nova_disciplina->codigo_disciplina = cod;
    strcpy(nova_disciplina->departamento, depto);
    strcpy(nova_disciplina->nome_disciplina, nome);
    nova_disciplina->creditos = creditos;
    nova_disciplina->fila_espera = fila_espera;
    nova_disciplina->matriculados = matriculados;

    return nova_disciplina;
}

Creditos *criar_codigo_creditos(int cred_teor, int cred_prat, int cred_ext, int cred_est){
    Creditos *codigo_creditos = (Creditos *)malloc(sizeof(Creditos));
    
    codigo_creditos->teoria = cred_teor;
    codigo_creditos->pratica = cred_prat;
    codigo_creditos->extensao = cred_ext;
    codigo_creditos->estudo = cred_est;
    
    return codigo_creditos;
}

// Cria fila dinâmica de alunos em fila de espera por uma vaga em uma disciplina
Fila_Espera *criar_fila_espera(){
    Fila_Espera *fila_espera = (Fila_Espera *)malloc(sizeof(Fila_Espera));
    
    // Inicia fila
    fila_espera->primeiro_fila=NULL;
    fila_espera->ultimo_fila=NULL;
    
    return fila_espera;
}

// Cria pilha dinâmica de alunos matriculados em uma disciplina
Matriculados *criar_pilha_matriculados(){
    Matriculados *pilha_matriculados = (Matriculados *)malloc(sizeof(Matriculados));
    
    // Inicia pilha
    pilha_matriculados->topo_matriculado = NULL;
    pilha_matriculados->numero_matriculados = 0;
    
    return pilha_matriculados; 
}


void remover_disciplina(Lista_Disciplinas *lista_disciplinas, int cod){
	if(!lista_vazia(lista_disciplinas)){
        int p;
        p = buscar_posicao(lista_disciplinas, cod);
        
        // Verifica se foi encontrada uma posição válida
        if(p!=(-1)){
            for(int i=p; i<lista_disciplinas->fim; i++){
                lista_disciplinas->disciplinas[i]=lista_disciplinas->disciplinas[i+1];
            }
            lista_disciplinas->fim--;

            printf("\nDisciplina removida com sucesso!\n\n");
        } else {
            // Posição inválida ( p == (-1)) indica que não existe disciplina com o código indicado 
            printf("\nNão foi possível remover a disciplina. Não foi encontrada disciplina com o código inserido.\n\n");
        }

    } else {
        printf("\nNão foi possível remover a disciplina. Nenhuma disciplina cadastrada.\n\n");
    }
}


void buscar_disciplina(Lista_Disciplinas *lista_disciplinas, int cod){
    if(!lista_vazia(lista_disciplinas)){
        int p;
        p = buscar_posicao(lista_disciplinas, cod);

        // Verifica se foi encontrada uma posição válida
        if(p!=(-1)){
            char nome_disciplina[50], departamento_disciplina[50];
            int creditos_teoria, creditos_pratica, creditos_extensao, creditos_estudo;

            // Recebe os campos do resultado da busca
            strcpy(nome_disciplina, lista_disciplinas->disciplinas[p].nome_disciplina);
            strcpy(departamento_disciplina, lista_disciplinas->disciplinas[p].departamento);
            creditos_teoria = lista_disciplinas->disciplinas[p].creditos->teoria;
            creditos_pratica = lista_disciplinas->disciplinas[p].creditos->pratica;
            creditos_extensao = lista_disciplinas->disciplinas[p].creditos->extensao;
            creditos_estudo = lista_disciplinas->disciplinas[p].creditos->estudo;

            // Imprime os campos do resultado
            printf("\nBusca realizada com sucesso!\n");
            printf("Disciplina: %s\n", nome_disciplina);
            printf("Departamento da Disciplina: %s\n", departamento_disciplina);
            printf("Créditos: %02d-%02d-%02d-%02d\n\n", creditos_teoria, creditos_pratica, creditos_extensao, creditos_estudo);
        } else {
            // Posição inválida ( p == (-1)) indica que não existe disciplina com o código indicado
            printf("\nNão foi encontrada disciplina com o código inserido.\n\n");
        }

    } else {
        printf("\nNão foi encontrada disciplina com o código inserido. Nenhuma disciplina cadastrada.\n\n");
    }
}


void imprimir_alunos_matriculados(Lista_Disciplinas *lista_disciplinas, int cod){
    if(!lista_vazia(lista_disciplinas)){
        int p;
        p = buscar_posicao(lista_disciplinas, cod);

        // Verifica se foi encontrada uma posição válida
        if(p!=(-1)){
            if(!pilha_vazia(lista_disciplinas->disciplinas[p].matriculados)){
                Aluno *aux = lista_disciplinas->disciplinas[p].matriculados->topo_matriculado;

                printf("\nAlunos:\n");    
                for(int i=0; i<lista_disciplinas->disciplinas[p].matriculados->numero_matriculados; i++){
                    printf("%s \n", aux->nome_aluno);
                    aux = aux->prox;
                }
                printf("\n");
            } else {
                printf("\nNenhum aluno matriculado nessa disciplina.\n\n");
            }
        } else {
            // Posição inválida ( p == (-1)) indica que não existe disciplina com o código indicado
            printf("\nNão foi possível imprimir os alunos matriculados na disciplina. Não foi encontrada disciplina com o código inserido.\n\n");
        }
    } else {
        printf("\nNão foi possível imprimir os alunos matriculados na disciplina. Nenhuma disciplina cadastrada\n\n");
    }
}

// Verifica se a pilha dinâmica de matriculados está vazia
int pilha_vazia(Matriculados *matriculados){
    return (matriculados->topo_matriculado == NULL);
}


void matricular_aluno(Lista_Disciplinas *lista_disciplinas, int cod, char nome_a[50]){
    if(!lista_vazia(lista_disciplinas)){
        int p;
        p = buscar_posicao(lista_disciplinas, cod);

        // Verifica se foi encontrada uma posição válida
        if(p!=(-1)){
            Aluno *novo_aluno = (Aluno *)malloc(sizeof(Aluno));

            // copia nome_a em novo_aluno->nome_aluno
            strcpy(novo_aluno->nome_aluno, nome_a);
            
            novo_aluno->prox = lista_disciplinas->disciplinas[p].matriculados->topo_matriculado;
            lista_disciplinas->disciplinas[p].matriculados->topo_matriculado = novo_aluno;
            lista_disciplinas->disciplinas[p].matriculados->numero_matriculados++;

            printf("\nAluno matriculado com sucesso!\n\n");
        } else {
            // Posição inválida ( p == (-1)) indica que não existe disciplina com o código indicado
            printf("\nNão foi possível matricular o aluno. Não foi encontrada disciplina com o código inserido.\n\n");
        }
    } else {
        printf("\nNão foi possível matricular o aluno. Nenhuma disciplina cadastrada.\n\n");
    }
}


void desmatricular_aluno(Lista_Disciplinas *lista_disciplinas, int cod){
    if(!lista_vazia(lista_disciplinas)){
        int p;
        p = buscar_posicao(lista_disciplinas, cod);

        // Verifica se foi encontrada uma posição válida 
        if(p!=(-1)){
            if(!pilha_vazia(lista_disciplinas->disciplinas[p].matriculados)){
                lista_disciplinas->disciplinas[p].matriculados->topo_matriculado = lista_disciplinas->disciplinas[p].matriculados->topo_matriculado->prox;
                lista_disciplinas->disciplinas[p].matriculados->numero_matriculados--;
                printf("\nAluno desmatriculado com sucesso!\n\n");
            } else {
                printf("\nNão foi possível desmatricular o aluno. Nenhum aluno matriculado nessa disciplina.\n\n");
            }
        } else {
            // Posição inválida ( p == (-1)) indica que não existe disciplina com o código indicado
            printf("\nNão foi possível desmatricular o aluno. Não foi encontrada disciplina com o código inserido.\n\n");
        } 
    } else {
        printf("\nNão foi possível desmatricular o aluno. Nenhuma disciplina cadastrada.\n\n");
    }
}
