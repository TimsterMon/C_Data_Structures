/*
 * EmployeeList.c
 *  Lab3
 *  cs411
 *  Created on: Jan 30, 2014
 *      Author: Cale Bickler
 */

#include "Employee.h"

int getID(employeeList* eL);
void freeID(employeeList* eL, int ID);
employee* find(employeeList* eL, int id);
void insert(employeeList* eL, employee* e);

void add(employeeList* eL, char* nameIn, double salary) {
	if (eL->count == MAX_EMPS) {
		puts("Maximum number of employees reached");
		fflush(stdout);
	}
	else {
		int ID = getID(eL);
		employee* e = create(ID, nameIn, salary);

		//go to end then set next to new employee
		if (eL->count < 1) {
			eL->top = e;
		}
		else {
			employee* current = eL->top;
			int i;
			for (i = 0; i < (eL->count - 1); i++) {
				current = current->next;
			}
			current->next = e;
		}
		eL->count = (eL->count + 1);
	}
}

employee* find(employeeList* eL, int id){
	employee* current = eL->top;
	int i;
	for (i = 0; i < eL->count; i++) {
		if(current->IDnumber == id) {
			return current;
		}
		eL->previous = current;
		current = current->next;
	}
	return NULL;
}

void displaySingle(employeeList* eL, int ID){
	employee* current = find(eL, ID);
	if (current == NULL) {

		puts("ERROR: ID does not exist");
		fflush(stdout);
	}
	else {
		display(current);
	}
}

void displayAll(employeeList* eL){
	int i;
	if (eL->count > 0) {
		employee* current = eL->top;
		for(i = 0; i < eL->count; i++) {
			display(current);
			current = current->next;
		}
	}
}

void sort(employeeList* eL) {
	employee* oldTop = eL->top;
	employee* oldList;
	eL->top = NULL;
	int oldCount = eL->count;
	eL->count = 0;
	int i;
	while(oldCount > 0){
		oldList = oldTop;
		for (i = 0; i < oldCount; i++){
			if (i == (oldCount - 1)) {
				insert(eL, oldList);
			}
			oldList = oldList->next;
		}
		oldCount--;
	}

}

void insert(employeeList* eL, employee* e) {
	if (eL->count > 0) {
		employee* current = eL->top;
		if (e->IDnumber < eL->top->IDnumber) {
			eL->top = e;
			e->next = current;
		}
		else{
			int i = 0;
			for (i = 0; i < (eL->count - 1); i++){
				if (e->IDnumber < current->next->IDnumber) {
					eL->previous = current;
					current = current->next;
					eL->previous->next = e;
					e->next = current;
					eL->count++;
					return;
				}
				eL->previous = current;
				current = current->next;
			}
			current->next = e;
		}
	}
	else {
		eL->top = e;
	}
	eL->count++;
}

void freeID(employeeList* eL, int ID){
	eL->free[eL->freeCount] = ID;
	eL->freeCount++;
}

employeeList* init() {
	employeeList *eL= (employeeList*) malloc(sizeof(employeeList));
	srand((int)time(NULL));
	int i;
	for(i = 0; i < 100; i++) {
		eL->free[i] = (i + 1);
	}
	eL->count = 0;
	eL->freeCount = 100;
	return eL;
}

int getID(employeeList* eL) {
	int randEle = rand() % eL->freeCount;
	int id = eL->free[randEle];
	eL->freeCount--;
	eL->free[randEle] = eL->free[eL->freeCount];
	return id;
}

void deleteEmp(employeeList* eL, int ID){
	employee* current = find(eL, ID);
	if (current == NULL) {
		puts("ERROR: ID does not exist");
		fflush(stdout);
	}
	else {
		employee* next = current->next;
		freeID(eL, current->IDnumber);
		destroy(current);
		if(eL->top == current) {
			eL->top = next;
		}
		else {
			eL->previous->next = next;
		}
		eL->count--;
	}
}

void deleteAllEmp(employeeList* eL){
	while (eL->count > 0) {
		employee* current = eL->top;
		int i;
		for (i = 0; i < (eL->count - 1); i++) {
			current = current->next;
		}
		freeID(eL, current->IDnumber);
		destroy(current);
		eL->count--;
	}
}

void initialize(employeeList* eL, int num) {
	char* names[10] = {"Bob Jones", "Mary Fitzpatrick", "Steve Young", "Greg Gutfield", "John Boehner", "James Dean", "Seth Rogen", "Lana Baldwin", "Taylor Swift", "Ellie Stein"};
	double salary;
	int i;
	for (i = 0; i < num; i++) {
		salary = ((double)((rand() << 15) | rand()) / 10000);
		add(eL, names[(rand() % 10)], salary);
	}
}
