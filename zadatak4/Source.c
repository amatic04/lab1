/* 4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani. */

//sortirani unos i ispis

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE (150)

typedef struct _poly* position;
typedef struct _poly {
	int koef;
	int eks;
	position next;
}poly;
int insertSorted(position, int, int);
int printPoly(position);

int main() {
	poly head1 = { .next = NULL, .koef = 0, .eks = 0 };
	poly head2 = { .next = NULL, .koef = 0, .eks = 0 };
	int status = 0;
	FILE* fp;
	char buffer[MAX_LINE];
	char* buf;
	int koef, eks, count;

	fp = fopen("polynomes.txt", "r");
	if (fp == NULL) {
		printf("\nGreska pri otvaranju datoteke!");
		exit(1);
	}
	fgets(buffer, MAX_LINE, fp);
	buf = buffer;
	while (strlen(buf) != 0) {
		sscanf(buf, "%dx^%d %n", &koef, &eks, &count);
		status = insertSorted(&head1, koef, eks);
		if (status != 0)
			return -2;
		buf = buf + count;

	}
	fgets(buffer, MAX_LINE, fp);
	buf = buffer;
	while (strlen(buf) != 0) {
		sscanf(buf, "%dx^%d %n", &koef, &eks, &count);
		status = insertSorted(&head2, koef, eks);
		if (status != 0)
			return -2;
		buf = buf + count;
	}
	printPoly(&head1);
	printf("\n");
	printPoly(&head2);
	return 0;
}
int insertSorted(position head, int koef, int eks) {
	position current = head;
	position new;

	if (current->next != NULL) {
		while (current->next != NULL && current->next->eks >= eks) {
			current = current->next;
		}
		if (current->eks == eks) {
			current->koef = current->koef + koef;
			return 0;
		}
	}
	new = (position)malloc(sizeof(poly));
	if (new == NULL) {
		printf("Greska pri alociranju memorije!");
		exit(1);
	}
	new->koef = koef;
	new->eks = eks;

	new->next = current->next;
	current->next = new;

	return 0;
}
int printPoly(position head) {
	position first = head->next;
	printf("\n");
	if (first) {
		printf("%dx^%d", first->koef, first->eks);
		first = first->next;
	}
	for (; first != NULL; first = first->next) {
		printf(" + %dx^%d", first->koef, first->eks);

	}
	return 0;
}
