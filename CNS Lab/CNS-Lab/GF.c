#include<stdio.h>
#include<gmp.h>

char *A,*B,*C;
void swap(char* a,char* b){
	char temp=*a;
	*a=*b;
	*b=temp;
}


void convert(char *A,mpz_t x){
	mpz_set_ui(x,0);
	int i;
	for(i=0;i<strlen(A);i++){
		mpz_mul_ui(x,x,2);
		mpz_add_ui(x,x,A[i]-'0');
	}
	//gmp_printf("%Zd\n",x);
}

void convert_rev(mpz_t x,char *A){
	mpz_t temp;
	mpz_init(temp);
	int cnt=0,i;
	while(mpz_sgn(x)!=0){
		mpz_mod_ui(temp,x,2);
		unsigned int a=mpz_get_ui(temp);
		A[cnt++]=a+'0';
		mpz_tdiv_q_ui(x,x,2);
	}
	for(i=0;i<cnt/2;i++){
		swap(&A[i],&A[cnt-i-1]);
	}
	A[cnt]='\0';
}

void adjust(char *A,int n){
	int i,k=strlen(A),j;
	for(i=n-1,j=k-1;i>=0 && j>=0;i--,j--){
		A[i]=A[j];
	}
	while(i>=0){
		A[i--]='0';
	}
}

void add(char *c,char *a,char *b){
	int a1=*a-'0',b1=*b-'0';
	a1=a1*b1;
	int c1=*c-'0';
	c1=(c1+a1)%2;
	*c=c1+'0';
}

void addition(char *A,char *B,char *C){
	int n=strlen(A),i;
	for(i=0;i<n;i++){
		C[i]='0';
		add(&C[i],&A[i],&B[i]);
	}
}

void multiply(char *A,char *B,char *C){
	int n=strlen(A),i,j;
	for(i=0;i<n;i++){
		C[i]='0';
	}
	for(i=0;i<n/2;i++){
		swap(&A[i],&A[n-1-i]);
		swap(&B[i],&B[n-1-i]);
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			add(&C[(i+j)%n],&A[i],&B[j]);
		}
	}
	for(i=0;i<n/2;i++){
		swap(&C[i],&C[n-i-1]);
	}
}		

int main()
{
	mpz_t x,y,z;
	mpz_init(x);
	mpz_init(y);
	mpz_init(z);
	A=malloc(1024*sizeof(char));
	B=malloc(1024*sizeof(char));
	C=malloc(1025*sizeof(char));
	int n;
	printf("Enter the exponent:");
	scanf("%d",&n);
	while(1){
		printf("Enter 1st no:");
		scanf("%s",A);
		printf("Enter 2nd no:");
		scanf("%s",B);
		convert(A,x);
		convert(B,y);	
		mpz_xor(z,x,y);
		convert_rev(z,C);
		adjust(C,n);
		printf("Addition and subtraction is: %s\n",C);
		multiply(A,B,C);
		printf("Multiplication is: %s\n",C);	
	}
	return 0;
}
