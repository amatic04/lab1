/* 2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable. */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define ALLOCATION_ERROR (-1)

struct _person;
typedef struct _person* Position;
typedef struct _person
{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	Position next;
} person;

Position createPerson();
int addFront(Position p);
Position findLast();
int addBehind(Position p);
int Print(Position p);
int searchPerSurname(Position p);
Position Delete(Position p);
int menu();
int printPerson();

int main()
{
	person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

	menu(&Head);

	return EXIT_SUCCESS;
}

Position createPerson() // Creates new element (person) that can be added to list
{
	Position newPerson = NULL;
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int birthYear = 0;

	newPerson = (Position)malloc(sizeof(person));
	if (!newPerson)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	printf("Enter name: ");
	scanf(" %s", newPerson->name);
	printf("\nEnter surname: ");
	scanf(" %s", newPerson->surname);
	printf("\nEnter birth year: ");
	scanf(" %d", &newPerson->birthYear);
	printf("\n");

	return newPerson;
}

int addFront(Position head) // Add element at the front of the list
{
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

Position findLast(Position head) // Finds last element of the list
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	return head;
}

int addBehind(Position head) // Add element at the end of the list
{
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		head = findLast(head);
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int Print(Position head) // Prints list
{
	while (head != NULL)
	{
		printf(" %s %s %d \n\n", head->name, head->surname, head->birthYear);
		head = head->next;
	}

	return 0;
}

int searchPerSurname(Position p) // Findes person based on surname
{
	char sur[MAX_LENGTH];

	printf("Enter surname of person you want to find: ");
	scanf("%s", &sur);

	while (p != NULL && strcmp(sur, p->surname) != 0)
	{
		p = p->next;
	}
	if (p == NULL)
		printf("\nPerson wtih surname you entered does not exist!\n\n");
	else
		printPerson(p);

	return EXIT_SUCCESS;
}

Position Delete(Position p)
{
	Position prev = NULL;
	char sur[MAX_LENGTH];

	printf("Enter the surname of the person you want to delete: ");
	scanf("%s", sur);
	printf("\n");

	Position current = p;

	while (current != NULL && strcmp(sur, current->surname) != 0)
	{
		prev = current;
		current = current->next;
	}

	if (current != NULL && strcmp(sur, current->surname) == 0)
	{
		if (prev != NULL)
		{
			prev->next = current->next;
			free(current);
			printf("Deleted!\n\n");
		}
		else
		{
			// If the first element is the one to be deleted, update the Head pointer
			p = p->next;
			free(current);
			printf("Deleted!\n\n");
		}
	}
	else
	{
		printf("Person with the entered surname does not exist!\n\n");
	}

	return p;
}

int menu(Position Head)
{
	char choice;

	while (1) {
		printf("Enter: F -> Add in front, P -> Print, B -> Add behind, S -> Search per surname, D -> Delete, X -> Exit\n\n");
		printf("Unos: ");
		scanf(" %c", &choice);
		printf("\n");

		if (choice == 'F' || choice == 'f')
			addFront(Head);
		else if (choice == 'B' || choice == 'b')
			addBehind(Head);
		else if (choice == 'P' || choice == 'p')
			Print(Head->next);
		else if (choice == 'S' || choice == 's')
			searchPerSurname(Head->next);
		else if (choice == 'D' || choice == 'd')
		{
			Head->next = Delete(Head->next);
		}
		else if (choice == 'X' || choice == 'x')
			break;
		else
			printf("Entry error, please try again!\n\n");
	}

	return EXIT_SUCCESS;
}

int printPerson(Position person)
{
	printf("\nName: %s, surname: %s, birth year: %d, adress: %p\n\n",
		person->name, person->surname, person->birthYear, person);

	return EXIT_SUCCESS;
}
