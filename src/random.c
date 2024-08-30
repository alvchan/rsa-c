#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"

/* TODO: check if mt_vec array survives */
mt_vec mt_srand(uint32_t seed) {
	/* Initialize state array with a 32-bit seed. */
	mt_vec mt;

	mt.state[0] = seed & 0xffffffff;
	for (mt.idx = 1; mt.idx < N; mt.idx++)
		mt.state[mt.idx] = (69069 * mt.state[mt.idx-1]) & 0xffffffff;

	return mt;
}

uint32_t mt_rand(uint32_t seed) {
	mt_vec mt = mt_srand(seed);

	uint32_t y;
	static uint32_t mag[2] = {0x0, XOR_TEMPER};

	int32_t i;
	
	if (mt.idx >= N || mt.idx < 0) {
		for (i = 0; i < N-M; i++) {
			y = (mt.state[i] & UPPER_MASK) | (mt.state[i+1] & LOWER_MASK);
			mt.state[i] = mt.state[i+M] ^ (y >> 1) ^ mag[y & 0x1];
		}

		for (; i < N-1; i++) {
			y = (mt.state[i] & UPPER_MASK) | (mt.state[i+1] & LOWER_MASK);
			mt.state[i] = mt.state[i+(M-N)] ^ (y >> 1) ^ mag[y & 0x1];
		}

		y = (mt.state[N-1] & UPPER_MASK) | (mt.state[0] & LOWER_MASK);
		mt.state[N-1] = mt.state[M-1] ^ (y >> 1) ^ mag[y & 0x1];

		mt.idx = 0;
	}

	y = mt.state[mt.idx++];
	y ^= y >> 11;
	y ^= (y << 7) & 0x9d2c5680;
	y ^= (y << 15) & 0xefc60000;
	y ^= y >> 18;

	return y;
}

int main(void) {
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
		printf("%u\n", mt_rand(rand()));
}
