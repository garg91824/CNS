#include<bits/stdc++.h>
using namespace std;

int main()
{
	int k,i,j,n,t;
	string str;
	while(1){
		cout<<"Enter 1 for encryption and 2 for decryption:";
		cin>>t;
		cin.ignore();
		cout<<"Enter text:";
		getline(cin,str);
		cout<<"Enter the key:";
		cin>>k;
		if(t==1){
			for(i=0;i<str.size();i++){
				if(str[i]==' '){
					continue;
				}
				str[i]=(str[i]+k-'a')%26 + 'a';
			}	
		}	
		else{
			for(i=0;i<str.size();i++){
				if(str[i]==' '){
					continue;
				}
				str[i]=(((str[i]-'a'-k)%26)+26)%26 + 'a';
			}
		}	
		cout<<str<<endl;
	}
	return 0;
}
