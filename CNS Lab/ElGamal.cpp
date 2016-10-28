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
	gmp_randstate_t state;
	gmp_randinit_default ( state );
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

void encrypt (mpz_t y , mpz_t mesg , mpz_t c1 , mpz_t c2 )
{
	mpz_t k , K;
	mpz_inits(k,K,NULL);
	mpz_urandomm( k , state , temp ) ;
	
	mpz_powm ( c1 , generator , k , temp );
	mpz_powm ( K , y , k , temp );
	mpz_mul ( c2 , mesg , K );
	mpz_mod ( c2 , c2 , temp);

}

void decrypt(mpz_t x , mpz_t c1 , mpz_t c2)
{
	mpz_t K;
	mpz_init(K);
	mpz_powm(K , c1 , x , temp );
	mpz_invert ( K , K , temp);
	mpz_mul(c2 ,c2 , K);
	mpz_mod(c2 , c2, temp);


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
	mpz_t xA , yA , k , K , c1 ,c2 ,M;
	mpz_inits(xA , yA , k , K ,M ,c1,c2, NULL );

	gmp_randinit_default(state);
	mpz_inits(prime , temp ,  generator , one , NULL);
	mpz_set_ui (one , 1 );
	primeAndGenerator();
	gmp_printf("Prime is %Zd and generator is %Zd \n ",temp , generator );
	
	privatePublicKeys(xA , yA );
	mpz_set_ui(M , 45 );
	
	encrypt(yA , M , c1 , c2);
	gmp_printf("Sent Message : (c1 , c2 ) : (%Zd , %Zd) \n",c1,c2);
	decrypt(xA , c1 , c2 );
	gmp_printf("Decrypted Messge :%Zd \n",c2);
}
