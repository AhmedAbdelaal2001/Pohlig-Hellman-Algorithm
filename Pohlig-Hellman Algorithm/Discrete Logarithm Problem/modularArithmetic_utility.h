#pragma once
#include "primes_utility.h"

//Computes g^A (mod N) in logarithmic time.
long long int fastPowering(long long int g, long long int A, long long int N);

//Computes the order of an element g belonging to the field of integers modulo p.
//The primeFactors argument is a list containing the prime factors of p - 1.
long long int computeOrder(long long int g, long long int p, list<int>* primeFactors);

//Computes a^-1 (mod p)
long long int computeInverse(long long int a, long long int p);

//Solves two congruences of the form x = a (mod m) & x = b (mod n)
long long int solveCongruences(long long int a, long long int b, long long int m, long long int n);

//Solves a system of congruences of the form: x = c1 (mod m1) & x = c2 (mod m2) & ... & x = cn (mod mn).
//Equivalent to solving the Chinese Remainder Problem.
long long int chineseRemainder(list<long long int> c, list<long long int> m);