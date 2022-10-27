#include <bits/stdc++.h>
using namespace std;

int encode(string s)
{
    int sum=0, num, x=0;
    for (int i=s.length()-1; i>=0 ; i--)
    {
        s[i]= toupper(s[i]);
        num = int(s[i]-'A'); 
        sum += num * (pow(26, x));  
        x++; 
    }
    
    return sum; 
}

void decode(int N)
{
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
       
       cout<<endl; 
}

int main()
{
    string s= "njit" ;
    
    int sum = encode(s); 
    cout << sum <<endl; 
    
    decode(sum);
    
    
    return 0;
}
