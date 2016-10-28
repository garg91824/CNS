#include<bits/stdc++.h>
using namespace std;


string s1,s2;
int main()
{	
	int t,n,i,k;
	while(1){
		cout<<"Enter the key:";
		cin>>s1;
		cout<<"Enter the text:";
		cin>>s2;
		for(i=0;i<s1.size();i++){
			int k1=s1[i],k2=s2[i];
			k1^=k2;
			char ch=(char)k1;
			cout<<ch<<" ";	
		}
		cout<<"\n";
	}
	return 0;
}
