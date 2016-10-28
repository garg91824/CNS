#include <gmp.h>
#include <iostream>
using namespace std;

gmp_randstate_t state;
void getPrimes (mpz_t x , mpz_t y)
{
	mpz_urandomb (x , state , 10);
	mpz_nextprime(x , x);

	mpz_urandomb( y , state , 10 );
	mpz_nextprime(y , y );

	return;
}
void getEandD(mpz_t e , mpz_t d, mpz_t phiN)
{
	step1 : mpz_urandomm( e , state , phiN);	
	if(mpz_invert(d , e , phiN)==0)
		goto step1;
}
void encrypt(mpz_t mesg , mpz_t encrypted , mpz_t e , mpz_t n)
{
	mpz_powm(encrypted , mesg , e , n);
}

void decrypt(mpz_t mesg , mpz_t encrypted , mpz_t d , mpz_t n)
{
	mpz_powm(mesg , encrypted ,d ,n);
}
int main()
{
	mpz_t p , q , n , phiN ,  temp1 ,temp2 ,e,d , mesg , encryptedMesg;
	gmp_randinit_default(state);
	mpz_inits(p ,q ,n,phiN , temp1 , temp2 , e,d , mesg , encryptedMesg ,NULL);
	
	getPrimes(p , q);

	//get the value of n
	mpz_mul(n , p ,q );

	gmp_printf("Value of n : %Zd\n",n);
	//Calculate phi(n)
	mpz_sub_ui(temp1 , p ,1);
	mpz_sub_ui(temp2 , q ,1);
	mpz_mul(phiN , temp1 , temp2);

	//get E and D values
	getEandD(e ,d, phiN);

	//get message
	cout<<"Enter message \n";
	gmp_scanf("%Zd", mesg);
	
	//Encrypt
	encrypt(mesg , encryptedMesg , e , n);
	gmp_printf("Encrypted Message : %Zd \n", encryptedMesg);

	//Decrypt
	decrypt( mesg , encryptedMesg , d , n );
	gmp_printf("Decrypted Message : %Zd \n",mesg);

}
