#include <bits/stdc++.h>
#include<iostream>
#include<math.h>
#include<random>
using namespace std;
 
std::random_device rd;
std::mt19937 gen(rd());

long long int powerSqAndMul(long long int u, long long int m, long long int p)
{
   long long int A=1,b;
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

long long int random(long long int low, long long int high)
{
    std:: uniform_int_distribution<> dist(low, high);
    return dist(gen);
}


long long int gcd(long long int a, long long int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

long long int modInverse(long long int A, long long int M)
{
	long long int m0 = M;
	long long int y = 0, x = 1;

	if (M == 1)
		return 0;

	while (A > 1) {

		long long int q = A / M;
		long long int t = M;

		M = A % M, A = t;
		t = y;

		y = x - q * y;
		x = t;
	}

	if (x < 0)
		x += m0;

	return x;
}
string getString(){
    cout << "Input string: ";

    string str;
    getline(cin, str);

    return str;
}

long long int getBlockSize(){
    string inputStr;
    long long int blockSize;

    do{
        try{
            cout << "Block size: ";
            getline(cin, inputStr);
            blockSize = stoi(inputStr);
        } catch(...){
            blockSize = 0;
        }
    } while(blockSize < 1);

    return blockSize;
}


string addPadding(string str, long long int blockSize, char paddingChar){
    while(str.length() % blockSize != 0){
        str += paddingChar;
    }
    return str;
}

string tokenize(string str, long long int blockSize){
    for(long long int i = blockSize; i < str.length(); i += blockSize+1){     
        str.insert(i, 1, ' ');
    }
    return str;
}

vector<long long int> encode(string s, long long int blockSize)
{
    vector <long long int> encoded_array; 
    
    long long int i=blockSize-1; 
    long long int j=0; 
    while(j+blockSize <= s.length())
    {
        long long int sum=0, num, x=0;
        while ( i>=j)
        {
            s[i]= toupper(s[i]);
            num = int(s[i]-'A'); 
            sum += num * (pow(26, x));  
            x++; 
            //cout << "i: inside: " << i <<endl;
            i--;
        }
        encoded_array.push_back(sum); 
        //cout << "current i pos: " << i <<" " << s[i] <<endl; 
        //cout << "current j pos: " << j <<" " << s[j] <<endl; 
        i= i+ (blockSize*2)+1; 
        j= j+ blockSize+1; 
        
    }
    return encoded_array; 
}

void decode(long long int N)
{
    long long int i=1, L=26; 
       vector<long long int> vec; 
       long long int a; 
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
       
       for(long long int i=vec.size()-1; i>=0; i--)
       {
           cout << char(vec[i]+'A');
       }
}


long long int rsa_encryption(long long int m, long long int p, long long int q)
{
    long long int e, n, phi_n, e_inverse, d, C, D;
    
    n= p*q; 
    phi_n = (p-1) * (q-1); 
    
    e=2; // e can be given
    while(e < phi_n) 
    {
      if(gcd(e, phi_n)==1)
         break;
      else
         e++;
    }
    e_inverse = modInverse(e, phi_n); 
    d = powerSqAndMul(e_inverse, 1,  phi_n ); 
   
    C= powerSqAndMul(m, e, n);
    D= powerSqAndMul (C, d, n);
    
    return C;  
}

long long int rsa_decryption(long long int C, long long int p, long long int q)
{
    long long int e, n, e_inverse, phi_n, d, D;
    n= p*q; 
    phi_n = (p-1) * (q-1); 
    e=2; // e can be given
    while(e < phi_n) 
    {
      if(gcd(e, phi_n)==1)
         break;
      else
         e++;
    }
    
    n= p*q;
    phi_n = (p-1) * (q-1); 
    
    e_inverse = modInverse(e, phi_n); 
    d = powerSqAndMul(e_inverse, 1,  phi_n); 
   
    D= powerSqAndMul (C, d, n);
    
    return D;  
}



int main()
{
    long long int p= 1299887 , q= 1299899 ;
    string str = "crypto";
    int blockSize = 2;
    char paddingChar = 'x';

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str = addPadding(str, blockSize, paddingChar);
    str = tokenize(str, blockSize);
     
    cout << "String in Blocks: \n" << str;

    cout << endl; 
    vector<long long int> encoded_array = encode(str, blockSize);
    
    cout << "Encoded Array: " <<endl;
    for(long long int i=0; i< encoded_array.size(); i++)
    {
        cout << encoded_array[i] << " "; 
    }
    
    vector <long long int> rsa_encrypted_array;
    
    cout << "\nEncrypted RSA string: " <<endl; 
    for(long long int i=0; i< encoded_array.size(); i++)
    {
        long long int C= rsa_encryption(encoded_array[i], p, q);
        rsa_encrypted_array.push_back(C);
        cout << rsa_encrypted_array[i] << " "; 
    }
    
    cout << "\nDecrypted RSA string: " <<endl; 
    vector <long long int> rsa_decrypted_array;
    for(long long int i=0; i< rsa_encrypted_array.size(); i++)
    {
        long long int D= rsa_decryption(rsa_encrypted_array[i], p, q);
        rsa_decrypted_array.push_back(D);
        cout << rsa_decrypted_array[i] << " "; 
    }
    
    cout << "\nDecoded RSA String:" <<endl; 
    vector<string> decoded_str; 
    for (long long int i=0 ; i < rsa_decrypted_array.size(); i++)
    {
        decode(rsa_decrypted_array[i]);
    }
    
   
    return 0;
}
