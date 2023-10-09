//Luciu Alexandru Cristian 311CB
#include "header.h"

unsigned long long mean(TGrid grid, int x1, int x2, int y1, int y2, unsigned char * rosu, unsigned char * verde, unsigned char * albastru) {
  int size = x2 - x1; // Determin marimea matricei pentru care fac media
  int i, j;
  unsigned long long red = 0, green = 0, blue = 0, mean = 0;
  for (i = x1; i < x2; i++)
    for (j = y1; j < y2; j++) {
      red = red + grid[i][j].val_R;
      green = green + grid[i][j].val_G;
      blue = blue + grid[i][j].val_B;
    }
  red = red / (size * size); // Calulez media dupa forumula furnizata
  green = green / (size * size);
  blue = blue / (size * size);
  red = (unsigned char) (red);
  green = (unsigned char)(green);
  blue = (unsigned char) (blue);

  * rosu = red;
  * verde = green;
  * albastru = blue;
  // Determin mean
  for (i = x1; i < x2; i++)
    for (j = y1; j < y2; j++)
      mean += (red - grid[i][j].val_R) * (red - grid[i][j].val_R) + (green - grid[i][j].val_G) * (green - grid[i][j].val_G) + (blue - grid[i][j].val_B) * (blue - grid[i][j].val_B);
  mean = mean / (3 * size * size);

  // Determin partea intreaga

  mean = (long long) (mean);

  return mean;
}

Timagine alocImagine() {
  Timagine I = (Timagine) malloc(sizeof(struct imagine));

  if (I == NULL) // Verific daca s-a alocat memorie pentr o imagine
    exit(-1);

  I -> fiu1 = NULL;
  I -> fiu2 = NULL;
  I -> fiu3 = NULL;
  I -> fiu4 = NULL;

  return I;
}

Timagine creezImagine(int x1, int x2, int y1, int y2, TGrid grid, int prag) {
  int i, j;
  unsigned char rosu, verde, albastru;
  Timagine I = alocImagine();
  if (mean(grid, x1, x2, y1, y2, & rosu, & verde, & albastru) > prag) { // imaginea nu e uniforma
    I -> tip_nod = 0; // Inseamna ca nodul nu e frunza
    I -> fiu1 = creezImagine(x1, (x1 + x2) / 2, y1, (y2 + y1) / 2, grid, prag);
    I -> fiu2 = creezImagine(x1, (x1 + x2) / 2, (y2 + y1) / 2, y2, grid, prag);
    I -> fiu3 = creezImagine((x1 + x2) / 2, x2, (y2 + y1) / 2, y2, grid, prag);
    I -> fiu4 = creezImagine((x1 + x2) / 2, x2, y1, (y2 + y1) / 2, grid, prag);

  } else { // imagine e uniforma
    I -> tip_nod = 1;
    I -> val_R = rosu;
    I -> val_G = verde;
    I -> val_B = albastru;
  }
  return I;
}

int numar_niveluri_arbore(Timagine I) {
  if (I == NULL) {
    return 0;
  } else { // Determin cel mai mare nivel din partea stanga si dreapat
    int stanga1 = numar_niveluri_arbore(I -> fiu1);
    int stanga2 = numar_niveluri_arbore(I -> fiu2);
    int dreapta1 = numar_niveluri_arbore(I -> fiu3);
    int dreapta2 = numar_niveluri_arbore(I -> fiu4);
    int nivel_maxim_stanga = (stanga1 > stanga2) ? stanga1 : stanga2;
    int nivel_maxim_dreapta = (dreapta1 > dreapta2) ? dreapta1 : dreapta2;
    return (nivel_maxim_stanga > nivel_maxim_dreapta) ? (nivel_maxim_stanga + 1) : (nivel_maxim_dreapta + 1); // Returnez cel mai inalt nivel
  }
}

int nrFrunze(Timagine I) {

  if (I == NULL) return 0;

  if (I -> fiu1 == NULL && I -> fiu2 == NULL && I -> fiu3 == NULL && I -> fiu4 == NULL) // verific daca nodul e furunza
    return 1;
  int nr = 0;
  nr += nrFrunze(I -> fiu1);
  nr += nrFrunze(I -> fiu2);
  nr += nrFrunze(I -> fiu3);
  nr += nrFrunze(I -> fiu4);

  return nr;
}

void nivelMin(Timagine I, int actual, int * min) {

  if (I == NULL) return;

  if (I -> fiu1 == NULL && I -> fiu2 == NULL && I -> fiu3 == NULL && I -> fiu4 == NULL)
    if (actual <= * min) // Compar actual (initila 0) cu minim (initila nr max niveluri)
      min = actual;

  nivelMin(I -> fiu1, actual + 1, min);
  nivelMin(I -> fiu2, actual + 1, min);
  nivelMin(I -> fiu3, actual + 1, min);
  nivelMin(I -> fiu4, actual + 1, min);
}

void eliberareImagine(Timagine I) {
  // Functie de eliberare recursiva de eliberare a memoriei
  if (I != NULL) {
    eliberareImagine(I -> fiu1);
    eliberareImagine(I -> fiu2);
    eliberareImagine(I -> fiu3);
    eliberareImagine(I -> fiu4);
    free(I);
  }

}

void Comprimare(Timagine I, FILE * f, TCoada * C) {
  ExtrQ(C, & I);
  if (I == NULL) return;

  if (I -> tip_nod == 0) { // Daca nodul e de tip 0 adaug in fisier tipul
    fwrite( & (I -> tip_nod), sizeof(unsigned char), 1, f);
  } else { // Daca nodul e de tip 1 adaug in fisier tipul si valorile pentru culori
    fwrite( & (I -> tip_nod), sizeof(unsigned char), 1, f);
    fwrite( & (I -> val_R), sizeof(unsigned char), 1, f);
    fwrite( & (I -> val_G), sizeof(unsigned char), 1, f);
    fwrite( & (I -> val_B), sizeof(unsigned char), 1, f);
  }
  // Daca nodul nu e frunza ii adaug in fisier fii
  if (I -> fiu1 != NULL && I -> fiu2 != NULL && I -> fiu3 != NULL && I -> fiu4 != NULL) {
    IntrQ(C, I -> fiu1);
    IntrQ(C, I -> fiu2);
    IntrQ(C, I -> fiu3);
    IntrQ(C, I -> fiu4);
  }
  //Daca coada nu e nula aplic functia pentru urmatoarea valoare
  if (C -> inc != NULL)
    Comprimare(I, f, C);
  else return;

}

void creezPMM(Timagine I, int x1, int x2, int y1, int y2, TGrid grid) {
  int i, j;

  if (I -> tip_nod == 1) {
    // Daca nodul e frunza scriu valorile in matrice 
    for (i = x1; i < x2; i++)
      for (j = y1; j < y2; j++) {
        grid[i][j].val_R = I -> val_R;
        grid[i][j].val_G = I -> val_G;
        grid[i][j].val_B = I -> val_B;
      }
  } else { // Functie recursiva pana ajung la un nod
    creezPMM(I -> fiu1, x1, (x1 + x2) / 2, y1, (y2 + y1) / 2, grid);
    creezPMM(I -> fiu2, x1, (x2 + x1) / 2, (y1 + y2) / 2, y2, grid);
    creezPMM(I -> fiu3, (x1 + x2) / 2, x2, (y2 + y1) / 2, y2, grid);
    creezPMM(I -> fiu4, (x1 + x2) / 2, x2, y1, (y1 + y2) / 2, grid);
  }
}

void elibereaza_matrice(TGrid matrice, int linii) {
  // Elibereaza fiecare linie a matricii
  int i = 0;
  for (i = 0; i < linii; i++) {
    free(matrice[i]);
  }

  // Elibereaza pointerul la pointerul la structura Tgr
  free(matrice);
  matrice = NULL;
}

/* FuncTia de adaugare a unui element in coada */
int IntrQ(TCoada * c, Timagine x) {
  TLista aux = NULL;
  aux = (TLista) malloc(sizeof(TCelula));
  if (!aux) return 0;
  aux -> info = x;
  aux -> urm = NULL;
  if (c -> sf != NULL) c -> sf -> urm = aux;
  else c -> inc = aux;
  c -> sf = aux;
  return 1;
}

/* FuncTia de extragere a unui element din coada */
int ExtrQ(TCoada * c, Timagine * x) {
  TLista aux = NULL;
  if (c -> inc == NULL) return 0;
  aux = c -> inc;
  * x = aux -> info;
  c -> inc = aux -> urm;
  if (c -> inc == NULL) c -> sf = NULL;
  free(aux);
  return 1;
}

/* FuncTia de distrugere a cozii */
void DistrQ(TCoada ** c) {
  TLista p, aux;
  p = ( * c) -> inc;
  while (p) {
    aux = p;
    p = p -> urm;
    free(aux);
  }
  free( * c);
  * c = NULL;
}

/* FuncTia de iniTializare coada */
TCoada * InitQ() {
  TCoada * c = (TCoada * ) malloc(sizeof(TCoada));
  if (!c) return NULL;
  c -> inc = c -> sf = NULL;
  return c;
}