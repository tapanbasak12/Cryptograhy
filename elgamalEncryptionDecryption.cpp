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

int main()
{
    long long int P, G, p_a, a, p_b, b, k,M, C, H, m, q, R, D;
     
    cout << "Enter Prime Number: ";
    cin >>P;
    
    G = findGenerator(P); 
    cout << "Genrator for prime: " << G <<endl;
    
    a = random(2, P-2); 
    p_a = powerSqAndMul(G, a, P); 
    cout << "Private Key of Alice: " << a <<endl;
    cout << "Public Key of Alice:(g^a mod P): " << p_a <<endl; 
    
    
    b = random(2, P-2); 
    p_b = powerSqAndMul(G, b, P);
    cout << "Private Key of Bob: " << b <<endl;
    cout << "Public Key of Bob(g^b mod P): " << p_b <<endl;
    
    cout<<"Enter m (the message in number less than the prime): "; 
    cin >> m;
    
   
    // Elgalmal Encryption
    k= random(1, P-1); //secret key any random value
    M= powerSqAndMul(p_b, k, P);
    C= powerSqAndMul(m*M, 1, P); 
    H= powerSqAndMul(G, k, P); //Hint
    cout << "CipherText: " << C << "\nHint: " << H <<endl;
    
    // Elgamal Decryption
    q= P-1-b;
    R= powerSqAndMul(H, q, P);
    D= powerSqAndMul(C*R, 1 , P);
     
    cout << "Decrypted Message: " << D << endl; 
     
    return 0;
}
