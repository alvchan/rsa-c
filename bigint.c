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

#ifdef DEBUG
int main(void) {
	;
}
#endif
