#include<stdio.h>
#include<gmp.h>

mpz_t x,y,g;
void extended_euclid(mpz_t a,mpz_t b){
	if(mpz_sgn(b)==0){
		mpz_set_ui(x,1);
		mpz_set_ui(y,0);
		mpz_set(g,a);
		return ;
	}
	mpz_t r;
	mpz_init(r);
	mpz_mod(r,a,b);
	extended_euclid(b,r);
	mpz_set(r,y);
	mpz_set(y,x);
	mpz_t temp;
	mpz_init(temp);
	mpz_tdiv_q(temp,a,b);
	mpz_mul(temp,temp,r);
	mpz_sub(y,y,temp);
	mpz_set(x,r);
}

int main()
{	
	mpz_t a,b;
	mpz_init(a);
	mpz_init(b);
	mpz_init(x);
	mpz_init(y);
	mpz_init(g);
	while(1){
		gmp_scanf("%Zd %Zd",&a,&b);
		extended_euclid(a,b);
		if(mpz_sgn(g)<0){
			mpz_mul_si(x,x,-1);
			mpz_mul_si(y,y,-1);
			mpz_abs(g,g);
		}
		gmp_printf("%Zd %Zd %Zd\n",x,y,g);	
	}
	return 0;
}
