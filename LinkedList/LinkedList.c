/*
 * LinkedList.c
 *  Lab3
 *  cs411
 *  Created on: Jan 30, 2014
 *      Author: Cale Bickler
 */

#include "Employee.h"

void printMenu();
int getInt(char*, int, int);
double getDouble(char*, double, double);
char* getStr(char* prompt, int size);

int main (int argc, char *argv[]) {
	int selection;
	double salary;
	printMenu();
	employeeList *eL = init();
	while(1) {
		selection = getInt("Please Select: ", 1, 9);
		switch (selection) {
		case 1: //add employee
			salary = getDouble("Enter Salary: ", 0.0, 10000000.0);
			char* name = getStr("Enter Name: ", MAX_NAME);
			add(eL, name, salary);
			free(name);
			name = NULL;
			puts("Created employee");
			fflush(stdout);
			break;
		case 2: //remove  employee
			deleteEmp(eL, getInt("Enter ID: ", 1, 100));
			break;
		case 3: //display single
			displaySingle(eL, getInt("Enter ID: ", 1, 100));
			break;
		case 4: //display all employees
			displayAll(eL);
			break;
		case 5: //reset list
			deleteAllEmp(eL);
			puts("Cleared List");
			fflush(stdout);
			break;
		case 6://create initial list
			initialize(eL, 10);
			puts("Created 10 employees");
			fflush(stdout);
			break;
		case 7: //sort
				sort(eL);
				puts("Sorted");
				fflush(stdout);
				break;
		case 8: //help
			printMenu();
			break;
		case 9: //quit
			puts("Quitting");
			fflush(stdout);
			deleteAllEmp(eL);
			free(eL);
			eL = NULL;
			exit(1);
			break;
		}
	}
	return 1;
}

void printMenu() {
	puts("Employee Maintenance");
	puts("1) Add Employee");
	puts("2) Remove Employee");
	puts("3) Display Employee");
	puts("4) Display Employee List");
	puts("5) Reset List");
	puts("6) Create Initial List");
	puts("7) Sort Employee List");
	puts("8) Help");
	puts("9) Quit");
	fflush(stdout);
}

int getInt(char* prompt, int min, int max) {
	int in;
	while (1) {
		printf("%s", prompt);
		fflush(stdout);
		if (scanf("%i", &in)!=1) {
			puts("Error: Please enter numeric input");
			fflush(stdout);
			scanf("%*s");
		}
		else if (in < min || in > max) {
			printf("Error: Please enter value between %i and %i \n", min, max);
			fflush(stdout);

		}
		else {
			fflush(stdin);
			return in;
		}
	}
	fflush(stdin);
	return in;
}

double getDouble(char* prompt, double min, double max) {
	double in;
	while (1) {
		printf("%s", prompt);
		fflush(stdout);
		if (scanf("%lf", &in)!=1) {
			puts("Error: Please enter numeric input");
			fflush(stdout);
			scanf("%*s");
		}
		else if (in < min || in > max) {
			printf("Error: Please enter value between %.2f and %.2f \n", min, max);
			fflush(stdout);
		}
		else {
			fflush(stdin);
			return in;
		}
	}
	fflush(stdin);
	return in;
}
char* getStr(char* prompt, int size) {
	printf("%s", prompt);
	fflush(stdout);
	char* s = malloc(MAX_NAME + 1);
	scanf(" %20[^\n]s", s);
	fflush(stdout);
	fflush(stdin);
	return s;
}
