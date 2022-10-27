#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int modInverse(int A, int M)
{
	if(gcd(A,M) != 1) 
	{
	    cout << "A and P are not co-primes: Inverse doesn't exist ";
	    return 0; 
	}
	
	int m0 = M;
	int y = 0, x = 1;

	if (M == 1)
		return 0;

	while (A > 1) {

		int q = A / M;
		int t = M;

		M = A % M, A = t;
		t = y;

		y = x - q * y;
		x = t;
	}

	if (x < 0)
		x += m0;

	return x;
}

int main()
{
	int A = 112, P = 114; // ax = 1 *(mod P)
    
	cout << "Modular inverse of A: " << modInverse(A, P) <<endl;
	return 0;
}

