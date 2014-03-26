/*
 * Employee.h
 *  Lab7
 *  cs411
 *  Created on: Feb 28, 2014
 *      Author: Cale Bickler
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#define MAX_NAME 20
#define MAX_EMPS 100

typedef struct{
	int IDnumber;
	char name[MAX_NAME];
	double salary;
} employee;

typedef struct node {
	int count;
	employee* emps[3];
	struct node* links[4];
}node;

typedef struct {
	int count;
	node* root;
	node* previous;
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
