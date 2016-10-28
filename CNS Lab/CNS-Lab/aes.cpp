#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;

#define pb push_back

string mixColumns[4][4]=
{
	{ "02","03","01","01" },
	{ "01","02","03","01" },
	{ "01","01","02","03" },
	{ "03","01","01","02" }
};

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
int hexToNum(char ch){
	if(ch>='0' && ch<='9'){
		return (int)(ch-'0');
	}
	else{
		return (int)(ch-'A'+10);
	}
}

string convertToHex(string str){
	string ret="";
	int i;
	for(i=0;i<str.size();i++){
		ret+=charHex(str[i]);	
	}
	return ret;
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

int binToNum(string s){
	int ret=0;
	int i;
	for(i=0;i<s.size();i++){
		ret=(ret*2+s[i]-'0');
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

mpz_t arr[(1<<8)][(1<<8)];
string pol="100011011";
string limit="11111111";
mpz_t highest;

void convert_gmp(string s,mpz_t foo){
	mpz_init(foo);
	mpz_set_ui(foo,0);
	int i;
	for(i=0;i<s.size();i++){
		mpz_mul_ui(foo,foo,2);
		mpz_add_ui(foo,foo,s[i]-'0');
	}
}

void multiply(int x,int y,mpz_t var,mpz_t irreducPol){
	mpz_t t1,t2;
	int i,j;
	mpz_init(t2);
	mpz_set(t2,irreducPol);
	mpz_init(t1);
	mpz_init(var);
	mpz_set_ui(var,0);
	mpz_set_ui(t1,x);
	for(int i=0;i<8;i++){
		if((1<<i)&y){
			mpz_xor(var,var,t1);
		}
		mpz_mul_2exp(t1,t1,1);
	}
	mpz_t reducer,temp;
	mpz_init(temp);
	mpz_init(reducer);
	mpz_set_ui(reducer,1);
	mpz_mul_2exp(reducer,reducer,16);
	mpz_mul_2exp(t2,t2,8);
	for(i=16;i>=8;i--){
		mpz_init(temp);
		mpz_and(temp,reducer,var);
		if(mpz_sgn(temp)!=0){
			mpz_xor(var,var,t2);
		}
		mpz_div_2exp(reducer,reducer,1);
		mpz_div_2exp(t2,t2,1);
	}
}

void create_table()
{
	int i,j,k;
	mpz_t var;
	mpz_init(var);
	mpz_init(highest);
	convert_gmp(limit,highest);
	for(i=0;i<(1<<8);i++){
		for(j=0;j<(1<<8);j++){
			mpz_init(arr[i][j]);
		}
	}
	mpz_t irreducPol;
	convert_gmp(pol,irreducPol);
	for(i=0;i<(1<<8);i++){
		for(j=0;j<(1<<8);j++){
			multiply(i,j,arr[i][j],irreducPol);
		}
	}
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

mpz_t W[100];
string keys[100];
vector<string>roundkeys;
string roundConstants[11]={"01","02","04","08","10","20","40","80","1B","36"};
string S[16][16],inv_S[16][16];


string leftShift(string s,int amt){
	string ret="";
	ret.resize(s.size());
	int i;
	int n=s.size();
	for(i=0;i<n;i++){
		ret[i]=s[(i+amt)%n];
	}
	return ret;
}

string byteSubstitute(string s,int round){
	string temp1="",temp2="";
	int i,ind1,ind2,j;
	string ret="";
	for(i=0;i<s.size();i+=8){
		temp1="",temp2="";
		for(j=0;j<4;j++){
			temp1+=s[i+j];
			temp2+=s[i+j+4];
		}
		ind1=binToNum(temp1);
		ind2=binToNum(temp2);
		ret+=hexToBin(S[ind1][ind2]);
		if(i==0){
			ret=stringXOR(ret,hexToBin(roundConstants[round]));
		}
	}
	return ret;
}

string singleByteSubs(string s){
	string temp1="",temp2="";
	int i,ind1,ind2,j;
	string ret="";
	assert(s.size()==8);
	for(i=0;i<s.size();i+=8){
		temp1="",temp2="";
		for(j=0;j<4;j++){
			temp1+=s[i+j];
			temp2+=s[i+j+4];
		}
		ind1=binToNum(temp1);
		ind2=binToNum(temp2);
		ret+=hexToBin(S[ind1][ind2]);
	}
	return ret;
}

string G(string s,int round){
	s=leftShift(s,8);
	s=byteSubstitute(s,round);
	return s;
}

void split(string key){
	string temp="";
	int curr=0;
	for(int i=0;i<128;i+=32){
		temp="";
		for(int j=0;j<32;j++){
			temp+=key[i+j];
		}
		keys[curr]=temp;
		curr++;
	}
}


void read_tables(){
	int i,j;
	ifstream in;
	in.open("aes_s_box.txt");
	for(i=0;i<16;i++){
		for(j=0;j<16;j++){
			in>>S[i][j];
		}
	}
	in.close();
	in.open("aes_inv_s_box.txt");
	for(i=0;i<16;i++){
		for(j=0;j<16;j++){
			in>>inv_S[i][j];
		}
	}
	in.close();
}

string convertBinToHex(string s){
	string ret="";
	int i,j;
	for(i=0;i<s.size();i+=4){
		string temp="";
		for(j=0;j<4;j++){
			temp+=s[i+j];
		}
		ret+=fun(binToNum(temp));
	}
	return ret;
}
string stateMatrix[4][4],keyMatrix[4][4],final[4][4];

void convertToMatrix(string plaintext,string temp[][4]){
	int curr=0,i,j,k;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			temp[j][i]="";
			for(k=0;k<8;k++){
				temp[j][i]+=plaintext[curr];
				curr++;
			}
		}
	}
}

string mpzToBin(mpz_t x){
	string ret="";
	int i;
	mpz_t t1,t2,temp;
	mpz_init(t1);
	mpz_init(t2);
	mpz_init(temp);
	mpz_set_ui(t1,1);
	for(i=7;i>=0;i--){
		mpz_mul_2exp(t2,t1,i);
		mpz_and(temp,t2,x);
		if(mpz_sgn(temp)==0){
			ret+="0";
		}
		else{
			ret+="1";
		}
	}
	return ret;
}

int main()
{
	string key,plaintext;
	getline(cin,key);	// 128 bits
	key=convertToHex(key);
	key=hexToBin(key);
	roundkeys.pb(key);
	read_tables();
	create_table();
	cout<<"Round Keys:\n";
	cout<<convertBinToHex(key)<<endl;
	int i,j,k,p;
	string temp="";
	for(i=1;i<=10;i++){
		split(roundkeys[i-1]);
		keys[4]=stringXOR(keys[0],G(keys[3],i-1));
		for(j=5;j<8;j++){
			keys[j]=stringXOR(keys[j-4],keys[j-1]);
		}
		temp="";
		for(j=4;j<8;j++){
			temp+=keys[j];
		}
		cout<<convertBinToHex(temp)<<"\n";
		roundkeys.pb(temp);
	}
	getline(cin,plaintext);
	plaintext=convertToHex(plaintext);
	plaintext=hexToBin(plaintext);
	int curr=0;
	convertToMatrix(plaintext,stateMatrix);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			mixColumns[i][j]=hexToBin(mixColumns[i][j]);
		}
	}
	convertToMatrix(roundkeys[0],keyMatrix);
	cout<<"Round 0\n";
	for(j=0;j<4;j++){
		for(k=0;k<4;k++){
			stateMatrix[j][k]=stringXOR(keyMatrix[j][k],stateMatrix[j][k]);
			cout<<convertBinToHex(stateMatrix[j][k])<<" ";
		}
		cout<<endl;
	}
	for(i=1;i<=10;i++){
		cout<<"Round "<<i<<"\n";
		convertToMatrix(roundkeys[i],keyMatrix);
		for(j=0;j<4;j++){
			for(k=0;k<4;k++){
				stateMatrix[j][k]=singleByteSubs(stateMatrix[j][k]);
			}
		}
		cout<<"Subs\n";
		for(j=0;j<4;j++){
			for(k=0;k<4;k++){
				keys[k]=stateMatrix[j][k];
			}
			for(k=0;k<4;k++){
				stateMatrix[j][k]=keys[(k+j)%4];
				cout<<convertBinToHex(stateMatrix[j][k])<<" ";
			}
			cout<<endl;
		}
		if(i!=10){
			for(j=0;j<4;j++){
				for(k=0;k<4;k++){
					string res="";
					for(p=0;p<8;p++){
						res+="0";
					}
					for(p=0;p<4;p++){
						int i1=binToNum(mixColumns[j][p]);
						int i2=binToNum(stateMatrix[p][k]);
						string t1=mpzToBin(arr[i1][i2]);
						res=stringXOR(res,t1);
						final[j][k]=res;
					}
				}
			}
			for(j=0;j<4;j++){
				for(k=0;k<4;k++){
					stateMatrix[j][k]=final[j][k];
				}
			}
		}
		cout<<"After columnMix and/or RoundKey\n";
		for(j=0;j<4;j++){
			for(k=0;k<4;k++){
				stateMatrix[j][k]=stringXOR(keyMatrix[j][k],stateMatrix[j][k]);
				cout<<convertBinToHex(stateMatrix[j][k])<<" ";
			}
			cout<<endl;
		}
	}
	string ciphrText="";
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			ciphrText+=convertBinToHex(stateMatrix[j][i]);
		}
	}
	cout<<"CiphrText : "<<ciphrText<<endl;
	return 0;
}