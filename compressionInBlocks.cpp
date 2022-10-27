#include <bits/stdc++.h>
using namespace std;

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
       
       cout<<endl; 
}

int main()
{
    string str = getString();
    int blockSize = getBlockSize();
    char paddingChar = 'X';

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str = addPadding(str, blockSize, paddingChar);
    str = tokenize(str, blockSize);
     
    cout << "String in Blocks: \n" << str;

    cout << endl; 
    vector<int> encoded_array = encode(str, blockSize); 
    for(int i=0; i< encoded_array.size(); i++)
    {
        cout << encoded_array[i] << " "; 
    }
   
    vector<string> decoded_str; 
    for (int i=0 ; i < encoded_array.size(); i++)
    {
         decoded_str.push_back ( decode(encoded_array[i]) );
    }
    
    
    
    
    
    return 0;
}
