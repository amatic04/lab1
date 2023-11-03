/* 3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke. */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (50)
#define ALLOCATION_ERROR (-1)
#define FILE_OPEN_ERROR (-1)

struct _person;
typedef struct _person* position;
typedef struct _person
{
	char name[MAX_LENGTH];
	char surname[MAX_LENGTH];
	int birthYear;
	position next;
} person;

position createPerson();
int addFront();
position findLast();
int addEnd();
int Print();
int searchPerSurname();
position Delete();
int addBehind();
int addInFront();
int printPerson();
int write();
int read();
int deleteAll();
int menu();


int main()
{
	person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

	menu(&Head);
	
	deleteAll(&Head);
	return EXIT_SUCCESS;
}

position createPerson() // Creates new element (person) that can be added to list
{
	position newPerson = NULL;
	char name[MAX_LENGTH] = { 0 };
	char surname[MAX_LENGTH] = { 0 };
	int birthYear = 0;

	newPerson = (position)malloc(sizeof(person));
	if (newPerson == NULL)
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

int addFront(position head) // Add element at the front of the list
{
	position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

position findLast(position head) // Finds last element of the list
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	return head;
}

int addEnd(position head) // Add element at the end of the list
{
	position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		head = findLast(head);
		newPerson->next = head->next;
		head->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int Print(position head) // Prints list
{
	while (head != NULL)
	{
		printf(" %s %s %d \n\n", head->name, head->surname, head->birthYear);
		head = head->next;
	}

	return 0;
}

int searchPerSurname(position p) // Findes person based on surname
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

position Delete(position p)
{
	position prev = NULL;
	char sur[MAX_LENGTH];

	printf("Enter the surname of the person you want to delete: ");
	scanf("%s", sur);
	printf("\n");

	position current = p;

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

int addBehind(position p) // Add element behind certain element
{
	char sur[MAX_LENGTH];

	printf("Enter surname of person you want to add behind: ");
	scanf("%s", &sur);
	printf("\n");

	while (p != NULL && strcmp(sur, p->surname) != 0)
	{
		p = p->next;
	}
	if (p == NULL)
		printf("\nPerson wtih surname you entered does not exist!\n\n");
	
	position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		newPerson->next = p->next;
		p->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int addInFront(position p) // Add element in front of certain element
{
	char sur[MAX_LENGTH];

	printf("Enter surname of person you want to add in front of: ");
	scanf("%s", &sur);
	printf("\n");

	position prev = NULL;

	while (p != NULL && strcmp(sur, p->surname) != 0)
	{
		prev = p;
		p = p->next;
	}
	if (p == NULL)
		printf("\nPerson wtih surname you entered does not exist!\n\n");

	position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson)
	{
		newPerson->next = prev->next;
		prev->next = newPerson;
	}

	return EXIT_SUCCESS;
}

int write(position p)
{
	FILE* fp = NULL;
	fp = fopen("persons.txt", "w");

	if (fp == NULL)
	{
		printf("File did not open error!\n");
		return FILE_OPEN_ERROR;
	}

	while (p != NULL)
	{
		fprintf(fp, "%s\t %s\t %d\t\n", p->name, p->surname, p->birthYear);
		p = p->next;
	}

	fclose(fp);

	return 0;
}

int read()
{
	char file[MAX_LENGTH];
	int b = 0;
	person Head;
	Head.next = NULL;
	position p = &Head;
	position q = NULL;

	printf("Enter the name of the file you want to read your list from: ");
	scanf(" %s", &file);
	FILE* fp = NULL;
	fp = fopen(file, "r");
	if (fp == NULL)
	{
		printf("File did not open error!\n");
		return FILE_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		if (fgetc(fp) == '\n')
			b++;
	}
	rewind(fp);
	if (b != 0)
	{
		for (int i = 0; i < b; i++) {
			q = (position)malloc(sizeof(person));
			if (q == NULL)
			{
				printf("Can't allocate memory!\n");
				return ALLOCATION_ERROR;
			}
			fscanf(fp, "%s %s %d", q->name, q->surname, &q->birthYear);
			q->next = p->next;
			p->next = q;
			p = p->next;
		}
	}
	fclose(fp);
	Print(Head.next);
	return 0;
}

int printPerson(position person)
{
	printf("\nName: %s, surname: %s, birth year: %d, adress: %p\n\n",
		person->name, person->surname, person->birthYear, person);

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

int menu(position Head)
{
	char choice;

	while (1) {
		printf("Enter:\n F -> Add in front,\n P -> Print,\n E -> Add at the end,\n S -> Search per surname,\n D -> Delete,\n B -> Add behind,\n I -> Add in front of,\n W -> write in file,\n R -> read from file,\n X -> Exit\n\n");
		printf("Unos: ");
		scanf(" %c", &choice);
		printf("\n");

		if (choice == 'F' || choice == 'f')
			addFront(Head);
		else if (choice == 'E' || choice == 'e')
			addEnd(Head);
		else if (choice == 'P' || choice == 'p')
			Print(Head->next);
		else if (choice == 'S' || choice == 's')
			searchPerSurname(Head->next);
		else if (choice == 'D' || choice == 'd')
		{
			Head->next = Delete(Head->next);
		}
		else if (choice == 'B' || choice == 'b')
			addBehind(Head);
		else if (choice == 'I' || choice == 'i')
			addInFront(Head);
		else if (choice == 'W' || choice == 'w')
			write(Head->next);
		else if (choice == 'R' || choice == 'r')
			read();
		else if (choice == 'X' || choice == 'x')
			break;
		else
			printf("Entry error, please try again!\n\n");
	}

	return EXIT_SUCCESS;
}
