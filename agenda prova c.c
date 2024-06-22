#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 5
#define SIZE 30
#define FILENAME "agenda.txt"

typedef struct {
    char nome[SIZE];
    char telefone[15];
    char endereco[100];
} Tagenda;

void ordemAlfabetica(Tagenda arr[], int n) {
    Tagenda temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].nome, arr[j+1].nome) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void cadastrarNomes(Tagenda pessoas[], int *fim, void (*ordenar)(Tagenda[], int)) {
    char opcAdd = 's';
    while (*fim < MAX && opcAdd == 's') {
        printf("\nDigite o nome da pessoa %d: ", *fim + 1);
        fgets(pessoas[*fim].nome, SIZE, stdin);
        pessoas[*fim].nome[strcspn(pessoas[*fim].nome, "\n")] = 0;

        printf("Digite o telefone da pessoa %d: ", *fim + 1);
        fgets(pessoas[*fim].telefone, 15, stdin);
        pessoas[*fim].telefone[strcspn(pessoas[*fim].telefone, "\n")] = 0;

        printf("Digite o endereco da pessoa %d: ", *fim + 1);
        fgets(pessoas[*fim].endereco, 100, stdin);
        pessoas[*fim].endereco[strcspn(pessoas[*fim].endereco, "\n")] = 0;
        (*fim)++;
        ordenar(pessoas, *fim);

        if (*fim < MAX) {
            printf("Deseja inserir mais nomes? [s=sim, n=nao]: ");
            scanf(" %c", &opcAdd);
            getchar();
        }
    }

    if (*fim >= MAX) {
        printf("\nImpossível inserir... agenda cheia.\n\n");
    }
}

void apagarNomes(Tagenda pessoas[], int *fim) {
    int opcDel, i;
    char nomeBusca[SIZE];

    if (*fim > 0) {
        printf("* * * *   Remover Nome   * * * *\n\n");
        printf("Você gostaria de remover por nome ou posição?\nTecle 1 para remover por nome ou 2 para remover por posição: ");
        scanf("%d", &opcDel);
        getchar();

        if (opcDel == 1) {
            printf("Digite o nome a ser removido: ");
            fgets(nomeBusca, SIZE, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = 0;

            for (i = 0; i < *fim; i++) {
                if (strcmp(pessoas[i].nome, nomeBusca) == 0) {
                    break;
                }
            }

            if (i < *fim) {
                for (; i < *fim - 1; i++) {
                    pessoas[i] = pessoas[i + 1];
                }
                (*fim)--;
                printf("\nElemento removido com sucesso!\n");
            } else {
                printf("\nNome não encontrado.\n");
            }
        } else if (opcDel == 2) {
            printf("Qual a posição a ser removida? ");
            scanf("%d", &i);
            getchar();
            i--;

            if (i >= 0 && i < *fim) {
                for (; i < *fim - 1; i++) {
                    pessoas[i] = pessoas[i + 1];
                }
                (*fim)--;
                printf("\nElemento removido com sucesso!\n");
            } else {
                printf("\nPosição inválida.\n");
            }
        } else {
            printf("\nOpção inválida.\n");
        }
    } else {
        printf("\nImpossível remover... agenda vazia.\n\n");
    }
}

void imprimirAgenda(Tagenda pessoas[], int fim) {
    printf("* * * *   Agenda   * * * *\n\n");
    for (int i = 0; i < fim; i++) {
        printf("%d - Nome: %s \tTelefone: %s\n \tEndereco: %s\n", i + 1, pessoas[i].nome, pessoas[i].telefone, pessoas[i].endereco);
    }
    printf("\n\n");
}


int main() {
    setlocale(LC_ALL, "portuguese");

    Tagenda pessoas[MAX];
    int fim = 0;
    int op;

    do {
        printf("* * * *   M E N U   * * * *\n\n");
        printf("1 - Inserir Dados da Agenda\n");
        printf("2 - Remover Dados da Agenda\n");
        printf("3 - Imprimir Dados da Agenda\n");
        printf("4 - Procurar por nome na Agenda\n");
        printf("9 - Sair\n");
        printf("Digite a sua opcao: ");
        scanf("%d", &op);
        getchar();

        switch(op) {
            case 1:
                system("cls");
                cadastrarNomes(pessoas, &fim, ordemAlfabetica);
                system("pause");
                break;

            case 2:
                system("cls");
                apagarNomes(pessoas, &fim);
                system("pause");
                break;

            case 3:
                system("cls");
                imprimirAgenda(pessoas, fim);
                system("pause");
                break;

            case 4:
                system("cls");
                printf("Qual nome você gostaria de localizar? \n");
                char nomeBusca[SIZE];
                fgets(nomeBusca, SIZE, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;

                int i;
                for (i = 0; i < fim; i++) {
                    if (strcmp(pessoas[i].nome, nomeBusca) == 0) {
                        printf("Nome: %s \tTelefone: %s\n", pessoas[i].nome, pessoas[i].telefone);
                        break;
                    }
                }

                if (i == fim) {
                    printf("\nNome não localizado!\n");
                }

                system("pause");
                break;
        }
    } while (op != 9);


    return 0;
}
