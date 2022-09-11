# Pohlig-Hellman-Algorithm
The Pohlig-Hellman Algorithm is used to compute discrete logarithms in finite Abelian groups. In this repository, the algorithm was implemented in C++ for the group of units modulo a prime number p. In other words, we are efficiently solving the problem g ^ x = h (mod p) for large values of g, h, and p.

## Purpose
I implemented this algorithm to reinforce my study of public key cryptosystems; to experiment with breaking cryptosystems which depend on the hardness of the discrete logarithm problem, such as the Diffie-Hellman key exchange scheme and Elgamal PKC.

### How it Works
The algorithm first computes the order N of g, which must divide p - 1 according to Fermat's little theorem and Lagrange's theorem. We then compute the prime factorization of N (i.e. we write N = q1^e1 * q2^e2 * ... * qt^et). Afterwards, we define t different subproblems as (g^(N/qi^ei))^x = h^(N/qi^ei) (mod p) for i ranging from 1 to t. Each of said subproblems is a DLP itself, dealing with an element of order qi^ei, and they can be solved using Shanks' Giant-step Baby-step algorithm along with a decomposition of x into a linear combination of powers of qi, in O(ei * sqrt(qi)). Finally, the solutions to the t subproblems are conjoined using the Chinese Remainder Theorem, yielding the final answer. 
