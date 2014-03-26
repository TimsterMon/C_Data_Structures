/*
 * Employee.c
 *  Lab7
 *  cs411
 *  Created on: Feb 28, 2014
 *      Author: Cale Bickler
 */
#include "Employee.h"

employee* create(int IDIn, char* nameIn, double salaryIn){
	employee *e= (employee*) malloc(sizeof(employee));
	e->IDnumber = IDIn;
	int i;
	for (i = 0; i < MAX_NAME; i++) {
		e->name[i] = *nameIn;
		nameIn++;
	}
	e->salary = salaryIn;
	return e;
}
void destroy(employee *e){
	free(e);
	e = NULL;
}
void display(employee* e){
	printf("Employee #%-3i Name: %-20s Salary: $%.2f\n", e->IDnumber, e->name, e->salary);
	fflush(stdout);
}
