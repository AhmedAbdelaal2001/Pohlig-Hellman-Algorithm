#include "primes_utility.h"

bool isPrime(long long int n) {

	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false; //To avoid considering even values in the loop below.

	for (long i = 3; i <= floor(sqrt(n)); i++) {

		if (n % i == 0) return false;

	}

	return true;

}

list<int>* primeFactorization(long long int n, list<int>* primes) {

	list<int>* primeFactors = new list<int>;
	list<int>::iterator currentPrime = primes->begin();

	while (n > 1) {

		while (n % *currentPrime == 0) {     //Dealing with repeated prime divisors.

			primeFactors->push_back(*currentPrime);
			n /= *currentPrime;

		}

		currentPrime++;
	}

	return primeFactors;
}

long long int extendedEuclidean(long long int a, long long int b, long long int& u, long long int& v) {

	long long int previousRemainder = a;
	long long int currentRemainder = b;
	long long int next_u = 0;
	u = 1;

	while (currentRemainder != 0) {

		long quotient = previousRemainder / currentRemainder;
		long nextRemainder = previousRemainder % currentRemainder;
		long sum = u - quotient * next_u; //u and quotient * next_u will always have opposite signs, if they are both nonzero.

		previousRemainder = currentRemainder;
		currentRemainder = nextRemainder;
		u = next_u;
		next_u = sum;
	}

	v = (previousRemainder - u * a) / b;

	return previousRemainder;
}

bool isRelativelyPrime(long long int a, long long int b) {

	long long int u = 0;
	long long int v = 0;

	return extendedEuclidean(a, b, u, v) == 1;

}

bool isRelativelyPrimeList(long long int* a, int n) {

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {

			if (!isRelativelyPrime(a[i], a[j]))
				return false;

		}
	}

	return true;
}