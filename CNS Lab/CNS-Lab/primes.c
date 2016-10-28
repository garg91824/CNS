#include<stdio.h>
#include<gmp.h>

int main()
{	
	mpz_t x,last;
	mpz_init(x);
	mpz_init(last);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	int type;
	mpz_set_str(x,"2",10);
	int cnt;
	scanf("%d",&cnt);
	mpz_urandomb(last,state,cnt);
	gmp_printf("%Zd\n",last);
	while(mpz_cmp(x,last)<=0){
		gmp_printf("%Zd ",x);
		mpz_nextprime(x,x);
	}
	return 0;
}
