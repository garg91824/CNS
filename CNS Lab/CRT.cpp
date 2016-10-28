#include<iostream>
#include <gmp.h>
#include <vector>
using namespace std;


int main()
{
	int i = 0 , k = 0 , input = 0;
	cout<<"Enter the number of prime factors\n";
	cin >> k ;
	vector<int> mValues , rValues ,cValues;
	mpz_t temp1,temp2;
	mpz_inits(temp1,temp2,NULL);
	cout<<"Enter prime factors\n";
	while( i < k)
	{
		cin>>input;
		mValues.push_back(input);	
		i++ ;
	}
	
	cout<<"Enter the remainders\n";
	i = 0;
	while( i < k )
	{
		cin>>input;
		rValues.push_back(input);
		i++;
	}

	int M = 1;
	for(i = 0 ; i < k ; i++ )
		M = M*mValues[i];

	mpz_t rop;
	mpz_init(rop);
	int temp = 0 ,sum  = 0;
	for(i = 0 ; i < k ; i++ )
	{
		temp = M / mValues[i];
		mpz_set_ui(temp1,temp);
		mpz_set_ui(temp2,mValues[i]);
		mpz_invert(rop , temp1 , temp2);	
		cValues.push_back(mpz_get_ui(rop) * temp);
	}
	for(i = 0 ; i < k ; i++ )
		sum += rValues[i]*cValues[i];
	cout<<(sum % M ) <<endl;

}
