/*
 * linkedlist.c
 *
 *  Created on: 1 nov 2014
 *      Author: krantz
 */

#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

struct node {
	int data;
	struct node *next;
}*head, *var;

/*Adds a new node as head, with specified value*/
void add_beginning(int val) {

	var = (struct node *) malloc(sizeof(struct node));
	var->data = val;
	if (head == NULL) {
		head = var;
		head->next = NULL;
	} else {
		var->next = head;
		head = var;
	}

	// printf("Data added at beginning %d\n", head -> data);
}
/*Adds a new node with specified value at the end of the list*/
void add_end(int val) {
	struct node *temp;
	temp = head;
	var = (struct node *) malloc(sizeof(struct node));
	var->data = val;

	if (head == NULL) {
		head = var;
		head->next = NULL;
	} else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		var->next = NULL;
		temp->next = var;
	}
	 //printf("new node added at end %d\n", var -> data);

}
/* Removes the head element*/
int remove_first() {
	if (head != NULL) {
		struct node *temp;
		temp = head;
		int tempVal = head->data;
		head = temp->next;
		//printf("head removed %d\n", temp -> data);
		free(temp);
		return tempVal;
	}
	//  printf("List is empty, returns%d\n", -1);
	return -1;
}
/*Prints every value in the linked list*/
void print() {
	if (is_empty()) {
		puts("List Empty");
	} else {
		struct node *temp;
		temp = head;
		while (temp->next != NULL) {
			printf("%d\n", temp->data);
			temp = temp->next;
		}
		printf("%d\n", temp->data);
	}
}

/* Returns 1 if the linked list is empty, 0 of not empty*/
int is_empty() {
	return head != NULL ? 0 : 1;
}
