#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

#define DEBUG

struct bigint *bigint_init(unsigned int ndigits) {
	int *tmp_d;
	if (ndigits != 0) tmp_d = malloc(sizeof(int) * ndigits);
	else tmp_d = malloc(sizeof(int));

	if (!tmp_d) {
		puts("malloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}

	struct bigint *bi = malloc(sizeof(struct bigint));
	if (!bi) {
		puts("malloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}

	bi->ndigits = ndigits;
	bi->d = tmp_d;
	if (ndigits == 1) bi->d[0] = 0;

	return bi;
}

void bigint_free(struct bigint *bi) {
	if (bi->d != NULL) free(bi->d);

	if (bi != NULL) {
		free(bi);
		bi = NULL;
	}
}

void bigint_pushc(struct bigint *bi, int x) {
	if (!bi) {
		bi = bigint_init(1);
		bi->d[0] = x;
		return;
	}

	int *tmp_d = realloc(bi->d, (bi->ndigits+1) * sizeof(int));
	if (!tmp_d) {
		puts("realloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}
	bi->d = tmp_d;

	bi->ndigits++;
	bi->d[bi->ndigits-1] = x;
}

/*
void bigint_popc(struct bigint *bi) {
	struct bigint *new_bi = realloc(bi, sizeof(int) * bi->ndigits);
	if (!new_bi) {
		puts("realloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}
	bi = new_bi;

	bi->ndigits--;
}
*/

struct bigint *bigint_add(const struct bigint *a, const struct bigint *b) {
	struct bigint *sum = bigint_init(0);

	int carry = 0;
	for (int i = 0; i < a->ndigits; i++) {
		int digit_sum = a->d[i] + b->d[i] + carry;
		bigint_pushc(sum, digit_sum % 10);
		carry = digit_sum / 10;
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
	struct bigint *product = bigint_init(0);

	int carry = 0;
	for (int i = 0; i < b->ndigits; i++) { /* B's digit counter */
		if (b->d[i] == 0) continue;

		struct bigint *row_product = bigint_init(0);
		for (int pad = 0; pad < i; pad++) {
			bigint_pushc(row_product, 0);
		}

		for (int j = 0; j < a->ndigits; j++) { /* A's digit counter */
			int digit_product = a->d[j] * b->d[i] + carry;
			bigint_pushc(row_product, digit_product % 10);
			carry = digit_product / 10;
		}

		/* carry extra overflow digits */
		while (carry > 0) {
			bigint_pushc(row_product, carry % 10);
			carry /= 10;
		}

		bigint_add(product, row_product);

		bigint_free(row_product);
	}

	return product;
}

void bigint_print(struct bigint *bi) {
	if (bi->ndigits >= 1) {
		for (int i = bi->ndigits-1; i >= 0; i--) {
			printf("%d", bi->d[i]);
		}
		printf("\n");
	}
}

#ifdef DEBUG
int main(void) {
	struct bigint *x = bigint_init(2);
	free(x->d);
	//x->d = (int []) {2, 4};
	x->d = (int []) {9, 9};

	struct bigint *y = bigint_init(2);
	free(y->d);
	//y->d = (int []) {5, 0};
	y->d = (int []) {9, 9};

	struct bigint *sum = bigint_add(x, y);
	bigint_print(sum);

	struct bigint *product = bigint_mult(x, y);
	bigint_print(product);

	bigint_free(product);
	bigint_free(sum);
	free(y);
	free(x);
}
#endif
