#include<stdio.h>
#include<gmp.h>

int main()
{
	mpz_t x,y,q;
	mpz_init(x);
	mpz_init(y);
	mpz_init(q);
	while(1){
		gmp_scanf("%Zd %Zd",&x,&y);
		while(mpz_sgn(y)!=0){
			mpz_mod(q,x,y);
			mpz_set(x,y);
			mpz_set(y,q);
		}
		mpz_abs(x,x);
		gmp_printf("%Zd\n",x);
	}
	return 0;
}
