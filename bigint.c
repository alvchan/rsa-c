#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

#define DEBUG

void bigint_pushc(struct bigint *bi, const int x) {
	int *tmp_d = realloc(bi, ndigits+sizeof(int);
	if (!tmp_d) printf("realloc failed to allocate memory; out of memory.");
	bi->d = tmp_d;
	bi->ndigits++;
	bi->d[ndigits-1] = x;
}

void bigint_popc(struct bigint *bi) {
	int *tmp_d = realloc(bi, ndigits-sizeof(int));
	if (!tmp_d) printf("realloc failed to allocate memory; out of memory.");
	bi->d = tmp_d;
	bi->ndigits--;
}

struct bigint bigint_add(const struct bigint *a, const struct bigint *b) {
	struct bigint sum;

	int carry = 0;
	for (int i = 0; i < a->ndigits; i++) {
		const int digit_sum = a->d[i] + b->d[i] + carry;
		bigint_pushc(&sum, digit_sum % 10);
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

#ifdef DEBUG
int main(void) {
	;
}
#endif
