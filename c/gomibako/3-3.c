#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PRIME_BOX 1000000

int main() {
double cpu_time;
    int count = 0;
    int num = 2;
    int prime = 0;

    int *primes = (int *)malloc(PRIME_BOX * sizeof(int));
    if (primes == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    while (count < PRIME_BOX) {
        bool is_prime = true;
        int sqrt_num = (int)sqrt(num);

        for (int i = 0; i < count && primes[i] <= sqrt_num; ++i) {
            if (num % primes[i] == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            primes[count] = num;
            prime = num;
            count++;
        }

        num++;
    }
cpu_time = clock();
printf("%.2f", cpu_time/ CLOCKS_PER_SEC);
    printf("1000000番目の素数は: %d\n", prime);

    free(primes);
    
    return 0;
}
