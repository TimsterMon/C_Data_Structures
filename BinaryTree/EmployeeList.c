/*
 * EmployeeList.c
 *  Lab5
 *  cs411
 *  Created on: Feb 13, 2014
 *      Author: Cale Bickler
 */

#include "Employee.h"

int getID(employeeList* eL);
void freeID(employeeList* eL, int ID);
employee* find(employeeList* eL, int id);
void traverse(employeeList* eL, employee* current, void func ( void (*f)));
void removeNode(employeeList* eL, employee* node, employee* nodeParent);

void add(employeeList* eL, char* nameIn, double salary) {
	if (eL->count == MAX_EMPS) {
		puts("Maximum number of employees reached");
		fflush(stdout);
	}
	else {
		int ID = getID(eL);
		employee* e = create(ID, nameIn, salary);

		if (eL->count < 1) {
			eL->root = e;
		}
		else {
			employee* current = eL->root;
			while(1) {
				//left
				if (e->IDnumber < current->IDnumber) {
					if (current->left != NULL) {
						current = current->left;
					}
					else {
						current->left = e;
						break;
					}
				}
				//right
				if (e->IDnumber > current->IDnumber) {
					if (current->right != NULL) {
						current = current->right;
					}
					else {
						current->right = e;
						break;
					}
				}
			}
		}
		eL->count = (eL->count + 1);
	}
}


employee* find(employeeList* eL, int id){
	employee* current = eL->root;
	while (1) {
		if (current == NULL) {
			break;
		}
		if(current->IDnumber == id) {
			return current;
		}
		if (id < current->IDnumber) {
			eL->previous = current;
			current = current->left;
		}
		else if (id > current->IDnumber) {
			eL->previous = current;
			current = current->right;
		}
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
	traverse(eL, eL->root, display);
}

void traverse(employeeList* eL, employee* current, void func ( void (*f))) {
	if (current == NULL) {
		return;
	}
	traverse(eL, current->left, func);
	func(current);
	traverse(eL, current->right, func);
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
	eL->root = NULL;
	return eL;
}

int getID(employeeList* eL) {
	int randEle = rand() % eL->freeCount;
	int id = eL->free[randEle];
	eL->freeCount--;
	eL->free[randEle] = eL->free[eL->freeCount];
	return id;
}

int deleteEmp(employeeList* eL, int ID){
	eL->previous = NULL;
	employee* current = find(eL, ID);
	if (current == NULL) {
		return 0;
	}
	else {//no children
		if (current->left == NULL && current->right == NULL) {
			removeNode(eL, current, eL->previous);
		}
		else { //one child
			if (current->left == NULL || current->right == NULL) {
				removeNode(eL, current, eL->previous);
			}
			else { //two children
				//find predecessor
				employee* pred = current->left;
				employee* parentPred = current;
				while (1) {
					if (pred->right == NULL) {
						break;
					}
					parentPred = pred;
					pred = pred->right;
				}
				int id = pred->IDnumber;
				removeNode(eL, pred, parentPred);
				current->IDnumber = id;
			}
		}
	}
	return 1;
}
void removeNode(employeeList* eL, employee* node, employee* nodeParent) {
	if (node->left == NULL && node->right == NULL) {//no children
		if (nodeParent == NULL) {
			eL->root = NULL;
		}
		else {
			if (node->IDnumber < nodeParent->IDnumber) {
				nodeParent->left = NULL;
			}
			else {
				nodeParent->right = NULL;
			}
		}
		freeID(eL, node->IDnumber);
		destroy(node);
	}
	else {
		if (node->left == NULL || node->right == NULL) {//one child
			if (nodeParent == NULL) {
				if(node->right == NULL) {
					eL->root = node->left;
				}
				else {
					eL->root = node->right;
				}
			}
			else {
				if (node->IDnumber < nodeParent->IDnumber) {
					if(node->right == NULL) {
						nodeParent->left = node->left;
					}
					else {
						nodeParent->left = node->right;
					}
				}
				else {
					if(node->right == NULL) {
						nodeParent->right = node->left;
					}
					else {
						nodeParent->right = node->right;
					}
				}
			}
			freeID(eL, node->IDnumber);
			destroy(node);
		}
	}
	eL->count--;
}

void deleteAllEmp(employeeList* eL){
	int i;
	for (i = 1; i < 101; i++) {
		deleteEmp(eL, i);
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
