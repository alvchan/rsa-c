#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

#define DEBUG

void bigint_pushc(struct bigint *bi, const int x) {
	struct bigint *new_bi = realloc(bi, sizeof(int) * (bi->ndigits + 2));
	if (!new_bi) puts("realloc failed to allocate memory; out of memory.");
	bi = new_bi;
	bi->ndigits++;
	bi->d[bi->ndigits-1] = x;
}

void bigint_popc(struct bigint *bi) {
	struct bigint *new_bi = realloc(bi, sizeof(int) * bi->ndigits);
	if (!new_bi) puts("realloc failed to allocate memory; out of memory.");
	bi = new_bi;
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
