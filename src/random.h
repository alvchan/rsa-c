#include <stdint.h>

#define N 624
#define M 397
#define XOR_TEMPER 0x9908b0df
#define UPPER_MASK 0x80000000
#define LOWER_MASK 0x7fffffff
#define DEFAULT_SEED 3791

typedef struct {
	uint32_t state[N];
	int32_t idx;
} mt_vec;

uint32_t rng_rand(void);
