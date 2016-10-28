#include<bits/stdc++.h>
using namespace std;
	
char s[27];
string str;

int main()
{
	int t,n,k,i;
	for(i=0;i<26;i++){
		s[i]='a'+i;
	}
	while(1){
		random_shuffle(s,s+26);
		cout<<"The key is:";
		for(i=0;i<26;i++){
			cout<<s[i];
		}
		cout<<endl;
		cout<<"Enter the text:";
		getline(cin,str);
		for(i=0;i<str.size();i++){
			if(str[i]==' ') continue;
			str[i]=s[str[i]-'a'];
		}		
		cout<<str<<"\n";
	}

	return 0;	
}
