/* ============================================================
   TRABALHO PRATICO - PROJETO DE ALGORITMOS
   Implementacao e Analise do Insertion Sort

   - Gera instancias crescentes, decrescentes e randomicas
   - Executa o Insertion Sort tradicional (insertionSort_versao1)
   - Salva os arquivos na estrutura de pastas:
       Insertion Sort/Arquivos de Entrada/<Tipo>/Entrada<Tipo><n>.txt
       Insertion Sort/Arquivos de Tempo/<Tipo>/Tempo<Tipo><n>.txt
       Insertion Sort/Arquivos de Saida/<Tipo>/Saida<Tipo><n>.txt
     onde <Tipo> = Crescente | Decrescente | Random

   Compilar:   gcc -O2 -Wall -o insertion_sort insertion_sort.c
   Executar:   ./insertion_sort
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

typedef enum {
    CRESCENTE,
    DECRESCENTE,
    RANDOMICA
} TipoInstancia;

/* Nome usado tanto para exibicao quanto para nomear arquivos
   (sem acentos, para evitar problemas de codificacao em nomes
   de arquivo em diferentes sistemas). */
const char *nomeTipo(TipoInstancia tipo) {
    switch (tipo) {
        case CRESCENTE:   return "crescente";
        case DECRESCENTE: return "decrescente";
        case RANDOMICA:   return "randomica";
    }
    return "desconhecido";
}

/* Nome em CamelCase usado para montar a arvore de pastas/arquivos
   exigida no trabalho (Crescente / Decrescente / Random). */
const char *nomeTipoPasta(TipoInstancia tipo) {
    switch (tipo) {
        case CRESCENTE:   return "Crescente";
        case DECRESCENTE: return "Decrescente";
        case RANDOMICA:   return "Random";
    }
    return "Desconhecido";
}

void criarPastaSeNaoExistir(const char *pasta); /* definida mais abaixo */

/* ---------- Leitura robusta de inteiros do teclado ---------- */
int lerInteiro(const char *prompt) {
    int valor;
    int ok;
    do {
        printf("%s", prompt);
        fflush(stdout);
        ok = scanf("%d", &valor);
        if (ok != 1) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            while (getchar() != '\n'); /* descarta o que foi digitado errado */
        }
    } while (ok != 1);
    return valor;
}

/* ---------- Geracao de instancias ---------- */
int *gerarInstancia(int tamanho, TipoInstancia tipo) {
    int *vetor = (int *) malloc((size_t) tamanho * sizeof(int));
    if (vetor == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para instancia de tamanho %d\n", tamanho);
        exit(1);
    }

    switch (tipo) {
        case CRESCENTE:
            for (int i = 0; i < tamanho; i++) {
                vetor[i] = i;
            }
            break;
        case DECRESCENTE:
            for (int i = 0; i < tamanho; i++) {
                vetor[i] = tamanho - i - 1;
            }
            break;
        case RANDOMICA:
            for (int i = 0; i < tamanho; i++) {
                vetor[i] = rand() % tamanho;
            }
            break;
    }

    return vetor;
}


void insertionSort(int *vetor, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

/* ---------- Escrita de arquivos ---------- */

/* Arquivo de ENTRADA: 1a linha = tamanho, demais linhas = valores
   (um por linha), exatamente como pedido no enunciado. */
void salvarEntrada(const char *caminho, int *vetor, int tamanho) {
    FILE *f = fopen(caminho, "w");
    if (f == NULL) {
        fprintf(stderr, "Erro ao criar arquivo %s\n", caminho);
        exit(1);
    }
    fprintf(f, "%d\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        fprintf(f, "%d\n", vetor[i]);
    }
    fclose(f);
}

/* Arquivo de SAIDA: instancia ja ordenada, um valor por linha.
   O enunciado so exige o cabecalho de tamanho nos arquivos de
   entrada e de tempo, entao aqui vai so a sequencia ordenada.
   (Se o padrao usado em aula exigir o tamanho tambem aqui, e so
   copiar a linha "fprintf(f, "%d\n", tamanho);" do salvarEntrada.) */
void salvarSaida(const char *caminho, int *vetor, int tamanho) {
    FILE *f = fopen(caminho, "w");
    if (f == NULL) {
        fprintf(stderr, "Erro ao criar arquivo %s\n", caminho);
        exit(1);
    }
    for (int i = 0; i < tamanho; i++) {
        fprintf(f, "%d\n", vetor[i]);
    }
    fclose(f);
}

/* Arquivo de TEMPO: 1a linha = tamanho, 2a linha = tempo em segundos
   gasto SOMENTE pelo algoritmo de ordenacao (sem contar geracao
   da instancia nem escrita de arquivos). */
void salvarTempo(const char *caminho, int tamanho, double tempoSegundos) {
    FILE *f = fopen(caminho, "w");
    if (f == NULL) {
        fprintf(stderr, "Erro ao criar arquivo %s\n", caminho);
        exit(1);
    }
    fprintf(f, "%d\n", tamanho);
    fprintf(f, "%.6f\n", tempoSegundos);
    fclose(f);
}

/* ---------- Execucao de uma instancia completa ---------- */
/* Monta e cria a arvore de pastas exigida:
     <pastaRaiz>/Arquivos de Entrada/<Tipo>/Entrada<Tipo><tamanho>.txt
     <pastaRaiz>/Arquivos de Tempo/<Tipo>/Tempo<Tipo><tamanho>.txt
     <pastaRaiz>/Arquivos de Saida/<Tipo>/Saida<Tipo><tamanho>.txt
   onde <Tipo> e Crescente, Decrescente ou Random. */
void executarInstancia(int tamanho, TipoInstancia tipo, const char *pastaRaiz) {
    char pastaEntrada[400], pastaTempoDir[400], pastaSaidaDir[400];
    char caminhoEntrada[512], caminhoSaida[512], caminhoTempo[512];

    snprintf(pastaEntrada,  sizeof(pastaEntrada),  "%s/Arquivos de Entrada/%s", pastaRaiz, nomeTipoPasta(tipo));
    snprintf(pastaTempoDir, sizeof(pastaTempoDir), "%s/Arquivos de Tempo/%s",   pastaRaiz, nomeTipoPasta(tipo));
    snprintf(pastaSaidaDir, sizeof(pastaSaidaDir), "%s/Arquivos de Saida/%s",   pastaRaiz, nomeTipoPasta(tipo));

    criarPastaSeNaoExistir(pastaEntrada);
    criarPastaSeNaoExistir(pastaTempoDir);
    criarPastaSeNaoExistir(pastaSaidaDir);

    snprintf(caminhoEntrada, sizeof(caminhoEntrada), "%s/Entrada%s%d.txt", pastaEntrada,  nomeTipoPasta(tipo), tamanho);
    snprintf(caminhoTempo,   sizeof(caminhoTempo),   "%s/Tempo%s%d.txt",   pastaTempoDir, nomeTipoPasta(tipo), tamanho);
    snprintf(caminhoSaida,   sizeof(caminhoSaida),   "%s/Saida%s%d.txt",   pastaSaidaDir, nomeTipoPasta(tipo), tamanho);

    printf("\n[%s | tamanho %d] Gerando instancia...\n", nomeTipo(tipo), tamanho);
    fflush(stdout);
    int *vetor = gerarInstancia(tamanho, tipo);
    salvarEntrada(caminhoEntrada, vetor, tamanho);

    printf("[%s | tamanho %d] Executando Insertion Sort...\n", nomeTipo(tipo), tamanho);
    fflush(stdout);

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    insertionSort(vetor, tamanho);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempoSegundos = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    salvarSaida(caminhoSaida, vetor, tamanho);
    salvarTempo(caminhoTempo, tamanho, tempoSegundos);

    printf("[%s | tamanho %d] Concluido em %.6f s\n", nomeTipo(tipo), tamanho, tempoSegundos);
    printf("   entrada: %s\n   saida:   %s\n   tempo:   %s\n", caminhoEntrada, caminhoSaida, caminhoTempo);

    free(vetor);
}

/* ---------- Criacao de pastas (usada em toda a arvore de arquivos) ---------- */
void criarPastaSeNaoExistir(const char *pasta) {
    char caminho[600];
    char *p;

    snprintf(caminho, sizeof(caminho), "%s", pasta);

    for (p = caminho + 1; *p; p++) {
        if (*p == '/' || *p == '\\') {
            *p = '\0';
            CreateDirectoryA(caminho, NULL);
            *p = '\\';
        }
    }

    CreateDirectoryA(caminho, NULL);
}

/* ---------- Execucao em lote de todas as instancias exigidas ---------- */
static const int TAMANHOS[] = {10, 100, 1000, 10000, 100000, 1000000};
static const int NUM_TAMANHOS = 6;

void executarTodasInstancias(const char *pastaRaiz) {
    criarPastaSeNaoExistir(pastaRaiz);
    TipoInstancia tipos[] = {CRESCENTE, DECRESCENTE, RANDOMICA};

    printf("\nATENCAO: para tamanho 1.000.000, os casos decrescente e\n");
    printf("randomico sao o pior caso / caso medio do Insertion Sort\n");
    printf("(O(n^2)) e podem levar varios minutos para terminar.\n");
    printf("O caso crescente e rapido em qualquer tamanho (O(n)).\n\n");
    fflush(stdout);

    for (int t = 0; t < 3; t++) {
        for (int i = 0; i < NUM_TAMANHOS; i++) {
            executarInstancia(TAMANHOS[i], tipos[t], pastaRaiz);
        }
    }
    printf("\nTodas as 18 instancias (6 tamanhos x 3 tipos) foram processadas.\n");
    printf("Estrutura: %s/Arquivos de Entrada|Tempo|Saida/<Crescente|Decrescente|Random>/...\n", pastaRaiz);
}

/* ---------- Menu principal ---------- */
int main(void) {
    srand((unsigned int) time(NULL));

    const char *pastaRaiz = "Insertion Sort";
    criarPastaSeNaoExistir(pastaRaiz);

    TipoInstancia tipoAtual = RANDOMICA;
    int opcao;

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
                if (tamanho <= 0) {
                    printf("Tamanho invalido.\n");
                    break;
                }
                executarInstancia(tamanho, tipoAtual, pastaRaiz);
                break;
            }
            case 2: {
                printf("1 - Randomica\n2 - Crescente\n3 - Decrescente\n");
                int escolha = lerInteiro("Escolha: ");
                if (escolha == 1) tipoAtual = RANDOMICA;
                else if (escolha == 2) tipoAtual = CRESCENTE;
                else if (escolha == 3) tipoAtual = DECRESCENTE;
                else {
                    printf("Opcao invalida.\n");
                    break;
                }
                printf("1 - 10\n2 - 100\n3 - 1000\n4 - 10000\n5 - 100000\n6 - 1000000\n");
                escolha = lerInteiro("Escolha: ");
                int tamanho;
                if (escolha == 1) tamanho = 10;
                else if (escolha == 2) tamanho = 100;
                else if (escolha == 3) tamanho = 1000;
                else if (escolha == 4) tamanho = 10000;
                else if (escolha == 5) tamanho = 100000;
                else if (escolha == 6) tamanho = 1000000;
                else {
                    printf("Opcao invalida.\n");
                    break;
                }
                executarInstancia(tamanho, tipoAtual, pastaRaiz);
                break;
            }
            case 3:
                executarTodasInstancias(pastaRaiz);
                break;
            case 4:
                printf("Encerrando a aplicacao.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}
