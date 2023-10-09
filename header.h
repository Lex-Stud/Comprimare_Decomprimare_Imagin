//Luciu Alexandru Cristian 311CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct imagine {
    unsigned char val_R;
    unsigned char val_G;
    unsigned char val_B;
    unsigned char tip_nod;
    struct imagine *fiu1;
    struct imagine *fiu2;
    struct imagine *fiu3;
    struct imagine *fiu4;
} *Timagine;

typedef struct celula
{ 
  Timagine info;
  struct celula* urm;
} TCelula, *TLista;

typedef struct coada
{ 
  TLista inc, sf;       /* adresa primei si ultimei celule */
} TCoada;

 typedef struct grid {
    unsigned char val_R;
    unsigned char val_G;
    unsigned char val_B;
 } **TGrid, *Tgr;

 unsigned long long mean(TGrid grid, int x1, int x2, int y1, int y2, unsigned char* rosu, unsigned char* verde, unsigned char* albastru);
 Timagine alocImagine();
 Timagine creezImagine(int x1, int y1, int x2, int y2, TGrid grid, int prag);
 void eliberareImagine(Timagine I);
 void tiparire_tip_nod(Timagine nod);
 int numar_niveluri_arbore(Timagine I);
 int nrFrunze(Timagine I);
 void nivelMin(Timagine I, int actual, int *min);
 void Decompresie(Timagine I, FILE * f, TCoada *C);
 void Comprimare(Timagine I, FILE *f, TCoada *C);
 void creezPMM(Timagine I, int x1, int y1, int x2, int y2, TGrid grid);
 void elibereaza_matrice(TGrid matrice, int linii);
 void adaugCoada(TCoada * C, Timagine I);
 TCoada* InitQ ();
 int IntrQ(TCoada *c, Timagine x);
 int ExtrQ(TCoada *c, Timagine *x);
 void DistrQ(TCoada **c);