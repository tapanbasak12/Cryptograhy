#include <bits/stdc++.h>
#include<iostream>
#include<math.h>
#include<random>
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
string getString(){
    cout << "Input string: ";

    string str;
    getline(cin, str);

    return str;
}

int getBlockSize(){
    string inputStr;
    int blockSize;

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


string addPadding(string str, int blockSize, char paddingChar){
    while(str.length() % blockSize != 0){
        str += paddingChar;
    }
    return str;
}

string tokenize(string str, int blockSize){
    for(int i = blockSize; i < str.length(); i += blockSize+1){     
        str.insert(i, 1, ' ');
    }
    return str;
}

vector<int> encode(string s, int blockSize)
{
    vector <int> encoded_array; 
    
    int i=blockSize-1; 
    int j=0; 
    while(j+blockSize <= s.length())
    {
        int sum=0, num, x=0;
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
}


int rsa_encryption(int m, int p, int q, int e)
{
    long long int  n, phi_n, e_inverse, d, C, D;
    
    n= p*q; 
    phi_n = (p-1) * (q-1); 
     
    
    e_inverse = modInverse(e, phi_n); 
    d = powerSqAndMul(e_inverse, 1,  phi_n ); 
   
    C= powerSqAndMul(m, e, n);
    D= powerSqAndMul (C, d, n);
    
    return C;  
}

int rsa_decryption(int C, int p, int q, int e)
{
    long long int n, e_inverse, phi_n, d, D;
    
    n= p*q;
    phi_n = (p-1) * (q-1); 
    
    e_inverse = modInverse(e, phi_n); 
    d = powerSqAndMul(e_inverse, 1,  phi_n); 
   
    D= powerSqAndMul (C, d, n);
    
    return D;  
}



int main()
{
    string str = getString();
    int blockSize = getBlockSize();
    char paddingChar = 'x';

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str = addPadding(str, blockSize, paddingChar);
    str = tokenize(str, blockSize);
     
    cout << "String in Blocks: \n" << str;

    cout << endl; 
    vector<int> encoded_array = encode(str, blockSize);
    
    cout << "Encoded Array: " <<endl;
    for(int i=0; i< encoded_array.size(); i++)
    {
        cout << encoded_array[i] << " "; 
    }
    
    vector <int> rsa_encrypted_array;
    
    cout << "\nEncrypted RSA string: " <<endl; 
    for(int i=0; i< encoded_array.size(); i++)
    {
        int C= rsa_encryption(encoded_array[i], 29, 31, 53);
        rsa_encrypted_array.push_back(C);
        cout << rsa_encrypted_array[i] << " "; 
    }
    
    cout << "\nDecrypted RSA string: Equal to " <<endl; 
    vector <int> rsa_decrypted_array;
    for(int i=0; i< rsa_encrypted_array.size(); i++)
    {
        int D= rsa_decryption(rsa_encrypted_array[i], 29, 31, 53);
        rsa_decrypted_array.push_back(D);
        cout << rsa_decrypted_array[i] << " "; 
    }
    
    cout << "\nDecoded RSA String:" <<endl; 
    vector<string> decoded_str; 
    for (int i=0 ; i < rsa_decrypted_array.size(); i++)
    {
        decode(rsa_decrypted_array[i]);
    }
    
   
    return 0;
}
