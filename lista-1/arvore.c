#include "arvore.h"

Arvore *cria_arv_vazia(void)
{
  return NULL;
}

Arvore *constroi_arv(char c, Arvore *e, Arvore *d)
{
  Arvore *no = (Arvore *)malloc(sizeof(Arvore));
  no->info = c;
  no->esq = e;
  no->dir = d;
  return no;
}

int verifica_arv_vazia(Arvore *a)
{
  return (a == NULL);
}

void arv_libera(Arvore *a)
{
  if (!verifica_arv_vazia(a))
  {
    arv_libera(a->esq);
    arv_libera(a->dir);
    free(a);
  }
}

//========= Exercício 2 - pré-ordem ====

void pre_ordem(Arvore *a)
{
  if (!verifica_arv_vazia(a))
  {
    printf("%s ", &a->info);
    pre_ordem(a->esq);
    pre_ordem(a->dir);
  }
}

//========= Exercício 2 - in-ordem ====

void in_ordem(Arvore *a)
{
  if (!verifica_arv_vazia(a))
  {
    in_ordem(a->esq);
    printf("%s ", &a->info);
    in_ordem(a->dir);
  }
}

//========= Exercício 2 - pós-ordem ====

void pos_ordem(Arvore *a)
{
  if (!verifica_arv_vazia(a))
  {
    pos_ordem(a->esq);
    pos_ordem(a->dir);
    printf("%s ", &a->info);
  }
}

//========= Exercício 3 - pertence ====

int pertence_arv(Arvore *a, char c)
{
  if (verifica_arv_vazia(a))
    return 0;

  if (a->info == c ||
      pertence_arv(a->esq, c) ||
      pertence_arv(a->dir, c))
  {
    return 1;
  }

  return 0;
}

//========= Exercício 4 - conta nós ====

int conta_nos(Arvore *a)
{
  if (verifica_arv_vazia(a))
    return 0;

  return conta_nos(a->esq) + conta_nos(a->dir) + 1;
}

//========= Exercício 5 - calcula altura ====

int calcula_altura_arvore(Arvore *a)
{
  if (verifica_arv_vazia(a))
    return -1;

  int alturaEsq = calcula_altura_arvore(a->esq) + 1;
  int alturaDir = calcula_altura_arvore(a->dir) + 1;

  return alturaEsq > alturaDir ? alturaEsq : alturaDir;
}

//========= Exercício 6 - conta folhas ====

int conta_nos_folha(Arvore *a)
{
  if (verifica_arv_vazia(a))
    return 0;

  if (verifica_arv_vazia(a->esq) && verifica_arv_vazia(a->dir))
    return 1;

  return conta_nos_folha(a->esq) + conta_nos_folha(a->dir);
}

int main(int argc, char *argv[])
{

  Arvore *a = constroi_arv('a',
                           constroi_arv('b',
                                        cria_arv_vazia(),
                                        constroi_arv('d', cria_arv_vazia(), cria_arv_vazia())),
                           constroi_arv('c',
                                        constroi_arv('e', cria_arv_vazia(), cria_arv_vazia()),
                                        constroi_arv('f', cria_arv_vazia(), cria_arv_vazia())));

  printf("Exercicio 2\n");
  printf("Pre ordem: ");
  pre_ordem(a);
  printf("\nIn ordem: ");
  in_ordem(a);
  printf("\nPos ordem: ");
  pos_ordem(a);

  printf("\n\nExercicio 3\n");
  char teste = 'a';
  int result = pertence_arv(a, teste);
  printf("%c pertence? R: %d", teste, result);

  printf("\n\nExercicio 4\n");
  int total = conta_nos(a);
  printf("Total de nos: %d", total);

  printf("\n\nExercicio 5\n");
  int altura = calcula_altura_arvore(a);
  printf("Altura: %d", altura);

  printf("\n\nExercicio 6\n");
  int totalFolhas = conta_nos_folha(a);
  printf("Total de folhas: %d", totalFolhas);

  arv_libera(a);

  return 0;
}
