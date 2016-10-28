#include <gmp.h>
#include <iostream>
using namespace std;

mpz_t prime , generator , temp , one ; 
gmp_randstate_t state;

void Generator()
{
	mpz_t  rop ;
	mpz_inits(rop, NULL) ;

	step1 : mpz_urandomm (generator , state , temp ) ;
		mpz_powm_ui(rop , generator , 2 , temp );
		if( rop == one)
			goto step1;
		mpz_powm( rop , generator , prime , temp );
		if( rop == one)
			goto step1;
	return ;
}

void primeAndGenerator()
{
	mpz_urandomb (prime , state , 5 );
	
	bool safePrime = false ;
	while(safePrime == false)
	{
		mpz_nextprime(prime , prime);
	
		mpz_set(temp ,prime);
		mpz_mul_si(temp , temp , 2 );
		mpz_add_ui(temp , temp , 1);
		if(mpz_probab_prime_p (temp , 20) != 0)
			safePrime = true;
	}
	Generator();

}

void privatePublicKeys( mpz_t x , mpz_t y )
{
	mpz_urandomm(x , state , temp );
	mpz_powm(y , generator , x , temp ); 
	gmp_printf("private key : %Zd , Publc key : %Zd \n",x,y );
	return ;
}

int main()
{
	mpz_t xA , yA ,xB , yB , sA , sB;
	mpz_inits(xA , yA , xB , yB , sA , sB, NULL );

	gmp_randinit_default(state);
	mpz_inits(prime , temp ,  generator , one , NULL);
	mpz_set_ui (one , 1 );
	primeAndGenerator();
	gmp_printf("Prime is %Zd %Zd and generator is %Zd \n ",prime,temp , generator );
	
	privatePublicKeys(xA , yA );
	privatePublicKeys(xB , yB );
	
	mpz_powm ( sA , yA , xB , temp );
	mpz_powm ( sB , yB , xA , temp );
	
	gmp_printf("Shared secret keys sA : %Zd , sB : %Zd \n" , sA , sB );
}
