#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_prime(int x) {
	/* Test primality of a given number via the Miller-Rabin test. */
	int m;
	for (int k = 1; k < 10; k++) {
		if ((x - 1) % (1 << k) == 0)
			m = (x - 1) >> k;
		else
			break;
	}

	int a = 2;

	long long a_m = 1;
	for (int i = 0; i < m; i++)
		a_m *= a;

	long long b = a_m % x;
	if (b == 1 || b == x-1)
		return true;

	for (int i = 0; i < 10; i++) {
		if (b == 1)
			return false;
		else if (b == x-1)
			return true;

		b = (b*b) % x;
	}

	return false;
}

int main(void) {
	printf("%d\n", is_prime(53));
	printf("%d\n", is_prime(55));
	printf("%d\n", is_prime(11));
	printf("%d\n", is_prime(13));
	printf("%d\n", is_prime(14));
	printf("%d\n", is_prime(101));
}
