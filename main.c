#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "insertionsort.h"
#include "operacoes.h"

int lerInteiro(const char *prompt) {
    int valor, ok;
    do {
        printf("%s", prompt);
        fflush(stdout);
        ok = scanf("%d", &valor);
        if (ok != 1) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            while (getchar() != '\n');
        }
    } while (ok != 1);
    return valor;
}

int main(void) {
    int tamanhos[] = {10, 100, 1000, 10000, 100000, 1000000};
    int tipoAtual = RANDOMICA;
    int opcao;

    srand((unsigned int) time(NULL));

    do {
        printf("\n===== Trabalho Pratico - Insertion Sort =====\n");
        printf("Tipo de instancia atual: %s\n", nomeTipo(tipoAtual));
        printf("1 - Executar o Insertion Sort em um vetor\n");
        printf("2 - Selecionar o tipo de instancia (randomica, crescente ou decrescente)\n");
        printf("3 - Executar TODAS as instancias exigidas no trabalho\n");
        printf("    (10, 100, 1.000, 10.000, 100.000, 1.000.000 x crescente/decrescente/randomica)\n");
        printf("4 - Sair da aplicacao\n");

        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: {
                int tamanho = lerInteiro("Digite o tamanho do vetor: ");
                if (tamanho <= 0) { printf("Tamanho invalido.\n"); break; }
                operacoes(tipoAtual, tamanho);
                break;
            }
            case 2: {
                printf("1 - Randomica\n2 - Crescente\n3 - Decrescente\n");
                int escolha = lerInteiro("Escolha: ");
                if (escolha == 1) tipoAtual = RANDOMICA;
                else if (escolha == 2) tipoAtual = CRESCENTE;
                else if (escolha == 3) tipoAtual = DECRESCENTE;
                else { printf("Opcao invalida.\n"); break; }

                printf("1-10  2-100  3-1000  4-10000  5-100000  6-1000000\n");
                escolha = lerInteiro("Escolha: ");
                if (escolha < 1 || escolha > 6) { printf("Opcao invalida.\n"); break; }
                operacoes(tipoAtual, tamanhos[escolha - 1]);
                break;
            }
            case 3: {
                int tipos[] = {CRESCENTE, DECRESCENTE, RANDOMICA};
                int t, i;
                for (t = 0; t < 3; t++) {
                    for (i = 0; i < 6; i++) {
                        printf("\n[%s | tamanho %d] processando...\n", nomeTipo(tipos[t]), tamanhos[i]);
                        operacoes(tipos[t], tamanhos[i]);
                    }
                }
                printf("\nTodas as 18 instancias (6 tamanhos x 3 tipos) foram processadas.\n");
                break;
            }
            case 4:
                printf("Encerrando a aplicacao.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}
