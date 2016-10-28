#include<stdio.h>
#include<gmp.h>

mpz_t temp;
void power(mpz_t a,mpz_t b,mpz_t c,mpz_t ans){
	mpz_set_ui(ans,1);
	while(mpz_sgn(b)>0){
		mpz_mod_ui(temp,b,2);
		if(mpz_cmp_ui(temp,1)==0){
			mpz_mul(ans,ans,a);
			mpz_mod(ans,ans,c);
		}
		mpz_mul(a,a,a);
		mpz_mod(a,a,c);
		mpz_tdiv_q_ui(b,b,2);	
	}
}

int main()
{
	mpz_t x,y,c,ans;
	mpz_init(x);
	mpz_init(y);
	mpz_init(c);
	mpz_init(ans);
	mpz_init(temp);
	while(1){
		gmp_scanf("%Zd %Zd %Zd",&x,&y,&c);
		power(x,y,c,ans);
		gmp_printf("The answer is %Zd\n",ans);
	}
	return 0;
}
