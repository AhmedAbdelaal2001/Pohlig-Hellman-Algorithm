#include "DLP_algorithms.h"

//Solves The Discrete Logarithm Problem (i.e. g^x = h (mod p)) for x, Using Shanks's Babystep-Giantstep Collision Algorithm.
long long int shanks(long long int g, long long int h, long long int p, long long int order) {

	long long int n = 1 + floor(sqrt(order));
	long long int* babyStepList = new long long int[n + 1]; //list that will contain the first n powers of g modulo p.
	long long int babyListPosition = 0; //will store the index position of the target value in the babyStepList.
	long long int giantListPosition = 0; //will store the index position of the target value in the giantStepList.
	long long int currentPower = 1; //Stores the current value of g^x. After the first loop, it will be used to store the current value of h*u^x.
	long long int u; //u = (g^-1)^n 

	for (long long int i = 0; i <= n; i++) { //Fill the babyStepList with the first n powers of g.

		babyStepList[i] = currentPower;
		currentPower = (currentPower * g) % p;

	}

	u = fastPowering(g, (order - 1) * n, p);
	currentPower = (u * h) % p;
	long long int* searchPosition = nullptr;

	for (long long int i = 1; i <= n; i++) { //Compute the values of h*u^x for x ranging from 1 to n. In each iteration,
		                                    //check for a collision with the babyStepList. Store the index positions of the colliding values.

		searchPosition = find(babyStepList, babyStepList + n + 1, currentPower);

		if (searchPosition != babyStepList + n + 1) { //If a collision is found, break out from the loop.
			giantListPosition = i;
			break;
		}

		currentPower = (currentPower * u) % p;
	}

	babyListPosition = searchPosition - babyStepList;

	return (babyListPosition + n * giantListPosition) % order;

}

long long int power(long long int g, long long int A) {
	
	long long int a = g;
	long long int b = 1;

	while (A > 0) {

		if (A % 2 == 1)
			b *= a;

		A /= 2;
		a *= a;
	}

	return b;
}

long long int primePowerSolver(long long int g, long long int h, long long int p, long long int orderBase, long long int orderExponent)
{
	long long int solution = 0;
	long long int previousSolution = 0;
	long long initialExponent = power(orderBase, orderExponent - 1);
	long long int currentExponent = initialExponent;
	long long int g_power = fastPowering(g, initialExponent, p);
	long long int g_power_temp = 1;
	long long int rhs = 0;

	for (long long int i = 0; i < orderExponent; i++) {
		g_power_temp = (g_power_temp * computeInverse(fastPowering(g, solution - previousSolution, p), p)) % p;
		rhs = (g_power_temp * h) % p;
		rhs = fastPowering(rhs, currentExponent, p);
		previousSolution = solution;
		solution += shanks(g_power, rhs, p, orderBase) * power(orderBase, i);
		currentExponent = power(orderBase, orderExponent - 2 - i);
	}

	return solution;
}

long long int Pohlig_Hellman(long long int g, long long int h, long long int p, list<int>* primes) {

	long long int currentValue = -1;
	long long int currentExponent = 0;
	list<int>* primeFactors = primeFactorization(p - 1, primes);
	long long order = computeOrder(g, p, primeFactors);

	list<int>::iterator it = primeFactors->begin();
	list<long long int> X, m;

	while (it != primeFactors->end()) {

		if (*it == currentValue) {
			
			currentExponent++;
			it++;

			if (it == primeFactors->end()) {

				long long int currentPower = power(currentValue, currentExponent);
				long long int currentOrder = order / currentPower;
				long long int current_g = fastPowering(g, currentOrder, p);
				long long int current_h = fastPowering(h, currentOrder, p);
				X.push_back(primePowerSolver(current_g, current_h, p, currentValue, currentExponent));
				m.push_back(currentPower);
			}

			continue;

		}
		else if (it != primeFactors->begin()) {

			long long int currentPower = power(currentValue, currentExponent);
			long long int currentOrder = order / currentPower;
			long long int current_g = fastPowering(g, currentOrder, p);
			long long int current_h = fastPowering(h, currentOrder, p);
			X.push_back(primePowerSolver(current_g, current_h, p, currentValue, currentExponent));
			m.push_back(currentPower);

		}

		currentValue = *it;
		currentExponent = 1;
		it++;
		if (it == primeFactors->end()) {

			long long int currentPower = power(currentValue, currentExponent);
			long long int currentOrder = order / currentPower;
			long long int current_g = fastPowering(g, currentOrder, p);
			long long int current_h = fastPowering(h, currentOrder, p);
			X.push_back(primePowerSolver(current_g, current_h, p, currentValue, currentExponent));
			m.push_back(currentPower);
		}
	}

	return chineseRemainder(X, m);
	
}