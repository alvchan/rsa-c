struct bigint {
	unsigned int ndigits;
	uint8_t *d;
};

struct bigint *bigint_init(unsigned int ndigits);
void bigint_free(struct bigint *bi);
void bigint_pushc(struct bigint *bi, uint8_t x);
void bigint_popc(struct bigint *bi);
struct bigint *bigint_add(const struct bigint *a, const struct bigint *b);
void bigint_print(struct bigint *bi);

