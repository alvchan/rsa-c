#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

#define DEBUG

struct bigint *bigint_init(int ndigits) {
	int *bi_d = malloc(sizeof(int) * ndigits);
	if (!bi_d) {
		puts("malloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}

	struct bigint *bi = malloc(sizeof(int) + sizeof(int *));
	if (!bi) {
		puts("malloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}

	bi->ndigits = ndigits;
	bi->d = bi_d;

	return bi;
}

void bigint_free(struct bigint *bi) {
	free(bi->d);
	bi->d = NULL;

	free(bi);
	bi = NULL;
}

void bigint_pushc(struct bigint *bi, const int x) {
	if (!bi) {
		bi = bigint_init(1);
		return;
	}

	struct bigint *new_bi = realloc(bi, sizeof(int) * (bi->ndigits + 2));
	if (!new_bi) {
		puts("realloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}
	bi = new_bi;

	bi->ndigits++;
	bi->d[bi->ndigits-1] = x;
}

void bigint_popc(struct bigint *bi) {
	struct bigint *new_bi = realloc(bi, sizeof(int) * bi->ndigits);
	if (!new_bi) {
		puts("realloc failed to allocate memory; out of memory.");
		exit(EXIT_FAILURE);
	}
	bi = new_bi;

	bi->ndigits--;
}

struct bigint bigint_add(const struct bigint *a, const struct bigint *b) {
	struct bigint *sum = NULL;

	int carry = 0;
	for (int i = 0; i < a->ndigits; i++) {
		const int digit_sum = a->d[i] + b->d[i] + carry;
		bigint_pushc(sum, digit_sum % 10);
		carry = digit_sum / 10;
	}

	return sum;
}

struct bigint bigint_mult(const struct bigint *a, const struct bigint *b) {
	struct bigint product;

	for (int i = 0; i < b->ndigits; i++) {
		product = bigint_add(&product, a);
	}

	return product;
}

void bigint_print(struct bigint *bi) {
	for (int i = bi->ndigits-1; i >= 0; i--) {
		printf("%d", bi->d[i]);
	}
	printf("\n");
}

#ifdef DEBUG
int main(void) {
	int arr_x[] = {2, 4};
	int arr_y[] = {5, 0};
	const struct bigint x = {2, arr_x};
	const struct bigint y = {2, arr_y};
	struct bigint sum = bigint_add(&x, &y);
	for (int i = 2; i >= 0; i--) {
		printf("%d\n", sum.d[i]);
	}
}
#endif
