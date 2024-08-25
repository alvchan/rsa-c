#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

struct bigint *bigint_init(void) {
	/* Set up and allocate a bigint. */
	struct list *data = list_init();

	struct bigint *bi = malloc(sizeof(struct bigint));
	if (!bi) {
		puts("malloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}

	bi->ndigits = 0;
	bi->d = data;

	return bi;
}

void bigint_free(struct bigint *bi) {
	/* Deallocate a bigint and its components. */
	if (bi != NULL) {
		if (bi->d != NULL) list_free(bi->d);

		free(bi);
		bi = NULL;
	}
}

uint8_t bigint_getval(const struct bigint *bi, int index) {
	/* Wrapper to access list contents more tersely. */
	return list_get(bi->d, index)->val;
}

void bigint_pushc(struct bigint *bi, uint8_t x) {
	/* Append a digit/"character" to a bigint. */
	if (!bi) bi = bigint_init();

	if (bi->d->val == 0xff) bi->d->val = x; /* copy if node's val uninitialized */
	else list_append(bi->d, x);

	bi->ndigits++;
}

struct bigint *bigint_add(const struct bigint *a, const struct bigint *b) {
	/* Add values of A and B, then return resulting sum. */
	struct bigint *sum = bigint_init();

	const struct bigint *greatest = (a->ndigits >= b->ndigits) ? a : b;
	struct list *greatest_head = greatest->d;

	const struct bigint *least = (a->ndigits < b->ndigits) ? a : b;
	struct list *least_head = least->d;

	uint8_t carry = 0;
	/* add up all digits in a common range */
	while (least_head != NULL) {
		assert(greatest_head->val != 0xff && "A list node was used uninitialized.");
		assert(least_head->val != 0xff && "A list node was used uninitialized.");

		uint8_t digit_sum = greatest_head->val + least_head->val + carry;
		/* TODO: change to direct carry system */
		carry = digit_sum / 10;

		bigint_pushc(sum, digit_sum % 10);

		greatest_head = greatest_head->next;
		least_head = least_head->next;
	}

	/* default to larger bigint digits if unevenly sized */
	while (greatest_head != NULL) {
		assert(greatest_head->val != 0xff && "A list node was used uninitialized.");

		uint8_t digit_sum = greatest_head->val + carry;
		carry = digit_sum / 10;

		bigint_pushc(sum, digit_sum % 10);

		greatest_head = greatest_head->next;
	}

	/* carry extra overflow digits */
	while (carry > 0) {
		bigint_pushc(sum, carry % 10);
		carry /= 10;
	}

	return sum;
}

struct bigint *bigint_mult(const struct bigint *a, const struct bigint *b) {
	/* Multiply A by B times and return the product. */
	struct bigint *product = bigint_init();

	struct list *a_head = NULL;
	struct list *b_head = b->d;
	int traversals = 0; /* # of nodes/loops passed */

	uint8_t carry = 0;
	while (b_head != NULL) {
		assert(b_head->val != 0xff && "A list node was used uninitialized.");

		/* anything * 0 = 0, just skip */
		if (b_head->val == 0) {
			b_head = b_head->next;
			traversals++;

			continue;
		}

		struct bigint *row_product = bigint_init();

		/* TODO: create process that can precalculate instead of appending */
		/* lshift for every digit of B to simulate place value */
		for (int pad = 0; pad < traversals; pad++) {
			bigint_pushc(row_product, 0);
		}

		/* multiply A by each digit of B */
		a_head = a->d;
		while (a_head != NULL) {
			assert(a_head->val != 0xff && "A list node was used uninitialized.");

			long digit_product = a_head->val * b_head->val + carry; /* TODO: change to bigint; no guarantee on product size */
			carry = digit_product / 10;

			bigint_pushc(row_product, digit_product % 10);

			a_head = a_head->next;
		}

		/* carry extra overflow digits */
		while (carry > 0) {
			bigint_pushc(row_product, carry % 10);
			carry /= 10;
		}

		/* TODO: create bigint_add flavor that mutates instead */
		/* set product value based on current initialization state */
		if (product->d->val == 0xff) { /* assumed to be uninit'd */
			product->ndigits = row_product->ndigits;

			free(product->d);
			product->d = row_product->d;
		} else {
			struct bigint *tmp = bigint_add(product, row_product);
			bigint_free(product);
			product = tmp;
		}

		free(row_product); /* free'd normally to leave list data for product */

		b_head = b_head->next;
		traversals++;
	}

	return product;
}

void bigint_println(const struct bigint *bi) {
	/* Print all digits of a bigint. */
	/* TODO: add circular links to list */;

	struct list *head = bi->d;

	while (head != NULL) {
		printf("%d", head->val);

		head = head->next;
	}
	printf("\n");
}

