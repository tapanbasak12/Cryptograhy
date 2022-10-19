#include <bits/stdc++.h>

using namespace std;
int main()
{
   int N=3276872;
   int i=1, L=26; 
   vector<int> vec; 
   int a; 
   while(1)
   {
       a = N % L;
       vec.push_back(a); 
       N= (N-a)/L; 
       
       if(N < L)
       {
           vec.push_back(N); 
           break;
       }
   }
   
   
   for(int i=vec.size()-1; i>=0; i--)
   {
       cout << char(vec[i]+'A');
   }
   
   return 0;
}
