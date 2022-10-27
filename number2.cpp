#include<iostream>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;

std::random_device rd;
std::mt19937 gen(rd());


long long int random(long long int low, long long int high)
{
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
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
    string str = "cryptography";
    int blockSize = 2; 
    char paddingChar = 'x';

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str = addPadding(str, blockSize, paddingChar);
    str = tokenize(str, blockSize);
     
    cout << "String in Blocks: \n" << str;

    cout << endl; 
    vector<int> encoded_array = encode(str, blockSize); 
    cout << "Numeric Representation: (Encoded): " <<endl; 
    for(int i=0; i< encoded_array.size(); i++)
    {
        cout << encoded_array[i] << " "; 
    }
    
    cout <<endl; 
    long long int P, G, p_a, a, p_b, b, k,M, C, H, m, q, R, key, D;
     
    P= 1299869;
    key = 12; 
    
    G = findGenerator(P); 
    cout << "Genrator for prime: " << G <<endl;
    
    a =  key; 
    p_a = powerSqAndMul(G, a, P); 
    cout << "Private Key of Alice: " << a <<endl;
    cout << "Public Key of Alice:(g^a mod P): " << p_a <<endl; 
    
    
    b = key*key;  
    p_b = powerSqAndMul(G, b, P);
    cout << "Private Key of Bob: " << b <<endl;
    cout << "Public Key of Bob(g^b mod P): " << p_b <<endl;
    
    
    vector <long long int> elgamal_encrypted_array;
    cout << "Elgamal Encryption: " <<endl; 
    
    for(int i=0; i< encoded_array.size(); i++)
    {
        int m= encoded_array[i]; 
         // Elgalmal Encryption
        k= 2; //secret key any random value
        M= powerSqAndMul(p_b, k, P);
        C= powerSqAndMul(m*M, 1, P); 
        H= powerSqAndMul(G, k, P); //Hint
        elgamal_encrypted_array.push_back(C);
        cout << elgamal_encrypted_array[i] << " "; 
    }
       
    cout <<endl;
    vector <long long int> elgamal_decrypted_array;
    
    cout << "Elgamal Decryption: " <<endl; 
    for(int i=0; i< elgamal_encrypted_array.size(); i++)
    {
         // Elgamal Decryption
        C= elgamal_encrypted_array[i]; 
        q= P-1-b;
        R= powerSqAndMul(H, q, P);
        D= powerSqAndMul(C*R, 1 , P);
        elgamal_decrypted_array.push_back(D);
        cout << elgamal_decrypted_array[i] << " ";
    }
    
    
    
    cout <<endl;
    return 0;
}
