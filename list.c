#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct list *list_init(void *val) {
	struct list *out = malloc(sizeof(struct list));
	if (!out) {
		fputs("malloc failed to allocate memory.", stderr);
	}

	out->val = val;
	out->next = NULL;
	out->prev = NULL;

	return out;
}

void list_free(struct list *l) {
	free(l);
}

void list_free_all(struct list *l) {
	struct list *head = l;
	struct list *next = NULL;

	while (head != NULL) {
		next = head->next;
		list_free(head);
		head = next;
	}
}

void list_append(struct list *l, void *val) {
	struct list *head = l;

	while (head->next != NULL) {
		head = head->next;
	}

	head->next = list_init(val);
	head->next->prev = head->next;
}

struct list *list_prepend(struct list *l, void *val) {
	struct list *out = list_init(val);

	out->next = l;
	l->prev = out;
	l = l->prev;

	return l;
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

	list_free_all(a_list);
	list_free_all(b_list);
}
*/
