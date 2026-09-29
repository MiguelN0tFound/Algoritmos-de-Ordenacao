#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operacoes.h"

int main(void) {
    int tamanhos[] = {10, 100, 1000, 10000, 100000, 1000000};
    int tipoAtual = RANDOMICA;
    int opcao;

    srand((unsigned int) time(NULL));

    do {
        printf("\n===== Algoritmos de Ordenacao =====\n");
        printf("1- Executar um algoritmo em um vetor\n");
        printf("2- Selecionar o tipo de instancia (randomica, crescente ou decrescente)\n");
        printf("3- Executar TODAS as instancias exigidas no trabalho\n");
        printf("    (10, 100, 1.000, 10.000, 100.000, 1.000.000 x crescente/decrescente/randomica)\n");
        printf("4- Sair da aplicacao\n");

        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: {
                int tamanho = lerInteiro("Digite o tamanho do vetor: ");
                if (tamanho <= 0) { printf("Tamanho invalido.\n"); break; }
                int algoritmo = lerAlgoritmo();
                operacoes(algoritmo, tipoAtual, tamanho);
                break;
            }
            case 2: {
                printf("\n1- Randomica\n2- Crescente\n3- Decrescente\n");
                int escolha = lerInteiro("Escolha: ");
                if (escolha == 1) tipoAtual = RANDOMICA;
                else if (escolha == 2) tipoAtual = CRESCENTE;
                else if (escolha == 3) tipoAtual = DECRESCENTE;
                else { printf("Opcao invalida.\n"); break; }

                printf("\n1-10  \n2-100  \n3-1000  \n4-10000  \n5-100000  \n6-1000000\n");
                escolha = lerInteiro("Escolha: ");
                if (escolha < 1 || escolha > 6) { printf("Opcao invalida.\n"); break; }
                int tamanho = tamanhos[escolha - 1];

                int algoritmo = lerAlgoritmo();
                operacoes(algoritmo, tipoAtual, tamanho);
                break;
            }
            case 3: {
                int algoritmo = lerAlgoritmo();
                int tipos[] = {CRESCENTE, DECRESCENTE, RANDOMICA};
                int t, i;
                for (t = 0; t < 3; t++) {
                    for (i = 0; i < 6; i++) {
                        printf("\n[%s | tamanho %d] processando...\n", nomeTipo(tipos[t]), tamanhos[i]);
                        operacoes(algoritmo, tipos[t], tamanhos[i]);
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
