#include "shellsort.h"

void shellSort(int *vetor, int tamanho) {
    int gap, i, j, temp;

    for (gap = tamanho / 2; gap > 0; gap /= 2) {
        for (i = gap; i < tamanho; i++) {
            temp = vetor[i];
            j = i;
            while (j >= gap && vetor[j - gap] > temp) {
                vetor[j] = vetor[j - gap];
                j -= gap;
            }
            vetor[j] = temp;
        }
    }
}
