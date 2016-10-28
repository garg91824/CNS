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
	int type;
	mpz_t a,b,c;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);	
	while(1){
		printf("1.Add\n2.Sub\n3.Mul\n4.Div\n");
		scanf("%d",&type);	
		gmp_scanf("%Zd %Zd %Zd",&a,&b,&c);
		if(type==1){
			mpz_add(a,a,b);
			mpz_mod(b,a,c);
			if(mpz_sgn(b)<0){
				mpz_add(b,b,c);
			}
			gmp_printf("%Zd\n",b);
		}
		else if(type==2){
			mpz_sub(a,a,b);
			mpz_mod(b,a,c);
			if(mpz_sgn(b)<0){
				mpz_add(b,b,c);
			}
			gmp_printf("%Zd\n",b);
		}
		else if(type==3){
			mpz_mul(a,a,b);
			mpz_mod(b,a,c);
			if(mpz_sgn(b)<0){
				mpz_add(b,b,c);
			}
			gmp_printf("%Zd\n",b);
		}
		else{
			mpz_init(x);
			mpz_init(y);
			mpz_init(g);
			extended_euclid(b,c);
			if(mpz_sgn(g)<0){
				mpz_mul_si(g,g,-1);
				mpz_mul_si(x,x,-1);
			}
			if(mpz_cmp_si(g,1)==0){
				mpz_mul(a,a,x);
				mpz_mod(b,a,c);
				if(b<0){
					mpz_add(b,b,c);
				}
				gmp_printf("%Zd\n",b);	
			}
			else{
				printf("Mod Division is not possible.\n");
			}
		}
		
	}
	
	return 0;
}
