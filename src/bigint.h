#include <stdint.h>
#include "list.h"

struct bigint {
	unsigned int ndigits;
	struct list *d;
};

struct bigint *bigint_init(void);
struct bigint *bigint_initv(long long x);
void bigint_free(struct bigint *bi);
uint8_t bigint_getval(const struct bigint *bi, int index);
void bigint_pushc(struct bigint *bi, uint8_t x);
struct bigint *bigint_add(const struct bigint *a, const struct bigint *b);
struct bigint *bigint_sub(const struct bigint *a, const struct bigint *b);
struct bigint *bigint_mult(const struct bigint *a, const struct bigint *b);
int bigint_compare(const struct bigint *a, const struct bigint *b);
void bigint_print(const struct bigint *bi);

