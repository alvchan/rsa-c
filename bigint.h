struct bigint {
	int ndigits;
	int *d;
};

struct bigint *bigint_init(const int ndigits);
void bigint_free(struct bigint *bi);
void bigint_pushc(struct bigint *bi, const int x);
void bigint_popc(struct bigint *bi);
struct bigint *bigint_add(const struct bigint *a, const struct bigint *b);
void bigint_print(struct bigint *bi);

