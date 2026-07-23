#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s
{
	char *str;
	struct node_s *prev;
	struct node_s *next;
} node_t;

typedef struct llist_s
{
	node_t *first;
	node_t *last;
} llist_t;



void add_node(llist_t *list, node_t *node) 
{
	node_t *current = list->first;

	if (current == NULL)//empty
	{ 
		list->first = node;
		list->last = node;
	}
	else if (strcmp(node->str, current->str) < 0) // new node is higher than first node
	{
		node->next = current;
		current->prev = node;
		list->first = node;
	}
	else { 
		while (current->next != NULL && strcmp(node->str, current->next->str) > 0)
		{
			current = current->next;
		}

		node->prev = current;
		node->next = current->next;

		if (current->next == NULL) 
		{
			list->last = node;
		}
		else 
		{
			current->next->prev = node;
		}

		current->next = node;
	}
}

void print_list(llist_t *list) 
{
	node_t *current = list->first;

	printf("--- forward ---\n");

	while (current->next != NULL)
	{
		printf("%s\n", current->str);
		current = current->next;
	}
	printf("%s\n\n", current->str);
	{
		node_t *current = list->last;

		printf("--- reverse ---\n");

		while (current->prev != NULL)
		{
			printf("%s\n", current->str);
			current = current->prev;
		}
		printf("%s\n\n", current->str);
	}
}



void free_list(llist_t *list)
{
	node_t *current = list->first;
	node_t *temp;

	while (current != NULL)
	{
		temp = current->next;
		free(current->str);
		free(current);
		current = temp;
	}
}


int main(void)
{
	llist_t list = {NULL, NULL};
	char input[2000];
	while (fgets(input, 2000, stdin)!= NULL) {

		input[strcspn(input, "\n")] = 0;

		node_t *node = malloc(sizeof(node_t));
		node->str = malloc(strlen(input) + 1);
		strcpy(node->str, input);

		add_node(&list, node);
	}

	print_list(&list);
	free_list(&list);

	return 0;
}
