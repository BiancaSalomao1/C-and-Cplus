#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define FILENAME "texto.txt"
#define BUFFER_SIZE 2048

void criptografar(char* texto) {
    for (int i = 0; i < strlen(texto); i++) {
        if (texto[i] >= 'a' && texto[i] <= 'z') {
            texto[i] = ((texto[i] - 'a' + 3) % 26) + 'a';
        } else if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = ((texto[i] - 'A' + 3) % 26) + 'A';
        }
    }
}

void descriptografar(char* texto) {
    for (int i = 0; i < strlen(texto); i++) {
        if (texto[i] >= 'a' && texto[i] <= 'z') {
            texto[i] = ((texto[i] - 'a' - 3 + 26) % 26) + 'a';
        } else if (texto[i] >= 'A' && texto[i] <= 'Z') {
            texto[i] = ((texto[i] - 'A' - 3 + 26) % 26) + 'A';
        }
    }
}

void readFile(char* buffer) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    size_t n = fread(buffer, 1, BUFFER_SIZE - 1, file);
    buffer[n] = '\0';

    fclose(file);
}

void writeFile(const char* buffer) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fwrite(buffer, 1, strlen(buffer), file);

    fclose(file);
}

void criararquivosenaoexistir() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        file = fopen(FILENAME, "w");
        if (file == NULL) {
            perror("Erro ao criar o arquivo");
            exit(EXIT_FAILURE);
        }
        fprintf(file, ""); // Escreve um conteúdo vazio
        fclose(file);
    } else {
        fclose(file);
    }
}

void showFile() {
    char buffer[BUFFER_SIZE];
    readFile(buffer);
    printf("%s\n", buffer);
}

void inputText() {
    char buffer[BUFFER_SIZE];
    printf("Digite o texto a ser salvo no arquivo: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove a nova linha do final
    writeFile(buffer);
}

int main() {
    int op;
    char buffer[BUFFER_SIZE];
    setlocale(LC_ALL, "portuguese");

    criararquivosenaoexistir();

    while (1) {
        printf("Menu\n");
        printf("1 – Digitar texto\n");
        printf("2 – Criptografar texto\n");
        printf("3 – Descriptografar texto\n");
        printf("4 – Mostrar texto\n");
        printf("9 – Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                inputText();
                system("pause");
                system("cls");
                break;
            case 2:
                readFile(buffer);
                criptografar(buffer);
                writeFile(buffer);
                printf("Texto criptografado com sucesso!\n");
                system("pause");
                system("cls");
                break;
            case 3:
                readFile(buffer);
                descriptografar(buffer);
                writeFile(buffer);
                printf("Texto descriptografado com sucesso!\n");
                system("pause");
                system("cls");
                break;
            case 4:
                showFile();
                system("pause");
                system("cls");
                break;
            case 9:
                printf("Saindo...\n");
                system("pause");
                system("cls");
                return 0;
            default:
                printf("Opção inválida!\n");
                system("pause");
                system("cls");
        }
    }

    return 0;
}
