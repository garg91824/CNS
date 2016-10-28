#include<bits/stdc++.h>
#include<fstream>
using namespace std;


#define pb push_back
#define pss pair<string,string>
#define mps make_pair
#define F first
#define S second

int pc1[56]={
	      57,  49,   41,  33,   25,    17,   9,
           1,  58,   50,  42,   34,    26,  18,
          10,   2,   59,  51,   43,    35,  27,
          19,  11,    3,  60,   52,    44,  36,
          63,  55,   47,  39,   31,    23,  15,
           7,  62,   54,  46,   38,    30,  22,
          14,   6,   61,  53,   45,    37,  29,
          21,  13,    5,  28,   20,    12,   4
	};

int pc2[48]={
		 14,   17,  11,   24,    1,   5,
          3,   28,  15,    6,   21,  10,
         23,   19,  12,    4,   26,   8,
         16,    7,  27,   20,   13,   2,
         41,   52,  31,   37,   47,  55,
         30,   40,  51,   45,   33,  48,
         44,   49,  39,   56,   34,  53,
         46,   42,  50,   36,   29,  32
	};

int IP[64]={
	    58,   50,  42,   34,   26,  18,   10,   2,
        60,   52,  44,   36,   28,  20,   12,   4,
        62,   54,  46,   38,   30,  22,   14,   6,
        64,   56,  48,   40,   32,  24,   16,   8,
        57,   49,  41,   33,   25,  17,    9,   1,
        59,   51,  43,   35,   27,  19,   11,   3,
        61,   53,  45,   37,   29,  21,   13,   5,
        63,   55,  47,   39,   31,  23,   15,   7
	};

int E_bit[48]={
 		 32,    1,   2,    3,    4,   5,
          4,    5,   6,    7,    8,   9,
          8,    9,  10,   11,   12,  13,
         12,   13,  14,   15,   16,  17,
         16,   17,  18,   19,   20,  21,
         20,   21,  22,   23,   24,  25,
         24,   25,  26,   27,   28,  29,
         28,   29,  30,   31,   32,   1
	};

int PERM[32]={
	 16, 7, 20, 21,
     29, 12, 28, 17,
      1, 15, 23, 26,
      5, 18, 31, 10,
      2,  8, 24, 14,
     32, 27,  3,  9,
     19, 13, 30,  6,
     22, 11,  4, 25
};

int IPinv[64]={
	40,    8,  48,   16,   56,  24,   64,  32,
    39,    7,  47,   15,   55,  23,   63,  31,
    38,    6,  46,   14,   54,  22,   62,  30,
    37,    5,  45,   13,   53,  21,   61,  29,
    36,    4,  44,   12,   52,  20,   60,  28,
    35,    3,  43,   11,   51,  19,   59,  27,
    34,    2,  42,   10,   50,  18,   58,  26,
    33,    1,  41,    9,   49,  17,   57,  25
};

int S[9][64];

char fun(int num){
	if(num<=9){
		return (char)(num+'0');
	}
	else{
		return (char)(num-10+'A');
	}
}

string charHex(char ch){
	int num=(int)ch;
	int p1=num/16,p2=num%16;
	string ret;
	ret+=fun(p1);
	ret+=fun(p2);
	return ret;
}

string convertToHex(string str){
	string ret="";
	int i;
	for(i=0;i<str.size();i++){
		ret+=charHex(str[i]);	
	}
	return ret;
}

string append(string str){
	str+="0D0A";
	while(1){
		int n=str.size();
		if((n%16)==0){
			break;
		}
		str+="0";
	}
	return str;
}

string charToBin(char ch){
	string ret="";
	int num=0,i;
	if(ch<='9'){
		num=ch-'0';
	}
	else{
		num=10+ch-'A';
	}
	for(i=0;i<4;i++){
		if(num&(1<<i)){
			ret="1"+ret;
		}
		else{
			ret="0"+ret;
		}
	}
	return ret;
}	


string hexToBin(string str){
	string ret="";
	int i;
	for(i=0;i<str.size();i++){
		ret+=charToBin(str[i]);
	}
	return ret;
}

string getPerm(string str,int*  pc1,int sz){
	string ret="";
	int i;
	for(i=0;i<sz;i++){
		ret+=str[pc1[i]-1];
	}
	return ret;
}

string getLower(string str,int num){
	int i;
	string ret="";
	for(i=0;i<num;i++){
		ret+=str[i];
	}
	return ret;
}

string getUpper(string str,int num){
	int i,n=str.size();
	string ret="";
	for(i=0;i<num;i++){
		ret=str[n-1-i]+ret;
	}
	return ret;
}

vector<int>numShifts(16);

string singleShift(string str,int pos){
	string ret="";
	int i;
	for(i=pos;i<str.size();i++){
		ret+=str[i];
	}
	for(i=0;i<pos;i++){
		ret+=str[i];
	}
	return ret;
}

vector<string> shifts(string str,vector<int>pos){
	int i,j;
	vector<string>v;
	v.pb(str);
	for(i=0;i<pos.size();i++){
		v.pb(singleShift(v[i],pos[i]));
	}
	return v;
}

vector<string> convertToKeys(string key){
	vector<string>v;
	string _K=getPerm(key,pc1,56);
	string c0=getLower(_K,28),r0=getUpper(_K,28);
	vector<string>cv=shifts(c0,numShifts),rv=shifts(r0,numShifts);
	int i;
	for(i=0;i<=16;i++){
		v.pb(getPerm(cv[i]+rv[i],pc2,48));
	}
	return v;
}

string stringXOR(string s1,string s2){
	int i;
	string ret;
	for(i=0;i<s1.size();i++){
		if(s1[i]==s2[i]){
			ret+="0";
		}
		else{
			ret+="1";
		}
	}
	return ret;
}

string decToBin(int k){
	string ret="";
	int i;
	for(i=0;i<4;i++){
		if((1<<i)&k){
			ret="1"+ret;
		}
		else{
			ret="0"+ret;
		}
	}
	return ret;
}

string singleBinToHex(string str){
	int num=0,i;
	for(i=0;i<str.size();i++){
		num=num*2+(str[i]-'0');
	}
	string ret="";
	if(num<=9){
		ret+=(num+'0');
	}
	else{
		ret+=(num-10+'A');
	}
	return ret;
}

string binToHex(string str){
	string ret="";
	int i,n=str.size(),j;
	for(i=0;i<n;i+=4){
		string t1="";
		for(j=0;j<4;j++){
			t1+=str[i+j];
		}
		ret+=singleBinToHex(t1);
	}
	return ret;
}

string convertToSS(string str,int pos){
	int row=(str[0]-'0')*2+(str[5]-'0');
	int col=0,i;
	for(i=1;i<5;i++){
		col=col*2+(str[i]-'0');
	}
	return decToBin(S[pos][row*16+col]);
}

string fun2(string s1,string s2,string key){
	s2=getPerm(s2,E_bit,48);
	string temp=stringXOR(s2,key);
	int i,j;
	string foo="";
	for(i=0;i<48;i+=6){
		string t1="";
		for(j=0;j<6;j++){
			t1+=temp[i+j];
		}
		foo+=convertToSS(t1,i/6);
	}
	foo=getPerm(foo,PERM,32);
	foo=stringXOR(foo,s1);
	return foo;
}

vector<pss> getLR(string L0,string R0,vector<string>K){
	vector<pss>ret;
	ret.pb(mps(L0,R0));
	int i;
	for(i=1;i<=16;i++){
		ret.pb(mps(ret[i-1].S,fun2(ret[i-1].F,ret[i-1].S,K[17-i])));
	}
	return ret;
}
	

string go(string str,string key){
	string text=hexToBin(str);
	string K=hexToBin(key);
	vector<string>v = convertToKeys(K);
	string ntext=getPerm(text,IP,64);
	string L0=getLower(ntext,32),R0=getUpper(ntext,32);
	vector<pss>LRS=getLR(L0,R0,v);
	string final=LRS[16].S+LRS[16].F;
	final=getPerm(final,IPinv,64);
	return binToHex(final);
}

string encrypt(string str,string key){
	int i,j;
	string ret="";
	int n=str.size();
	for(i=0;i<n;i+=16){
		string temp="";
		for(j=0;j<16;j++){
			temp+=str[i+j];
		}
		ret+=go(temp,key);
	}	
	return ret;
}

void readTables(){
	ifstream myfile;
	myfile.open("tables.txt");
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<64;j++){
			myfile>>S[i][j];
		}
	}
	myfile.close();
}

int main()
{
	string plaintext,key;
	int type,i;
	for(i=0;i<16;i++){
		numShifts[i]=2;
	}
	numShifts[0]=numShifts[1]=numShifts[8]=numShifts[15]=1;
	readTables();
	cout<<"Enter the key:";
	cin>>key;
	cin.ignore();
	while(1){
		cout<<"Enter the cipherText:";
		getline(cin,plaintext);
		cin>>type;
		cin.ignore();
		if(type==1){
			plaintext=convertToHex(plaintext);
		}
		//plaintext=append(plaintext);
		string cipherText=encrypt(plaintext,key);
		cout<<"The plaintext is:"<<cipherText<<endl;	
	}
	return 0;
}

/*
133457799BBCDFF1
*/