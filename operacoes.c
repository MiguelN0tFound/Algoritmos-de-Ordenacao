#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "operacoes.h"
#include "insertionsort.h"

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

/* Cria a pasta (e todas as pastas pai necessárias) se ela ainda não
   existir. Funciona tanto em Windows quanto em Linux/Mac, e pode ser
   chamada quantas vezes for preciso: se a pasta já existe, não faz
   nada; se foi apagada, recria na hora seguinte que for chamada. */
static void criarPasta(const char *caminho) {
    char comando[700];

#ifdef _WIN32
    char caminhoWin[600];
    int i;
    for (i = 0; caminho[i] != '\0' && i < 599; i++)
        caminhoWin[i] = (caminho[i] == '/') ? '\\' : caminho[i];
    caminhoWin[i] = '\0';
    snprintf(comando, sizeof(comando), "mkdir \"%s\" 2>nul", caminhoWin);
#else
    snprintf(comando, sizeof(comando), "mkdir -p \"%s\"", caminho);
#endif

    int r = system(comando);
    (void)r;
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

static void salvarEntrada(int tipo, int tamanho, int *vetor) {
    char pasta[300], caminho[400];
    int i;

    snprintf(pasta, sizeof(pasta), "Insertion Sort/Arquivos de Entrada/%s", nomeTipoPasta(tipo));
    criarPasta(pasta);
    snprintf(caminho, sizeof(caminho), "%s/Entrada%s%d.txt", pasta, nomeTipoPasta(tipo), tamanho);

    FILE *f = fopen(caminho, "w");
    if (f == NULL) return;
    fprintf(f, "%d\n", tamanho);
    for (i = 0; i < tamanho; i++) fprintf(f, "%d\n", vetor[i]);
    fclose(f);
}

static void salvarSaida(int tipo, int tamanho, int *vetor) {
    char pasta[300], caminho[400];
    int i;

    snprintf(pasta, sizeof(pasta), "Insertion Sort/Arquivos de Saida/%s", nomeTipoPasta(tipo));
    criarPasta(pasta);
    snprintf(caminho, sizeof(caminho), "%s/Saida%s%d.txt", pasta, nomeTipoPasta(tipo), tamanho);

    FILE *f = fopen(caminho, "w");
    if (f == NULL) return;
    for (i = 0; i < tamanho; i++) fprintf(f, "%d\n", vetor[i]);
    fclose(f);
}

static void salvarTempo(int tipo, int tamanho, double tempoGasto) {
    char pasta[300], caminho[400];

    snprintf(pasta, sizeof(pasta), "Insertion Sort/Arquivos de Tempo/%s", nomeTipoPasta(tipo));
    criarPasta(pasta);
    snprintf(caminho, sizeof(caminho), "%s/Tempo%s%d.txt", pasta, nomeTipoPasta(tipo), tamanho);

    FILE *f = fopen(caminho, "w");
    if (f == NULL) return;
    fprintf(f, "%d\n", tamanho);
    fprintf(f, "%.6f\n", tempoGasto);
    fclose(f);
}

void operacoes(int tipo, int tamanho) {
    clock_t startt, endt;
    double tempoGasto;

    int *vetor = gerarSequencia(tipo, tamanho);
    salvarEntrada(tipo, tamanho, vetor);

    startt = clock();
    insertionSort_versao1(vetor, tamanho);
    endt = clock();
    tempoGasto = ((double)(endt - startt) / CLOCKS_PER_SEC);

    salvarTempo(tipo, tamanho, tempoGasto);
    salvarSaida(tipo, tamanho, vetor);

    free(vetor);
}
