#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Daniel Huynh, Jesse Chaney CS201 Jan 30 2023
// This program stores and displays strings in a sorted doubly linked list.
#define STRLEN 200

typedef struct node_s
{
	char *str;
	struct node_s *prev;
	struct node_s *next;
}node_t;

typedef struct llist_s
{
	node_t *first;
	node_t *last;
}llist_t;



char start;
char button;
char word[STRLEN];

void menu();
int add_string(char * word, llist_t * list);
void print_list(llist_t * list);



int main(void)
{
	int count=1;
	llist_t mylist = {NULL, NULL};
	fgets(word, STRLEN, stdin);
	add_string(word, &mylist);
	++count;

	fgets(word, STRLEN, stdin);
	add_string(word, &mylist);
	++count;

	fgets(word, STRLEN, stdin);
	add_string(word, &mylist);
	++count;

	print_list(&mylist);

	return 0;
}	


int add_string(char* word, llist_t * list)
{

	node_t * node = (node_t *)malloc(sizeof(node_t));

	if(list->first == NULL)
	{
		list->first = list->last = node;
		list->first->str = strdup(word);
		return 1;
	}
	else if(list->first != NULL && list->first->next == NULL)//one item list
	{
		node_t * current = list->first;
		if(strcmp(word, current->str) >0)
		{
			current = current->next = node;		
			current->str = strdup(word);
			current->prev = list->first;
			current->next = NULL;
			list->last = current;
		}	
		if(strcmp(word, current->str) <0)
		{
			node_t * temp = current->prev = node;
			temp->next = current;
			current->next = NULL;
			temp->str = strdup(word);
			list->first = temp;
			list->last = current;

		}	
		return 1;
	}
	else //multiple item list
	{
		node_t * current = list->first;
		node_t * previous = current;
		while(current->next != NULL && strcmp(word, current->str) >0)//our value is largest in list
		{
			previous = current;
			current= current->next;
		}
		if(current->next == NULL)// our value is at the end of our listt
		{
			if(strcmp(word, current->str) <0)
			{
				node_t * temp = current->prev = node;
				previous->next = temp;
				temp->next =current;
				temp->prev = previous;
				temp->str = strdup(word);
			}

			/*
			previous = current;
			current = current->next = node;
			current->str = strdup(word);
			current->next= NULL;
			current->prev = previous;
			list->last= current;
			*/
		}
		else 
		{
			node_t * hold = current->next;
			hold->prev = current;
			previous->next = current;
		}
		return 1;
	}
	

	return 0;
}

void print_list(llist_t * list)
{
	node_t * current = list->first;
	printf("--- forward ---\n");
	while(current->next != NULL)
	{
		printf("%s", current->str);
		current= current->next;
	}
	printf("%s\n--- reverse ---\n", current->str);
	node_t * current2 = list->last;
	while(current2->prev != NULL)
	{
		printf("%s", current2->str);
		current2= current2->prev;
	}
	printf("%s", current2->str);
}

void free_list(llist_t * list)
{
	node_t * node = list->first;
	while(node != NULL)
	{
		node_t * temp = node->next;
		free(node->str);
		free(node);
		node = temp;
	}
	list->first = list->last = NULL;
}


