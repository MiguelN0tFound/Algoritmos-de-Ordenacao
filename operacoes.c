#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>     
#endif
#include "operacoes.h"
#include "Insertion/insertionsort.h"
#include "Bubble/bubblesort.h"
#include "Shell/shellsort.h"
#include "Selection/selectionsort.h"

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
 
int lerAlgoritmo(void) {
    int escolha;
    printf("1- Insertion Sort\n2- Bubble Sort\n3- Shell Sort\n4- Selection Sort\n5- Sair\n");
    
    escolha = lerInteiro("Escolha o algoritmo: ");
    do {
        if (escolha < 1 || escolha > 5) {
            printf("Opcao invalida. Digite um numero entre 1 e 5.\n");
            escolha = lerInteiro("Escolha o algoritmo: ");
        }
    } while (escolha < 1 || escolha > 5);
    switch (escolha) {
        case 1: return INSERTION;
        case 2: return BUBBLE;
        case 3: return SHELL;
        case 4: return SELECTION;
        case 5: return -1;
        default: return -1; // nunca deve acontecer, só pra o compilador ver todo caminho com return
    }
}


const char *nomeTipo(int tipo) {
    if (tipo == CRESCENTE) return "crescente";
    if (tipo == DECRESCENTE) return "decrescente";
    return "randomica";
}

static const char *nomeTipoPasta(int tipo) {
    if (tipo == CRESCENTE) return "Crescente";
    if (tipo == DECRESCENTE) return "Decrescente";
    return "Random";
}

static const char *nomeAlgoritmo(int algoritmo) {
    if (algoritmo == BUBBLE) return "Bubble Sort";
    if (algoritmo == SHELL) return "Shell Sort";
    if (algoritmo == SELECTION) return "Selection Sort";
    return "Insertion Sort";
}

static void ordenar(int algoritmo, int *vetor, int tamanho) {
    if (algoritmo == BUBBLE) bubbleSort(vetor, tamanho);
    else if (algoritmo == SHELL) shellSort(vetor, tamanho);
    else if (algoritmo == SELECTION) selectionSort(vetor, tamanho);
    else insertionSort_versao1(vetor, tamanho);
}


static void criarPasta(const char *caminho) {
    char buffer[600];
    char *p;

    snprintf(buffer, sizeof(buffer), "%s", caminho);

    for (p = buffer + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
#ifdef _WIN32
            _mkdir(buffer);
#else
            mkdir(buffer, 0777);
#endif
            *p = '/';
        }
    }
#ifdef _WIN32
    _mkdir(buffer);
#else
    mkdir(buffer, 0777);
#endif
}

static int *gerarSequencia(int tipo, int tamanho) {
    int *vetor = malloc(tamanho * sizeof(int));
    int i;

    if (tipo == CRESCENTE) {
        for (i = 0; i < tamanho; i++) vetor[i] = i;
    } else if (tipo == DECRESCENTE) {
        for (i = 0; i < tamanho; i++) vetor[i] = tamanho - i - 1;
    } else {
        for (i = 0; i < tamanho; i++) vetor[i] = rand() % tamanho;
    }

    return vetor;
}

static void salvarEntrada(int algoritmo, int tipo, int tamanho, int *vetor) {
    char pasta[300], caminho[400];
    int i;

    snprintf(pasta, sizeof(pasta), "%s/Arquivos de Entrada/%s", nomeAlgoritmo(algoritmo), nomeTipoPasta(tipo));
    criarPasta(pasta);
    snprintf(caminho, sizeof(caminho), "%s/Entrada%s%d.txt", pasta, nomeTipoPasta(tipo), tamanho);

    FILE *f = fopen(caminho, "w");
    if (f == NULL) return;
    fprintf(f, "%d\n", tamanho);
    for (i = 0; i < tamanho; i++) fprintf(f, "%d\n", vetor[i]);
    fclose(f);
}

static void salvarSaida(int algoritmo, int tipo, int tamanho, int *vetor) {
    char pasta[300], caminho[400];
    int i;

    snprintf(pasta, sizeof(pasta), "%s/Arquivos de Saida/%s", nomeAlgoritmo(algoritmo), nomeTipoPasta(tipo));
    criarPasta(pasta);
    snprintf(caminho, sizeof(caminho), "%s/Saida%s%d.txt", pasta, nomeTipoPasta(tipo), tamanho);

    FILE *f = fopen(caminho, "w");
    if (f == NULL) return;
    for (i = 0; i < tamanho; i++) fprintf(f, "%d\n", vetor[i]);
    fclose(f);
}

static void salvarTempo(int algoritmo, int tipo, int tamanho, double tempoGasto) {
    char pasta[300], caminho[400];

    snprintf(pasta, sizeof(pasta), "%s/Arquivos de Tempo/%s", nomeAlgoritmo(algoritmo), nomeTipoPasta(tipo));
    criarPasta(pasta);
    snprintf(caminho, sizeof(caminho), "%s/Tempo%s%d.txt", pasta, nomeTipoPasta(tipo), tamanho);

    FILE *f = fopen(caminho, "w");
    if (f == NULL) return;
    fprintf(f, "%d\n", tamanho);
    fprintf(f, "%.6f\n", tempoGasto);
    fclose(f);
}

void operacoes(int algoritmo, int tipo, int tamanho) {
    clock_t startt, endt;
    double tempoGasto;

    int *vetor = gerarSequencia(tipo, tamanho);
    salvarEntrada(algoritmo, tipo, tamanho, vetor);

    startt = clock();
    ordenar(algoritmo, vetor, tamanho);
    endt = clock();
    tempoGasto = ((double)(endt - startt) / CLOCKS_PER_SEC);

    salvarTempo(algoritmo, tipo, tamanho, tempoGasto);
    salvarSaida(algoritmo, tipo, tamanho, vetor);

    free(vetor);
}