#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "tads.h"

int menu_opcoes();
void executar_opcao(Lista_Disciplinas *lista_disciplinas, int opcao_selecionada);

int main(){
    
    Lista_Disciplinas *lista_disciplinas;
    lista_disciplinas = criar_lista_disciplinas();

    int opcao_selecionada;
    do {
        opcao_selecionada=menu_opcoes();
        executar_opcao(lista_disciplinas, opcao_selecionada);
    } while(opcao_selecionada);

    return 0;
}

int menu_opcoes(){
    int opcao;

    printf("Escolha uma opção\n");

    // Encerrar o programa
    printf("0. Sair\n");

    // Parte 1: 1. Imprimir lista
    printf("1. Imprimir o nome das disciplinas cadastradas\n");

    // Parte 1: 2. Inserir disciplina
    printf("2. Cadastrar disciplina\n");

    // Parte 1: 3. Remover disciplina
    printf("3. Remover disciplina\n");

    // Parte 1: 4. Buscar disciplina
    printf("4. Buscar disciplina\n");

    // Parte 1: 5. Imprimir pilha
    printf("5. Imprimir alunos matriculados em uma disciplina\n");

    // Parte 1: 6. Matricular aluno
    printf("6. Matricular aluno em uma disciplina\n");

    // Parte 1: 7. Remover matrícula
    printf("7. Desmatricular último aluno matriculado em uma disciplina\n");

    // Parte 2: 1. Imprimir fila 
    printf("8. Imprimir fila de espera por matrícula em uma disciplina\n");

    // Parte 2: 2. Inserir aluno na lista de espera
    printf("9. Inserir aluno na fila de espera de uma disciplina\n");

    // Parte 2: 3. Matricular aluno da fila de espera
    printf("10. Matricular aluno de maior preferência da fila de espera de uma disciplina\n");

    printf("Opcão: ");
    scanf("%d", &opcao);
    
    return opcao;
}

void executar_opcao(Lista_Disciplinas *lista_disciplinas, int opcao_selecionada){
    int cod, cred_teor, cred_prat, cred_ext, cred_est;
    char depto[50], nome[50], nome_aluno[50];

    switch(opcao_selecionada){
        case 0:
            break;
        
        case 1:
            system("clear || cls");
            imprimir_nome_disciplinas(lista_disciplinas);
            break;
        
        case 2:        
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);
            if(cod>9999){
                printf("\nCódigo de disciplina inválido!\n\n");
                break;
            }
            if(codigo_cadastrado(lista_disciplinas, cod)){
                printf("\nEste código de disciplina não está disponível.\n\n");
                break;
            }

            printf("Insira o departamento da disciplina (máx. 50 car.): ");
            // Limpa o buffer do teclado e recebe string com espaços e caracteres especiais
            scanf(" %[^\n]s", depto);

            
            printf("Insira o nome da disciplina (máx. 50 car.): ");
            // Limpa o buffer do teclado e recebe string com espaços e caracteres especiais
            scanf(" %[^\n]s", nome);


            printf("Insira o número de créditos de teoria da disciplina: ");
            scanf("%d", &cred_teor);
            if(cred_teor>99){
                printf("\nNúmero de créditos de teoria inválido!\n\n");
                break;
            }

            printf("Insira o número de créditos de prática da disciplina: ");
            scanf("%d", &cred_prat);
            if(cred_prat>99){
                printf("\nNúmero de créditos de prática inválido!\n\n");
                break;
            }

            printf("Insira o número de créditos de extensão da disciplina: ");
            scanf("%d", &cred_ext);
            if(cred_ext>99){
                printf("\nNúmero de créditos de extensão inválido!\n\n");
                break;
            }

            printf("Insira o número de créditos de estudo da disciplina: ");
            scanf("%d", &cred_est);
            if(cred_est>99){
                printf("\nNúmero de créditos de estudo inválido!\n\n");
                break;
            }

            system("clear || cls");
            inserir_disciplina(lista_disciplinas, cod, depto, nome, cred_teor, cred_prat, cred_ext, cred_est);
            break;
        
        case 3:
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);

            system("clear || cls");
            remover_disciplina(lista_disciplinas, cod);
            break;
        
        case 4:
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);

            system("clear || cls");
            buscar_disciplina(lista_disciplinas, cod);      
            break;
        
        case 5:
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);
            
            system("clear || cls");
            imprimir_alunos_matriculados(lista_disciplinas, cod);
            break;
        
        case 6:
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);

            printf("Insira o nome do aluno (máx. 50 car.): ");
            // Limpa o buffer do teclado e recebe string com espaços e caracteres especiais
            scanf(" %[^\n]s", nome_aluno);

            system("clear || cls");
            matricular_aluno(lista_disciplinas, cod, nome_aluno);
            break;
        
        case 7:
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);

            system("clear || cls");
            desmatricular_aluno(lista_disciplinas, cod);
            break;
        
        case 8:
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);

            system("clear || cls");
            imprimir_fila_espera(lista_disciplinas, cod);
            break;

        case 9:
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);

            printf("Insira o nome do aluno (máx. 50 car.): ");
            scanf(" %[^\n]s", nome_aluno);

            system("clear || cls");
            inserir_aluno_fila_espera(lista_disciplinas, cod, nome_aluno);
            break;

        case 10:
            printf("Insira o código da disciplina: ");
            scanf("%d", &cod);

            system("clear || cls");
            matricular_aluno_fila_espera(lista_disciplinas, cod);
            break;

        default:
            printf("Comando inválido\n");
    }
}