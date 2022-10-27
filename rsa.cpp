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


int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int modInverse(int A, int M)
{
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
    long long int m, p,q, n, phi_n, e, e_inverse, d, C, D;
    
    
    cout << "Enter Prime Numbers: ";
    cin >> p >> q;
    
    n= p*q; 
    cout << "n: " << n <<endl; 
    phi_n = (p-1) * (q-1); 
    cout << "phi_n: " << phi_n <<endl; 
   
    m = 6; //message  
    
    e=2; // e can be given
    while(e < phi_n) 
    {
      if(gcd(e, phi_n)==1)
         break;
      else
         e++;
    }
    cout << "e: " << e <<endl; 
    
    e_inverse = modInverse(e, phi_n); 
    d = powerSqAndMul(e_inverse, 1,  phi_n ); 
    cout << "d: " << d <<endl; 
   
    C= powerSqAndMul(m, e, n);
    D= powerSqAndMul (C, d, n);
    
    cout<< "Encrypted: " << C << "\nDecrypted: " << D << endl; 
    
     
    return 0;
}
