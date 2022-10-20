
// Online IDE - Code Editor, Compiler, Interpreter

#include<iostream>

using namespace std;

int main()
{
   int A=1,b,u=5,p=29,m=24;
   while(m>0)
   {
        cout<<u<<" ";
        b=m%2;
        if(b==1)
        A=(A*u)%p;
        m=(m-b)/2;
        u=(u*u)%p;
        cout<<A<<endl;
   }
   cout<<A;
}
