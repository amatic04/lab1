#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u èvorove binarnog stabla.

a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraæa
pokazivaè na korijen stabla.

b) Napisati funkciju replace koja æe svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat æe se u stablo na
slici Slika 2.

c) Prepraviti program na naèin da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira sluèajne brojeve u rasponu <10, 90>. Takoðer, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka

*/

typedef struct cvor Cvor;
typedef Cvor* position;
struct cvor {
    int element;
    position L;
    position R;
};

position addCvor(position root, int newElement);
int replace(position root);
int fprint_inorder(position root, FILE* file);

int main()
{

    position root = NULL;

    root = addCvor(root, 2);
    addCvor(root, 5);
    addCvor(root, 7);
    addCvor(root, 8);
    addCvor(root, 11);
    addCvor(root, 1);
    addCvor(root, 4);
    addCvor(root, 2);
    addCvor(root, 3);
    addCvor(root, 7);

    FILE* file = NULL;
    file = fopen("dat.txt", "w");

    fprint_inorder(root, file);
    fprintf(file, "\n");
    replace(root);

    fprint_inorder(root, file);


    // c)

    position randRoot = NULL;

    srand(time(NULL));

    int x = 0;

    for (int i = 0; i < 8; i++) {
        x = rand() % 81 + 10;
        randRoot = addCvor(randRoot, x);
    }

    return 0;
}

position addCvor(position root, int newElement) {

    if (root == NULL) {
        root = (position)malloc(sizeof(Cvor));

        if (root == NULL) {
            printf("ERROR alocating memory");
            return NULL;
        }

        root->element = newElement;
        root->L = root->R = NULL;
    }
    else {
        if (newElement >= root->element) {
            root->L = addCvor(root->L, newElement);
        }
        else {
            root->R = addCvor(root->R, newElement);
        }
    }

    return root;
}

int replace(position root) {

    if (root == NULL) {
        return 0;
    }
    int x = root->element;
    root->element = replace(root->L) + replace(root->R);
    x += root->element;

    return x;
}

int fprint_inorder(position root, FILE* file) {

    if (file == NULL) {
        printf("ERROR opening file\n");
        return 1;
    }

    if (root == NULL) {
        return 0;
    }
    fprint_inorder(root->L, file);
    fprintf(file, "%d, ", root->element);
    fprint_inorder(root->R, file);

    return 0;
}