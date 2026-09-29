#include "selectionsort.h"

void selectionSort(int *vetor, int tamanho) {
    int i, j, menor, temp;

    for (i = 0; i < tamanho - 1; i++) {
        menor = i;
        for (j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[menor]) {
                menor = j;
            }
        }
        temp = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = temp;
    }
}