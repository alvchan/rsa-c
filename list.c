#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct list *list_init(void) {
	/* Initialize and allocate space for a linked list node. */
	struct list *out = malloc(sizeof(struct list));
	if (!out) {
		fputs("malloc failed to allocate memory.", stderr);
	}

	out->val = 0xff; /* placeholder to indicate uninitialized state */
	out->next = NULL;
	out->prev = NULL;

	return out;
}

void list_free(struct list *l) {
	/* Clean up and deallocate nodes from a list. */
	struct list *head = l;
	struct list *next; /* needed to avoid free into head->next */

	/* traverse list and free each node */
	while (head != NULL) {
		next = head->next;
		free(head);
		head = next;
	}
}

void list_append(struct list *l, uint8_t x) {
	/* Add an element to the end of the list. */
	struct list *head = l;

	/* walk to end of list */
	while (head->next != NULL) {
		head = head->next;
	}

	/* create and relink nodes */
	head->next = list_init();
	head->next->val = x;
	head->next->prev = head;
}

struct list *list_prepend(struct list *l, uint8_t x) {
	/* Add an element to the start of the list. */
	struct list *out = list_init();

	out->val = x;
	out->next = l;
	l->prev = out;

	/* return start ptr b/c original is unaffected */
	return l->prev;
}

struct list *list_get(const struct list *src, int index) {
	/* Traverse list and return node at index of src. */
	struct list *head = (struct list *) src;

	for (int i = 0; i <= index; i++) {
		if (!head) puts("error (list_get): index out of bounds");

		head = head->next;
	}

	return head;
}

/*
int main(void) {
	struct list *head = NULL;

	int a = 42;
	struct list *a_list = list_init(&a);
	int a_next = 51;
	list_append(a_list, &a_next);

	head = a_list;
	puts("printing a...");
	while (head != NULL) {
		printf("%d\n", *(int *) head->val);
		head = head->next;
	}

	int b = 69;
	struct list *b_list = list_init(&b);
	int b_prev = 451;
	b_list = list_prepend(b_list, &b_prev);

	head = b_list;
	printf("b @ %p (main)\n", b_list);
	puts("printing b...");
	while (head != NULL) {
		printf("%d\n", *(int *) head->val);
		head = head->next;
	}

	list_free(a_list);
	list_free(b_list);
}
*/
