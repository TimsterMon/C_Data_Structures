/*
 * Employee.h
 *  Lab3
 *  cs411
 *  Created on: Jan 30, 2014
 *      Author: Cale Bickler
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#define MAX_NAME 20
#define MAX_EMPS 100

typedef struct employee{
	int IDnumber;
	char name[MAX_NAME];
	double salary;
	struct employee* next;
} employee;

typedef struct {
	int count;
	employee* top;
	employee* previous;
	int freeCount;
	int free[MAX_EMPS];
}employeeList;

//employee
employee* create(int IDIn, char* nameIn, double salaryIn);
void destroy(employee *e);
void display(employee* e);

//employeeList
void add(employeeList* eL, char* nameIn, double salary);
void displaySingle(employeeList* eL, int ID);
void displayAll(employeeList* eL);
employeeList* init();
void deleteEmp(employeeList* eL, int ID);
void deleteAllEmp(employeeList* eL);
void initialize(employeeList* eL, int num);
void sort(employeeList* eL);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#endif /* EMPLOYEE_H_ */

#ifndef NULL
#define NULL   ((void *) 0)
#endif
