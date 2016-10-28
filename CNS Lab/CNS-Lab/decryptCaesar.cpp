#include<bits/stdc++.h>
using namespace std;

int main()
{	
	int i,j,n;
	string str;
	while(1){
		getline(cin,str);
		for(i=0;i<26;i++){
			for(j=0;j<str.size();j++){
				if(str[j]==' ') continue;
				str[j]=(str[j]-1+26-'a')%26+'a';
			}
			cout<<str<<"\n";
		}
	}
	return 0;
}
