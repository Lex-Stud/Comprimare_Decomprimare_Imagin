//Luciu Alexandru Cristian 311CB
#include "header.h"

int main(int argc, char * argv[]) {
  int width = 0, height = 0, val_culoare = 0;
  char format[3];
  int i = 0, j = 0;
  Timagine I = NULL;

  //Cerinta 1
  if (strcmp(argv[1], "-c1") == 0) {

    I = alocImagine();
    int prag = atoi(argv[2]);
    char red, gr, blue;
    FILE * PMM = fopen(argv[3], "rb"); // Deschid fierul de citire

    if (PMM == NULL) {
      printf("Nu s-a dechis fisierul");
      exit(-2);
    }

    fgets(format, 3, PMM); // citesc datele de inceput
    fscanf(PMM, "%d %d %d", & width, & height, & val_culoare);
    char newline;
    fscanf(PMM, "%c", & newline); // citesc \n

    TGrid grid = (TGrid) malloc(height * sizeof(Tgr)); // aloc matricea de culori
    if (grid == NULL) {
      printf("Nu s-a alcoat matricea");
      exit(-1);
    }

    for (i = 0; i < height; i++)
      grid[i] = (Tgr) malloc(width * sizeof(struct grid));

    for (i = 0; i < height; i++)
      for (j = 0; j < width; j++) { // citesc matricea de culori
        fread( & grid[i][j].val_R, sizeof(unsigned char), 1, PMM);
        fread( & grid[i][j].val_G, sizeof(unsigned char), 1, PMM);
        fread( & grid[i][j].val_B, sizeof(unsigned char), 1, PMM);
      } // daca mean  > prag inseamna ca arborele are mai multe noduri

    if (mean(grid, 0, height, 0, height, & red, & gr, & blue) > prag) {
      I -> fiu1 = creezImagine(0, width / 2, 0, width / 2, grid, prag);
      I -> fiu2 = creezImagine(0, width / 2, width / 2, width, grid, prag);
      I -> fiu3 = creezImagine(width / 2, width, width / 2, width, grid, prag);
      I -> fiu4 = creezImagine(width / 2, width, 0, width / 2, grid, prag);
    } else {
      I -> tip_nod = 1;
      I -> val_R = red;
      I -> val_G = gr;
      I -> val_B = blue;
    }

    FILE * foutput = fopen(argv[4], "w");

    if (foutput == NULL) {
      printf("Nu s-a deschis fisierul primit ca parametru");
      exit(-2);
    }

    int niveluri = 0, nrdeFrunze = 0, nivelPrimaFrunza = 0;

    niveluri = numar_niveluri_arbore(I); // Detremin numarul de niveluri
    nrdeFrunze = nrFrunze(I); // Determin numarul de frunze
    nivelPrimaFrunza = niveluri;

    // verific in functie daca exista frunze mai sus decat cea de pe ultimul nivel
    nivelMin(I, 0, & nivelPrimaFrunza);

    int putere2 = 1;
    for (i = 0; i < nivelPrimaFrunza; i++)
      putere2 *= 2; // Detrmin partea cea mai mare ramasa intreaga

    nivelPrimaFrunza = height / putere2; // Determin zona cea mai mare care a ramas intreaga

    fprintf(foutput, "%d", niveluri);
    fputc('\n', foutput); // Adaug newline in fisier
    fprintf(foutput, "%d", nrdeFrunze);
    fputc('\n', foutput);
    fprintf(foutput, "%d", nivelPrimaFrunza);
    fputc('\n', foutput);
    fclose(foutput);
    fclose(PMM);
    elibereaza_matrice(grid, height);
    eliberareImagine(I);
  }

  // Cerinta 2

  if (strcmp(argv[1], "-c2") == 0) {

    I = alocImagine();
    int prag = atoi(argv[2]);
    FILE * compresieIntrare = fopen(argv[3], "rb");

    if (compresieIntrare == NULL)
      exit(-2);

    fgets(format, 3, compresieIntrare); // citesc datele de inceput
    fscanf(compresieIntrare, "%d %d %d", & width, & height, & val_culoare);
    char newline = 0;
    fscanf(compresieIntrare, "%c", & newline);

    TGrid grid = (TGrid) malloc(height * sizeof(Tgr)); // aloc matricea de culori
    if (grid == NULL) {
      printf("Nu s-a alcoat matricea");
      exit(-1);
    }

    for (i = 0; i < height; i++)
      grid[i] = (Tgr) malloc(width * sizeof(struct grid));

    for (i = 0; i < height; i++)
      for (j = 0; j < width; j++) { // citesc matricea de culori
        fread( & grid[i][j].val_R, sizeof(unsigned char), 1, compresieIntrare);
        fread( & grid[i][j].val_G, sizeof(unsigned char), 1, compresieIntrare);
        fread( & grid[i][j].val_B, sizeof(unsigned char), 1, compresieIntrare);
      }
    // Construiesc arbore
    unsigned char red, gr, blue;
    if (mean(grid, 0, height, 0, height, & red, & gr, & blue) > prag) {
      I -> fiu1 = creezImagine(0, width / 2, 0, width / 2, grid, prag);
      I -> fiu2 = creezImagine(0, width / 2, width / 2, width, grid, prag);
      I -> fiu3 = creezImagine(width / 2, width, width / 2, width, grid, prag);
      I -> fiu4 = creezImagine(width / 2, width, 0, width / 2, grid, prag);
    } else {
      I -> tip_nod = 1;
      I -> val_R = red;
      I -> val_G = gr;
      I -> val_B = blue;
    }

    FILE * compresieIesire = fopen(argv[4], "wb");

    if (compresieIesire == NULL)
      exit(-2);

    fwrite( & height, sizeof(int), 1, compresieIesire); // Pun in fisier dimensiunea imaginii
    int niveluri = numar_niveluri_arbore(I);
    // Creez coada in care voi adauga fii pentru pargurgerea pe nivel
    TCoada * C = InitQ();
    IntrQ(C, I);
    Comprimare(I, compresieIesire, C);

    DistrQ( & C); // Dezaloc memoria alocata
    elibereaza_matrice(grid, height);
    eliberareImagine(I);
    fclose(compresieIntrare);
    fclose(compresieIesire);
  }

  // Cerinta 3

  if (strcmp(argv[1], "-d") == 0) {
    FILE * fDecompresie = fopen(argv[2], "rb");
    FILE * fIesire = fopen(argv[3], "w");

    if (fDecompresie == NULL || fIesire == NULL)
      exit(-2);

    int size = 0;
    unsigned char red = 0, green = 0, blue = 0, tip = 0;
    fread( & size, sizeof(int), 1, fDecompresie);

    fprintf(fIesire, "P6\n"); // Pun in fisier valorile de inceput
    fprintf(fIesire, "%d %d\n", size, size);
    fprintf(fIesire, "255\n");

    I = alocImagine();

    fread( & tip, sizeof(unsigned char), 1, fDecompresie);
    // Verific daca arborele e alcatuit dint-un nod sau mai multe
    if (tip == 1) {
      I -> tip_nod = 1;
      fread( & red, sizeof(unsigned char), 1, fDecompresie);
      fread( & green, sizeof(unsigned char), 1, fDecompresie);
      fread( & blue, sizeof(unsigned char), 1, fDecompresie);
      I -> val_R = red;
      I -> val_G = green;
      I -> val_B = blue;
    } else {
      I -> tip_nod = 0;
      TCoada * C = InitQ(); // Creez coada pentru parcurgerea pe nivel
      IntrQ(C, I);

      Timagine aux = alocImagine();

      // Cat timp am noduri in coada citesc din fisier tipul respectiv si valoarea culorilor dupa caz
      while (ExtrQ(C, & aux) == 1) {

        if (aux -> tip_nod == 0) {

          fread( & tip, sizeof(unsigned char), 1, fDecompresie);
          aux -> fiu1 = alocImagine();

          if (tip == 0) { // Daca nodul e intern il adaug in coada
            aux -> fiu1 -> tip_nod = tip;
            IntrQ(C, aux -> fiu1);
          } else {
            aux -> fiu1 -> tip_nod = 1; // Daca nodul e frunza il adaug tipul si valorile pentru culori
            fread( & red, sizeof(unsigned char), 1, fDecompresie);
            fread( & green, sizeof(unsigned char), 1, fDecompresie);
            fread( & blue, sizeof(unsigned char), 1, fDecompresie);
            aux -> fiu1 -> val_R = red;
            aux -> fiu1 -> val_G = green;
            aux -> fiu1 -> val_B = blue;
          }

          fread( & tip, sizeof(unsigned char), 1, fDecompresie);
          aux -> fiu2 = alocImagine();

          if (tip == 0) {
            aux -> fiu2 -> tip_nod = tip;
            IntrQ(C, aux -> fiu2);
          } else {
            aux -> fiu2 -> tip_nod = 1;
            fread( & red, sizeof(unsigned char), 1, fDecompresie);
            fread( & green, sizeof(unsigned char), 1, fDecompresie);
            fread( & blue, sizeof(unsigned char), 1, fDecompresie);
            aux -> fiu2 -> val_R = red;
            aux -> fiu2 -> val_G = green;
            aux -> fiu2 -> val_B = blue;
          }

          fread( & tip, sizeof(unsigned char), 1, fDecompresie);
          aux -> fiu3 = alocImagine();

          if (tip == 0) {
            aux -> fiu3 -> tip_nod = tip;
            IntrQ(C, aux -> fiu3);
          } else {
            aux -> fiu3 -> tip_nod = 1;
            fread( & red, sizeof(unsigned char), 1, fDecompresie);
            fread( & green, sizeof(unsigned char), 1, fDecompresie);
            fread( & blue, sizeof(unsigned char), 1, fDecompresie);
            aux -> fiu3 -> val_R = red;
            aux -> fiu3 -> val_G = green;
            aux -> fiu3 -> val_B = blue;
          }

          fread( & tip, sizeof(unsigned char), 1, fDecompresie);
          aux -> fiu4 = alocImagine();

          if (tip == 0) {
            aux -> fiu4 -> tip_nod = tip;
            IntrQ(C, aux -> fiu4);
          } else {
            aux -> fiu4 -> tip_nod = 1;
            fread( & red, sizeof(unsigned char), 1, fDecompresie);
            fread( & green, sizeof(unsigned char), 1, fDecompresie);
            fread( & blue, sizeof(unsigned char), 1, fDecompresie);
            aux -> fiu4 -> val_R = red;
            aux -> fiu4 -> val_G = green;
            aux -> fiu4 -> val_B = blue;
          }
        }
      }
      DistrQ( & C);
    }

    TGrid grid = (TGrid) malloc(size * sizeof(Tgr)); // aloc matricea de culori
    if (grid == NULL) {
      printf("Nu s-a alcoat matricea");
      exit(-1);
    }

    for (i = 0; i < size; i++)
      grid[i] = (Tgr) malloc(size * sizeof(struct grid));

    creezPMM(I, 0, size, 0, size, grid); // Creez o matrice de culori

    for (i = 0; i < size; i++) // Scriu valorile culorilor in fisier 
      for (j = 0; j < size; j++) {
        fwrite( & grid[i][j].val_R, sizeof(unsigned char), 1, fIesire);
        fwrite( & grid[i][j].val_G, sizeof(unsigned char), 1, fIesire);
        fwrite( & grid[i][j].val_B, sizeof(unsigned char), 1, fIesire);
      }

    elibereaza_matrice(grid, size);
    eliberareImagine(I);
    fclose(fDecompresie);
    fclose(fIesire);
  }

  return 0;
}