#pragma once
#include "modularArithmetic_utility.h"

//Solves The Discrete Logarithm Problem (i.e. g^x = h (mod p)) for x, Using Shanks's Babystep-Giantstep Collision Algorithm.
long long int shanks(long long int g, long long int h, long long int p, long long int order);

long long int power(long long int g, long long int A);

long long int primePowerSolver(long long int g, long long int h, long long int p, long long int orderBase, long long int orderExponent);

long long int Pohlig_Hellman(long long int g, long long int h, long long int p, list<int>* primes);