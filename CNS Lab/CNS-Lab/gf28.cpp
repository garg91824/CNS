#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;

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
			gmp_printf("%Zd\n",arr[i][j]);
		}
	}
}

int main()
{
	create_table();
	return 0;
}