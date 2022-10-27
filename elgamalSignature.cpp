#include<iostream>
#include<math.h>
#include<random>
#include<bits/stdc++.h>
using namespace std;
 
std::random_device rd;
std::mt19937 gen(rd());

int powerSqAndMul(int u, int m, int p)
{
   int A=1,b;
   while(m>0)
   {
        b=m%2;
        if(b==1)
        A=(A*u)%p;
        m=(m-b)/2;
        u=(u*u)%p;
    }
    
    return A; 
}

int random(int low, int high)
{
    std:: uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

bool isPrime(int n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;
 
    
    if (n%2 == 0 || n%3 == 0) return false;
 
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;
 
    return true;
}

void findPrimefactors(unordered_set<int> &s, int n)
{
    
    while (n%2 == 0)
    {
        s.insert(2);
        n = n/2;
    }
 
   for (int i = 3; i <= sqrt(n); i = i+2)
    {
       
        while (n%i == 0)
        {
            s.insert(i);
            n = n/i;
        }
    }
 
    
    if (n > 2)
        s.insert(n);
}

int findGenerator(int n)
{
    unordered_set<int> s;
     if (isPrime(n)==false)
        return -1;
    
    int phi = n-1;
 
    findPrimefactors(s, phi);
 
    
    for (int r=2; r<=phi; r++)
    {
        
        bool flag = false;
        for (auto it = s.begin(); it != s.end(); it++)
        {
            if (powerSqAndMul(r, phi/(*it), n) == 1)
            {
                flag = true;
                break;
            }
         }
        
        if (flag == false)
           return r;
    }
 
    
    return -1;
}

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
    long long int P, G, K, M, C, H, m, q, R, R_inverse, D, r, X, Y, A, A_expected;
     
    cout << "Enter Prime Number: ";
    cin >> P;
    
    M=5;
    
    G = findGenerator(P); 
    cout << "Genrator for prime: " << G <<endl;
    
    r = random(2, P-2); //secret key
    K = powerSqAndMul(G, r, P); 
    
    //signing
    while(1)
    { 
        R = random(2, P-2); 
        if(gcd(R, P-1) == 1 ) break;
    }
    
    X = powerSqAndMul(G, R, P);
    R_inverse= modInverse(R, P-1);
    Y = powerSqAndMul( (M - r*X)*R_inverse, 1, P-1); 
    
    
    // Receiver Computes
    A = powerSqAndMul ( (powerSqAndMul(K, X, P) * powerSqAndMul(X, Y, P) ), 1, P); // A=(K^X)(X^Y) % P;
    
    cout << "Calculated A: " << A <<endl ; 
    
    A_expected = powerSqAndMul(G, M, P);
    
    cout << "Expected A: " << A <<endl ; 
    
    if( A== A_expected) cout << "Verified Signature: AUTHENTICATED" <<endl; 
     
    return 0;
}
