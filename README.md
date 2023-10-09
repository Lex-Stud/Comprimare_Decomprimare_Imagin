LEGENDA COD EXIT:
 -1 Nu s-a alocat memorie
 -2 Nu s-a dechis fisierul


Determin dupa valoarea lui argv[1] cerinta care trebuie rezolvata

Rezolvare cerinta 1

Deschid fisierele aflate in argv pe pozitia 3 si 4 si determin pragul afalat pe pozitia 2

Citesc din fisierul binar marimea matricei si valoarea maxima pe care o poate lua o culoare si aloc spatiu pentru o matrice de culor de width *  height

Cu ajutorul functiei creezImagine formez arborele cuatrenar

In functia creezImagine parcurg matricea de culori de culori cu linile de la x1 la x2 si coloanele de la y1 la y2 si determin mean. Daca mean > prag creez Nodul curent devine intern si creez inca 4 noduri impartind matricea initiala astfel 
            I -> fiu1 = creezImagine(x1, (x1 + x2) / 2, y1, (y2 + y1) / 2, grid, prag);
            I -> fiu2 = creezImagine(x1, (x1 + x2) / 2, (y2 + y1) / 2, y2, grid, prag);
            I -> fiu3 = creezImagine((x1 + x2) / 2, x2, (y2 + y1) / 2, y2, grid, prag);
            I -> fiu4 = creezImagine((x1 + x2) / 2, x2, y1, (y2 + y1) / 2, grid, prag);

Cu jutorul functiilor: numar_niveluri_arbore(I), nrFrunze(I), nivelPrimaFrunzadetrmin numarul de niveluri frunze i frunza de pe cel mai jos nivel. Cu ajutorul unui for determin 2 la puterea nivelPrima frunza pentriu a afla dimensiunea.

Cerinta 2

Deschid fisierele aflate in argv pe pozitia 3 si 4 si determin pragul afalat pe pozitia 2

Creez arborele cuaternar si o coada pentru parcurgerea in latime

In functia comprimare void Comprimare(Timagine I, FILE * f, TCoada * C)
 
 I - nodul curent
 f - fisierul in care scriu
 C - coada

 Determin tipul nodului si dupa caz adaug in fisier si valorile pentru culori (in caz ca nodul e frunza)
 Daca nodul e intern il adaug in coada pentru a pargurge arborele in latime.


Cerinta 3

Deschid fisierele aflate in argv pe pozitia 2 si 3

Scriu in fisierul de iesire tipul P6 marimea si valoarea maxima pentru o culare

Verific daca arbrele este alcatuit dintr-un dod sau mai multe.

Creez o coada penteru parcurgerea in latime a arborelui in care adaug radacina

Cu ajutorul unui while extrag din coada nodul pentru care citesc din fisier tipul pentru fiecare fiu. Daca fiuol este de tip  0 il adaug in coada. Altfel il adaug ca nod terminal.

Dupa ce am construit arborele aloc spatiu pentr o matrice de culori si cu ahutoruol functiei creezPMM scriu umplu matricea

void creezPMM(Timagine I, int x1, int x2, int y1, int y2, TGrid grid)

I - nodul curent
x1 x2 y1 y2 - coodronatele pentru care scriu in matrice
grid matricea de culori