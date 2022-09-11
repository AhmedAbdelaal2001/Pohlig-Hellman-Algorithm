#include "modularArithmetic_utility.h"

//Computes g^A (mod N) in logarithmic time.
long long int fastPowering(long long int g, long long int A, long long int N) {

	long long int a = g;
	long long int b = 1;

	while (A > 0) {

		if (A % 2 == 1)
			b = (b * a) % N;

		A /= 2;
		a = (a * a) % N;
	}

	return b;
}

//Computes the order of an element g belonging to the field of integers modulo p.
long long int computeOrder(long long int g, long long int p, list<int>* primeFactors) {

	long long int N = p - 1;
	list<int>::iterator it = primeFactors->begin();
	bool flag = false;

	for (it; it != primeFactors->end(); it++) {
		
		if (flag) it--;
		flag = false;

		long long int power = fastPowering(g, N / *it, p);
		if (power == 1)
		{
			N /= *it;
			it = primeFactors->erase(it);
			flag = true;
		}
		else {

			int currentFactor = *it;
			it++;
			while ((it != primeFactors->end()) && (*it == currentFactor)) {
				it++;
			}

			if (it == primeFactors->end())
				break;
			it--;

		}
	}

	return N;

}

//Computes a^-1 (mod b)
long long int computeInverse(long long int a, long long int p) {

	long long int inverse = 0;
	long long int v = 0;

	extendedEuclidean(a, p, inverse, v);

	while (inverse < 0)
		inverse += p;

	return inverse;

}

//Solves two congruences of the form x = a (mod m) & x = b (mod n)
long long int solveCongruences(long long int a, long long int b, long long int m, long long int n) {

	long long int y = (b - a) * computeInverse(m, n);
	long long int x = (a + y * m) % (m * n);

	if (x < 0)
		x += m * n;

	return x;
}

//Solves a system of congruences of the form: x = c1 (mod m1) & x = c2 (mod m2) & ... & x = cn (mod mn).
//Equivalent to solving the Chinese Remainder Problem.
long long int chineseRemainder(list<long long int> c, list<long long int> m) {

	list<long long int>::iterator it1 = c.begin();
	list<long long int>::iterator it2 = m.begin();

	long long int currentC = *it1;
	long long int currentM = *it2;

	it1++;
	it2++;

	for (it1; it1 != c.end(); it1++) {

		currentC = solveCongruences(currentC, *it1, currentM, *it2);
		currentM *= *it2;

		it2++;

	}

	return currentC;


}
