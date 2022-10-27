#include<iostream>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;
 
long long int powerSqAndMul(long long int u, long long int m, long long int p)
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


bool isPrime(long long int n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;
 
    
    if (n%2 == 0 || n%3 == 0) return false;
 
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;
 
    return true;
}

void findPrimefactors(unordered_set<long long int> &s, long long int n)
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

long long int findGenerator(long long int n)
{
    unordered_set<long long int> s;
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
    long long int P, G, x, a, y, b, ka, kb;
    int key = 12;  
    P= 1299869;
    
    G = findGenerator(P); 
    cout << "Generator for prime: " << G <<endl;
    
    a = key*key; //secret key of alice 
   
    x = powerSqAndMul(G, a, P); 
    cout << "Alice Sends to Bob:(g^a mod P): " << x <<endl; 
   
    b = key*key*key; 
    y = powerSqAndMul(G, b, P);
    cout << "Bob Sends to Alice(g^b mod P): " << x <<endl;
    
    ka = powerSqAndMul(y, a, P); 
    kb = powerSqAndMul(x, b, P); 
     
    printf("Secret key for the Alice is : %lld\n", ka);
    printf("Secret Key for the Bob is : %lld\n", kb); 
     
    return 0;
}
