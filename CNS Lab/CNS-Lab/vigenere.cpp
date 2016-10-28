#include<bits/stdc++.h>
using namespace std;

string str,key;
int main()
{
	int t,n,k,i;
	while(1){
		t=1;
		cout<<"Enter the key:";
		cin>>key;
		n=key.size();
		cin.ignore();
		cout<<"Enter the text:";
		getline(cin,str);
		if(t==1){
			int curr=0;
			for(i=0;i<str.size();i++){
				if(str[i]==' '){
					continue;
				}
				str[i]=(str[i]-'a'+key[curr]-'a')%26 +'a';
				curr=(curr+1)%n;
			}
		}
		else{
			int curr=0;
			for(i=0;i<str.size();i++){
				if(str[i]==' '){
					continue;
				}
				str[i]=(str[i]-key[curr]+26)%26+'a';
				curr=(curr+1)%n;
			}
		}
		cout<<str<<"\n";
	}
	return 0;
}
