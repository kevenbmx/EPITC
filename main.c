#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define M_PI 3.14159265358979323846
#define MAX_AFD_SZ 200
#define swap(type, i, j) {type vaux = i; i = j; j = vaux;}

#include "afd_util.h"

/* **************************************************** */

/*
  InicializaAFD(AFD, n, s):
  Inicializa a estrutura para um AFD com n estados e s simbolos
  Aloca espaco para o vetor binario de estados finais e para a matriz de transicao
*/
void InicializaAFD(tAFD *aut, int n, int s) {
  int i, j;
  aut->n = n;
  aut->s = s;

  aut->F = (int*) calloc(n, sizeof(int));
  for (i=0; i<n; i++) aut->F[i] = 0;

  aut->Delta = (int**) calloc(n, sizeof(int*));
  for (i=0;i<n; i++)
    aut->Delta[i] = (int*) calloc(s, sizeof(int));

  for (i=0; i<n; i++)
    for (j=0; j<s; j++)
      aut->Delta[i][j] = -1;
}


/*
  LiberaAFD(AFD): Liberar o espaco ocupado por um AFD.
*/
void LiberaAFD (tAFD *aut) {
  int i;
  int *v;

  free(aut->F);
  for (i=0;i<aut->n; i++) {
    v = aut->Delta[i];
    free(v);
  }
  free(aut->Delta);
  aut->n = aut->s = 0;
}
/*
  Codigo de saida:
    1: leitura bem sucedida
    0: erro na leitura do arquivo
*/
int LeAFDTXT(char* nomearq, tAFD *aut) {
  FILE *fp;
  int i, j, n, s, q0;

  fp = fopen(nomearq, "rt");
  if (fp==NULL)
     return(0);

  if (fscanf(fp, "%u %u %u", &n, &s, &q0)!=3)
    return(0);

  InicializaAFD(aut, n, s);

  aut->n = n;
  aut->s = s;
  aut->q0 = q0;

  for (i=0;i<n;i++) {
    if (fscanf(fp, "%d", &(aut->F[i])) !=1 ) {
      LiberaAFD(aut);
      return(0);
    }
  }

  // for (i=0;i<n;i++) printf("elemento %d: %d\n", i, aut->F[i]);

  for (i=0;i<n; i++)
    for (j=0; j<s; j++) {
      if (fscanf(fp, "%d", &(aut->Delta[i][j])) != 1) {
        LiberaAFD(aut);
        return(0);
      }
    }

  fclose(fp);
  return(1);
}

/*
  EscreveFD(nomearq, aut)
  Escreve o automato no arquivo nomearq
  Lay-out: identico aa funcao LeAFDTXT

  Codigo de saida:
    1: escrita bem sucedida
    0: erro na escrita do arquivo
*/
int EscreveAFDTXT(char* nomearq, tAFD *aut) {
  FILE *fp;
  int i, j;

  fp = fopen(nomearq, "wt");
  if (fp==NULL)
     return(0);

  fprintf(fp, "%d %d %d\n", aut->n,  aut->s, aut->q0);

  for (i=0;i<aut->n;i++)
    fprintf(fp, "%d ", aut->F[i]);
  fprintf(fp, "\n");

  for (i=0;i<aut->n; i++) {
    for (j=0; j<aut->s; j++)
      fprintf(fp, "%d ", aut->Delta[i][j]);
    fprintf(fp, "\n");
  }

  fclose(fp);
  return(1);
}


int main(){
tAFD* inicio = malloc(sizeof(tAFD));

return(0);
}
/*
int main(int argc, char *argv[]) {
    tAFD inicio = malloc(sizeof(tAFD));

return(0);
}*/

