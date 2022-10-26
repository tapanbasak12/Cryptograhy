
// Online IDE - Code Editor, Compiler, Interpreter

#include<iostream>

using namespace std;

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

int main()
{
  cout << powerSqAndMul(3, 118, 23);
}
