#include <bits/stdc++.h>

using namespace std;
int main()
{
    string s= "njit" ;
    int sum=0, num, x=0;
    for (int i=s.length()-1; i>=0 ; i--)
    {
        s[i]= toupper(s[i]);
        num = int(s[i]-'A'); 
        sum += num * (pow(26, x));  
        x++; 
    }
    
    cout << sum ; 
    
    return 0;
}
