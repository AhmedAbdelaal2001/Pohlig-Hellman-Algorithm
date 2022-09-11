#pragma once
#include <list>
using namespace std;

//Checks whether a number n is prime or not.
bool isPrime(long long int n);

//Returns a list containing the prime factors of a number n.
list<int>* primeFactorization(long long int n, list<int>* primes);

//Computes the gcd(a,b), as well as integer solutions to au + bv = gcd(a,b).
long long int extendedEuclidean(long long int a, long long int b, long long int& u, long long int& v);

//Checks whether 2 integers a & b are relatively prime or not.
bool isRelativelyPrime(long long int a, long long int b);

//Takes as input a pointer to an array containing n integers. Returns true if all of the integers are relatively
//prime, and false otherwise.
bool isRelativelyPrimeList(long long int* a, int n);
