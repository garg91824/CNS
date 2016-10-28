#include<stdio.h>
#include<gmp.h>
#include<time.h>

int main()
{
	int i;
	mpz_t x,y,q;
	mpz_init(x);
	mpz_init(y);
	mpz_init(q);
	gmp_randstate_t state;
	gmp_randinit_default(state);
	int cnt=10;
	clock_t start_time,end_time;
	printf("Bits\tSeconds\n");
	for(i=0;i<6;i++){
	//	gmp_scanf("%Zd %Zd",&x,&y);
		mpz_urandomb(x,state,cnt);
		mpz_urandomb(y,state,cnt);
		start_time=clock()*1000;
		while(mpz_sgn(y)!=0){	
			mpz_mod(q,x,y);
			mpz_set(x,y);
			mpz_set(y,q);
		}
		end_time=clock()*1000;
		mpz_abs(x,x);
		printf("%d\t%lf\n",cnt,(double)((end_time-start_time))/CLOCKS_PER_SEC);
		cnt=cnt*10;
	}
	return 0;
}
