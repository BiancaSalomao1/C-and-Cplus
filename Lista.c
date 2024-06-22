#include <stdio.h>
#include <stdlib.h>
#define MAX 5

int main()
{
    int lista[MAX];
    int posicao, op, elemento, fim;

    do
    {
        printf("* * * *   M E N U   * * * *\n\n");
        printf("\n1 - Push/ Entrada de Dados");
        printf("\n2 - Pop/ Apagar Dados");
        printf("\n3 - Imprimir Dados");
        printf("\n9 - Sair");
        printf("\n\nDigite a sua opcao: ");
        scanf("%d", &op);
        posicao = 0;
        fim = -1;

        switch (op)
        {
        case 1:
            system("cls");
            printf("\nDigite uma posicao para inserir na lista: ");
            scanf("%d", &posicao);
            if (posicao < MAX-1)
            {
                 if (posicao <= fim + 1)
                    {
                        printf("\nDigite um numero para inserir na lista: ");
                        scanf("%d", &elemento);

                        for (int i = fim; i >= posicao; i--)
                        {
                            lista[i + 1] = lista[i];
                        }
                        lista[posicao] = elemento;
                        fim++;
                        printf("\nElemento inserido com sucesso!!\n");
                    }
                    else
                        printf("\nPosicao nao valida\n");
                }
                else
                    printf("\nImpossivel inserir nesta posicao. Lista cheia.\n\n");

            system("pause");
            break;

        case 2:
            system("cls");
            printf("\nDigite a posicao a ser removida da lista: ");
            scanf("%d", &posicao);
            if (posicao >= 0 && posicao <= fim)
            {
               for (int i = posicao; i < fim; i++)
                {
                    lista[i] = lista[i + 1];
                }
                fim--;
                printf("\nElemento removido com sucesso!\n");
            }
            else
                printf("\nImpossivel remover...\nLista vazia ou posicao invalida.\n\n");
            system("pause");
            break;

        case 3:
            system("cls");
            printf("* * * *   L I S T A   * * * *\n\n");
            for (int i = 0; i <= fim; i++)
                printf("\t%d", lista[i]);
            printf("\n\n");
            system("pause");
            break;
        }

    } while (op != 9);

    return 0;
}
