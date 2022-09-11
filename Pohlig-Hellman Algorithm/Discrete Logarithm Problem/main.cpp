#include "DLP_algorithms.h"
#include <iostream>
#include <fstream>

void main() {

	list<int>* primes = new list<int>;
	ifstream inputFile;
	int num;

	inputFile.open("Primes.txt");
	if (!inputFile.is_open()) {

		cout << "Error! Could not open the file." << endl;
		return;

	}

	while (inputFile >> num)
		primes->push_back(num);

	long long int g = 2;
	long long int h = 39183497;
	long long int p = 41022299;

	long long int solution = Pohlig_Hellman(g, h, p, primes);

	cout << solution << endl;
	cout << fastPowering(g, solution, p) << endl;

	delete primes;

}