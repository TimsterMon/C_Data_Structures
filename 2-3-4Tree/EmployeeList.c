/*
 * EmployeeList.c
 *  Lab7
 *  cs411
 *  Created on: Feb 28, 2014
 *      Author: Cale Bickler
 */

#include "Employee.h"

int getID(employeeList* eL);
employee* find(employeeList* eL, int id);
void traverse(employeeList* eL, node* current, void func ( void (*f)));
void insert(employeeList* eL, node* n, employee* e);
node* split(employeeList* eL, node* n);
node* newNode();

void add(employeeList* eL, char* nameIn, double salary) {
	if (eL->count == MAX_EMPS) {
		puts("Maximum number of employees reached");
		fflush(stdout);
	}
	else {
		int ID = getID(eL);
		employee* e = create(ID, nameIn, salary);

		if (eL->count < 1) {
			node* n = newNode();
			n->emps[0] = e;
			n->count++;
			eL->root = n;
		}
		else {
			eL->previous = NULL;
			insert(eL, eL->root, e);
		}
		eL->count = (eL->count + 1);
	}
}

void insert(employeeList* eL, node* n, employee* e) { //walks down tree and finds where to insert
	if(n->count == 3) {
		node* top = split(eL, n);
		n = top;
	}

	if (n->links[0] == NULL) {
		if (n->emps[0]->IDnumber > e->IDnumber) {
			n->emps[2] = n->emps[1];
			n->emps[1] = n->emps[0];
			n->emps[0] = e;
			n->count++;
			return;
		}

		if (n->emps[1] == NULL) {
			n->emps[2] = n->emps[1];
			n->emps[1] = e;
			n->count++;
			return;
		}

		if (n->emps[0]->IDnumber < e->IDnumber && n->emps[1]->IDnumber > e->IDnumber) {
			n->emps[2] = n->emps[1];
			n->emps[1] = e;
			n->count++;
			return;
		}

		if (n->emps[1]->IDnumber < e->IDnumber) {
			n->emps[2] = e;
			n->count++;
			return;
		}
	}
	eL->previous = n;

	if (n->emps[0]->IDnumber > e->IDnumber) {
		insert(eL, n->links[0], e);
		return;
	}

	if (n->emps[1] == NULL) {//
		insert(eL, n->links[1], e);
		return;
	}

	if (n->emps[0]->IDnumber < e->IDnumber && n->emps[1]->IDnumber > e->IDnumber) {
		insert(eL, n->links[1], e);
		return;
	}

	if (n->emps[2] == NULL) {//
		insert(eL, n->links[2], e);
		return;
	}

	if (n->emps[1]->IDnumber < e->IDnumber && n->emps[2]->IDnumber > e->IDnumber) {
		insert(eL, n->links[2], e);
		return;
	}

	if (n->emps[2]->IDnumber < e->IDnumber) {
		insert(eL, n->links[3], e);
		return;
	}


}

node* split(employeeList* eL, node* n) {
	node* new = newNode();
	new->emps[0] = n->emps[2];
	n->emps[2] = NULL;
	new->count++;
	n->count--;
	if (eL->previous != NULL) { //insert middle value into previous
		if (eL->previous->emps[0]->IDnumber > n->emps[1]->IDnumber) { //insert at 0
			eL->previous->emps[2] = eL->previous->emps[1];
			eL->previous->emps[1] = eL->previous->emps[0];
			eL->previous->emps[0] = n->emps[1];
			n->emps[1] = NULL;
			eL->previous->links[3] = eL->previous->links[2];
			eL->previous->links[2] = eL->previous->links[1];
			eL->previous->links[1] = new;
			eL->previous->count++;
			n->count--;
			new->links[0] = n->links[2];
			new->links[1] = n->links[3];
		}
		else {
			if (eL->previous->emps[1] == NULL) { //insert at 1
				eL->previous->emps[2] = eL->previous->emps[1];
				eL->previous->emps[1] = n->emps[1];
				n->emps[1] = NULL;
				eL->previous->links[3] = eL->previous->links[2];
				eL->previous->links[2] = new;
				eL->previous->count++;
				n->count--;
				new->links[0] = n->links[2];
				n->links[2] = NULL;
				new->links[1] = n->links[3];
				n->links[3] = NULL;
			} else {
				if (eL->previous->emps[0]->IDnumber < n->emps[1]->IDnumber && eL->previous->emps[1]->IDnumber > n->emps[1]->IDnumber) { //insert at 1
					eL->previous->emps[2] = eL->previous->emps[1];
					eL->previous->emps[1] = n->emps[1];
					n->emps[1] = NULL;
					eL->previous->links[3] = eL->previous->links[2];
					eL->previous->links[2] = new;
					eL->previous->count++;
					n->count--;
					new->links[0] = n->links[2];
					n->links[2] = NULL;
					new->links[1] = n->links[3];
					n->links[3] = NULL;
				}
				else {
					if (eL->previous->emps[1]->IDnumber < n->emps[1]->IDnumber) { //insert at 2
						eL->previous->emps[2] = n->emps[1];
						n->emps[1] = NULL;
						eL->previous->links[3] = new;
						eL->previous->count++;
						n->count--;
						new->links[0] = n->links[2];
						n->links[2] = NULL;
						new->links[1] = n->links[3];
						n->links[3] = NULL;
					}
				}
			}
		}
		return eL->previous;
	}
	else {
		node *root= newNode();
		root->emps[0] = n->emps[1];
		n->emps[1] = NULL;
		root->count++;
		n->count--;
		root->links[0] = n;
		root->links[1] = new;
		new->links[0] = n->links[2];
		n->links[2] = NULL;
		new->links[1] = n->links[3];
		n->links[3] = NULL;
		eL->root = root;
		return eL->root;
	}
}

node* newNode() {
	node *n= (node*) malloc(sizeof(node));
	n->count = 0;
	n->links[0] = NULL;
	n->links[1] = NULL;
	n->links[2] = NULL;
	n->links[3] = NULL;
	n->emps[0] = NULL;
	n->emps[1] = NULL;
	n->emps[2] = NULL;
	return n;
}

employee* find(employeeList* eL, int id){
	node* current = eL->root;
	while (1) {
		if (current == NULL) { //not found
			break;
		}

		if(current->emps[0]->IDnumber == id) { // id is in 0
			return current->emps[0];
		}

		if (id < current->emps[0]->IDnumber) { //go down 0
			current = current->links[0];
		}
		else {
			if (current->emps[1] == NULL) { // go down 1
				current = current->links[1];
			}
			else {
				if (id < current->emps[1]->IDnumber) { // go down 1
					current = current->links[1];
				}
				else {
					if (id == current->emps[1]->IDnumber) { //it is in 1
						return current->emps[1];
					}
					else {
						if (current->emps[2] == NULL) { // go down 2
							current = current->links[2];
						}
						else {
							if (id < current->emps[2]->IDnumber) { // go down 2
								current = current->links[2];
							}
							else {
								if (id == current->emps[2]->IDnumber) { //it is in 2
									return current->emps[2];
								}
								else {
									current = current->links[3]; // do down 3
								}
							}
						}
					}
				}
			}
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

void traverse(employeeList* eL, node* current, void func ( void (*f))) {
	if (current == NULL) {
		return;
	}
	traverse(eL, current->links[0], func);
	func(current->emps[0]);
	traverse(eL, current->links[1], func);

	if (current->count > 1) {
		func(current->emps[1]);
		traverse(eL, current->links[2], func);
	}

	if (current->count > 2) {
		func(current->emps[2]);
		traverse(eL, current->links[3], func);
	}
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
	eL->previous = NULL;
	return eL;
}

int getID(employeeList* eL) {
	int randEle = rand() % eL->freeCount;
	int id = eL->free[randEle];
	eL->freeCount--;
	eL->free[randEle] = eL->free[eL->freeCount];
	return id;
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

