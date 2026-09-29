#ifndef OPERACOES_H
#define OPERACOES_H

#define CRESCENTE   0
#define DECRESCENTE 1
#define RANDOMICA   2

#define INSERTION 0
#define BUBBLE    1
#define SHELL     2
#define SELECTION 3

int lerInteiro(const char *prompt);

int lerAlgoritmo(void);
const char *nomeTipo(int tipo);
void operacoes(int algoritmo, int tipo, int tamanho);

#endif
