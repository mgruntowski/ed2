#include <time.h>
#include <stdlib.h>
#include "abb.h"

Arvore *cria_arvore_vazia(void)
{
  return NULL;
}

void arvore_libera(Arvore *a)
{
  if (a != NULL)
  {
    arvore_libera(a->esq);
    arvore_libera(a->dir);
    free(a);
  }
}

//========= Q1 - inserir
Arvore *inserir(Arvore *a, int v)
{
  if (a == NULL)
  {
    a = (Arvore *)malloc(sizeof(Arvore));
    a->info = v;
    a->esq = NULL;
    a->dir = NULL;
  }
  else if (v < a->info)
    a->esq = inserir(a->esq, v);
  else
    a->dir = inserir(a->dir, v);

  return a;
}

//========= Q1 - remover
Arvore *remover(Arvore *a, int v)
{
  if (a == NULL)
    return NULL;

  if (v < a->info)
    a->esq = remover(a->esq, v);
  else if (v > a->info)
    a->dir = remover(a->dir, v);
  else
  {
    if (a->esq == NULL && a->dir == NULL)
    {
      free(a);
      a = NULL;
    }
    else if (a->dir == NULL)
    {
      Arvore *tmp = a;
      a = a->esq;
      free(tmp);
    }
    else if (a->esq == NULL)
    {
      Arvore *tmp = a;
      a = a->dir;
      free(tmp);
    }
    else
    {
      Arvore *tmp = a->esq;

      while (tmp->dir != NULL)
        tmp = tmp->dir;

      a->info = tmp->info;
      tmp->info = v;
      a->esq = remover(a->esq, v);
    }
  }

  return a;
}

//========= Q1 - busca
int buscar(Arvore *a, int v)
{
  if (a == NULL)
    return 0;

  if (v < a->info)
    return buscar(a->esq, v);

  if (v > a->info)
    return buscar(a->dir, v);

  return 1;
}

//========= Q2 - min =====

int min(Arvore *a)
{
  if (a == NULL)
    return 0;

  if (a->esq == NULL)
    return a->info;

  return min(a->esq);
}

//========= Q2 - max =====

int max(Arvore *a)
{
  if (a == NULL)
    return 0;

  if (a->dir == NULL)
    return a->info;

  return max(a->dir);
}

//========= Q3 - imprime_decrescente =====

void imprime_decrescente(Arvore *a)
{
  if (a != NULL)
  {
    imprime_decrescente(a->dir);
    printf("%d ", a->info);
    imprime_decrescente(a->esq);
  }
}

//========= Q4 - maior ramo =====

int maior_ramo(Arvore *a)
{
  if (a == NULL)
    return 0;

  int valorEsq = maior_ramo(a->esq);
  int valorDir = maior_ramo(a->dir);

  return a->info + (valorEsq > valorDir ? valorEsq : valorDir);
}

void pre_order(Arvore *a)
{
  if (a != NULL)
  {
    printf("%d ", a->info);
    pre_order(a->esq);
    pre_order(a->dir);
  }
}

//========= Q5 - busca em ordenado e aleatorio =====

Arvore *insere_ordenado(Arvore *a, int quantidade)
{
  for (int i = 0; i < quantidade; i++)
  {
    a = inserir(a, i);
  }

  return a;
}

Arvore *insere_aleatorio(Arvore *a, int quantidade)
{
  srand(time(NULL));

  for (int i = 0; i < quantidade; i++)
  {
    a = inserir(a, rand() % quantidade);
  }

  return a;
}

int main()
{

  int i;

  Arvore *a = cria_arvore_vazia();

  printf("Exercicio 1\n");
  a = inserir(a, 50);
  a = inserir(a, 30);
  a = inserir(a, 90);
  a = inserir(a, 20);
  a = inserir(a, 40);
  a = inserir(a, 95);
  a = inserir(a, 10);
  a = inserir(a, 35);
  a = inserir(a, 45);

  printf("Árvore inicial: ");
  pre_order(a);

  printf("\nRemover 40: ");
  a = remover(a, 40);
  pre_order(a);

  a = inserir(a, 40);

  printf("\nBuscar 10: ");
  int achou = buscar(a, 10);
  printf("%d", achou);

  printf("\nBuscar 40: ");
  achou = buscar(a, 40);
  printf("%d", achou);

  printf("\n\nExercicio 2\n");
  int minVal = min(a);
  printf("Minimo: %d", minVal);
  int maxVal = max(a);
  printf("\nMaximo: %d", maxVal);

  printf("\n\nExercicio 3\n");
  imprime_decrescente(a);

  printf("\n\nExercicio 4\n");
  int valorMaiorRamo = maior_ramo(a);
  printf("Valor do maior ramo: %d", valorMaiorRamo);

  printf("\n\nExercicio 5\n");
  printf("a) ");

  Arvore *ordenada = cria_arvore_vazia();
  ordenada = insere_ordenado(ordenada, 100000);

  clock_t t1;
  t1 = clock();

  int achouOrdenada = buscar(ordenada, 100000);

  t1 = clock() - t1;
  double tempoOrdenada = ((double)t1) / CLOCKS_PER_SEC;

  printf("%fs, achou? %d", tempoOrdenada, achouOrdenada);

  printf("\nb) ");

  Arvore *aleatoria = cria_arvore_vazia();
  aleatoria = insere_aleatorio(aleatoria, 100000);

  clock_t t2;
  t2 = clock();

  int achouAleatoria = buscar(aleatoria, 100000);

  t2 = clock() - t2;
  double tempoAleatoria = ((double)t2) / CLOCKS_PER_SEC;

  printf("%fs, achou? %d", tempoAleatoria, achouAleatoria);

  // A b) demora menos porque a altura da árvore a) é n, enquanto a altura da árvore b) é aleatória

  return 0;
}
