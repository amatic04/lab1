/* 4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
čitaju iz datoteke. Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_LINE 1024
#define ALLOCATION_ERROR (-1)
#define FILE_OPEN_ERROR (-2)

struct _polynom;
typedef struct _polynom* position;
typedef struct _polynom {
	int coef;
	int exp;
	position next;
}polynom;

int read_from_file();
int read();
int insert_sorted();
position create_element();
int print_poly();
int sum_poly();
int mult_poly();
int deleteAll();

int main()
{
	char fileName[MAX_LINE] = { 0 };
	polynom head1 = { .coef = 0, .exp = 0, .next = NULL };
	polynom head2 = { .coef = 0, .exp = 0, .next = NULL };
	polynom headSum = { .coef = 0, .exp = 0, .next = NULL };
	polynom headProduct = { .coef = 0, .exp = 0, .next = NULL };

	position p1 = &head1;
	position p2 = &head2;
	position pS = &headSum;
	position pP = &headProduct;

	printf("Enter file name: ");
	scanf(" %s", fileName);


	if (read_from_file(p1, p2, fileName) == EXIT_SUCCESS)
	{
		printf("\nFirst polynomial: ");
		print_poly(p1->next);

		printf("\n\nSecond polynomial: ");
		print_poly(p2->next);

		sum_poly(p1->next, p2->next, pS);
		printf("\n\nSum of polynomials: ");
		print_poly(pS->next);

		mult_poly(p1->next, p2->next, pP);
		printf("\n\nProduct of polynomials: ");
		print_poly(pP->next);
	}

	deleteAll(p1);
	deleteAll(p2);
	deleteAll(pS);
	deleteAll(pP);

	printf("\n");

	return EXIT_SUCCESS;
}

int read_from_file(position head1, position head2, char* fileName)
{
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("\nDear customer, the file %s didn't open! Possible wrong insert!\r\n", fileName);
		return FILE_OPEN_ERROR;
	}
	char string[MAX_LINE];

	fgets(string, MAX_LINE, fp);
	read(head1, string, strlen(string));
	fgets(string, MAX_LINE, fp);
	read(head2, string, strlen(string));

	fclose(fp);


	return EXIT_SUCCESS;
}

int read(position head, char* string, int n)
{
	string[n] = 0;
	int c = 0, e = 0;
	int t = 0;
	char* sstring = string;
	int check = 0;

	while (strlen(sstring) > 0)
	{

		t = 0;

		check = sscanf(sstring, " %d %d %n ", &c, &e, &t);
		if (check != 2)
			break;
		sstring += t;

		insert_sorted(head, c, e);

	}

	return EXIT_SUCCESS;

}


int insert_sorted(position head, int c, int e)
{
	position temp = head;
	position newEl = NULL;

	while (temp->next != NULL && temp->next->exp > e)
		temp = temp->next;

	if (temp->next != NULL && temp->next->exp == e)
		temp->next->coef += c;

	else
	{
		newEl = create_element(c, e);
		newEl->next = temp->next;
		temp->next = newEl;
	}
	return EXIT_SUCCESS;
}

position create_element(int c, int e)
{
	position newEl = NULL;
	newEl = (position)malloc(sizeof(polynom));
	if (!newEl)
	{
		perror("Can't allocate memory!\n");
		return ALLOCATION_ERROR;
	}

	newEl->exp = e;
	newEl->coef = c;


	return newEl;
}

int print_poly(position first)
{
	position temp = first;


	while (temp)
	{
		if (temp->coef != 0) {
			if (temp->exp == 0)
				printf(" %d ", temp->coef);
			else if (temp->exp == 1 && temp->coef == 1)
				printf(" X ");
			else if (temp->exp == 1)
				printf(" %dX ", temp->coef);
			else if (temp->coef == 1)
				printf(" X^%d ", temp->exp);
			else
				printf(" %dX^%d ", temp->coef, temp->exp);

			if (temp->next != NULL)
				printf("+");
		}

		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int sum_poly(position first1, position first2, position headSum)
{
	position temp1 = first1;
	position temp2 = first2;

	while (temp1)
	{
		insert_sorted(headSum, temp1->coef, temp1->exp);
		temp1 = temp1->next;
	}
	while (temp2)
	{
		insert_sorted(headSum, temp2->coef, temp2->exp);
		temp2 = temp2->next;
	}

	return EXIT_SUCCESS;

}

int mult_poly(position first1, position first2, position headProduct)
{
	position temp1 = first1;
	position temp2 = first2;

	while (temp1)
	{
		temp2 = first2;

		while (temp2)
		{
			insert_sorted(headProduct, temp1->coef * temp2->coef, temp1->exp + temp2->exp);
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}

	return EXIT_SUCCESS;

}

int deleteAll(position p) {
	position q = NULL;
	while (p->next != 0) {
		q = p->next;
		p->next = q->next;
		free(q);
	}
	return 0;
}
