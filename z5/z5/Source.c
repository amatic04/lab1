#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 1024
#define ALLOCATION_ERROR -1
#define FILE_NOT_FOUND_ERROR -2
#define ERROR -3

struct _member;
typedef struct _member* position;
typedef struct _member {
	float number;
	position next;
}member;

float fileinput();
int printPostfix();
int pop();
int push();
int Delete();
position top = NULL;

int main() {
	float result;
	char filename[MAX_LINE];
	printf("Enter name of the file you want to read from: ");
	scanf("%s", filename);

	printPostfix(filename);

	result = fileinput(filename);
	if (result != ERROR) {
		printf("\nResult is %.2f.", result);
	}
	else {
		printf("Incorrectly set equation in the file!");
	}
	return 0;
}

float fileinput(char filename[MAX_LINE]) {
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File not found!\n");
		return FILE_NOT_FOUND_ERROR;
	}
	int n;
	int l;
	float temp1 = 0;
	float temp2 = 0;
	float* tmp1 = &temp1;
	float* tmp2 = &temp2;
	char ctemp[MAX_LINE];
	char oper[MAX_LINE];
	float res;
	float* tempres;
	tempres = &res;
	char* p = &ctemp;
	char line[MAX_LINE];
	fgets(ctemp, MAX_LINE, fp);
	while (strlen(p) > 0) {
		l = sscanf(p, "%f %n", &temp1, &n);
		if (l == 1) {
			push(tmp1);
		}
		else {
			sscanf(line, "%s %n", &oper, &n);
			if (!strcmp(oper, "+")) {
				pop(tmp1);
				pop(tmp2);
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				res = temp2 + temp1;
				push(tempres);
			}
			else if (!strcmp(oper, "-")) {
				pop(tmp1);
				pop(tmp2);
				res = temp2 - temp1;
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				push(tempres);
			}
			else if (!strcmp(oper, "*")) {
				pop(tmp1);
				pop(tmp2);
				res = temp2 * temp1;
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				push(tempres);
			}
			else if (!strcmp(oper, "/")) {
				pop(tmp1);
				if (temp1 == 0) {
					printf("Division with 0 is not possible!\n");
					return ERROR;
				}
				pop(tmp2);
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				res = temp2 / temp1;
				push(tempres);
			}
			else {
				printf("Unknown operation in file!\n");
				return ERROR;
			}

		}
		p += n;
		strcpy(line, p);
	}
	pop(tmp1);

	return *tmp1;
}

int printPostfix(char filename[MAX_LINE])
{
	printf("\nPostfix from file: ");

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	char line[MAX_LINE];

	while (!feof(fp))
	{
		fgets(line, MAX_LINE, fp);
		puts(line);
	}

	fclose(fp);
}

int push(float* temp) {
	position q;
	q = (position)malloc(sizeof(member));
	if (q == NULL) {
		printf("Can't allocate memory!\n");
		return ALLOCATION_ERROR;
	}
	q->number = *temp;
	q->next = top;
	top = q;
	return 0;
}

int pop(float* temp) {
	position q;
	if (top == NULL) {
		printf("List is empty!\n");
		*temp = ERROR;
		return ERROR;
	}
	*temp = top->number;
	q = top;
	top = top->next;
	free(q);
	return 0;
}

int Delete() {
	position head = top->next;
	position temp;

	while (head != NULL) {
		temp = head->next;
		free(head);
		head = temp;
	}
	return 0;
}
