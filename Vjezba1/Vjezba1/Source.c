/* 1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100 */



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX_NAME (150)
#define MAX_BOD (50)

typedef struct _student
{
	char name[MAX_NAME];
	char surname[MAX_NAME];
	int points;
	int relative_points;
}student;

int countStudentsFromFile(char* filename);
int studentData(char* filename, student*);

int main(void)
{
	char filename[MAX_FILE_NAME] = { 0 };
	student* person = NULL;
	int count = 0;

	printf("Insert filename -> ");
	scanf(" %s", filename);
	
	count = countStudentsFromFile(filename);


	if (count > 0) {
		printf("Broj studenata u datoteci %s je %d\n", filename, count);
		person = malloc(count * sizeof(student));

		if (!person) {
			perror("Memory allocation failed for students!\n");
			return EXIT_FAILURE;
		}

		studentData(filename, person, count);
	}

	return 0;
}

int countStudentsFromFile(char* filename)
{
	FILE* fp = NULL;
	int count = 0;
	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	int points = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Dear customer, the file %s didn't open!\r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{ // while not found end of file (EOF)
		int result = fscanf(fp, " %s %s %d", name, surname, &points);
		if (result == 3) {
			count++;
		}
	}

	fclose(fp);
	return count;
}

int studentData(char* filename, student* osoba, int count)
{
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	int i = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Dear customer, the file %s didn't open!\r\n", filename);
		return EXIT_FAILURE;
	}


	while (!feof(fp))
	{ // while not found end of file (EOF)
		fscanf(fp, " %s %s %d", osoba[i].name, osoba[i].surname, &osoba[i].points);
		osoba[i].relative_points = ((((float)osoba[i].points) / MAX_BOD) * 100);
		i++;
	}

	for (int j = 0; j < count; j++)
	{
		printf("\n%s %s %d %d\n", osoba[j].name, osoba[j].surname, osoba[j].points, osoba[j].relative_points);
	}

	fclose(fp);
}
