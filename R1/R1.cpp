// R1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "gmp.h"

using namespace std;
void simpleViferih();
void findSuperSimple();
void simpleVolstenholm();
void findSimple();
void findSimpleVolstenholm();
void findSimpleViferih();

void clearAllVectors();

mpq_t* getBinomK(mpz_t *N, mpz_t *K);
std::vector<mpz_t*> vectorSimple; // создали пустой вектор типа mpz_t*
//vectorVefirih.reserve(10);          // тут мы зарезервировали память под 10 элементов типа int

int menu();

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(0,"rus");
	int ch=-1;
	while((ch=menu())!=4)
	{
		switch(ch)
		{
		case 1:
			clearAllVectors();
			findSimpleViferih();
			break;
		case 2:
			clearAllVectors();
			findSimpleVolstenholm();
			break;
		case 3:
			clearAllVectors();
			findSuperSimple();
			break;
		case 4:
			break;
		default:
			cout<<"Ошибка ввода, попробуйте ещё раз."<<endl;
		}
	}

	getchar();
	return 0;
}

int menu()
{
	int ch;
	cout<<"1 - поиск простых чисел Вифериха"<<endl
		<<"2 - поиск простых чисел Вольстенхольма"<<endl
		<<"3 - поиск супер простых чисел"<<endl
		<<"4 - выход"<<endl
		<<"?: ";
	cin>>ch;
	return ch;
}

bool isSimpleViferih(mpz_t *P)
{
	mpz_t exp,base,mod,c,p, one;		//целочисленный тип из библиотеки gmp
	mpz_init(mod);
	mpz_init(exp);			//иниц-ем 
	mpz_init(base);			//иниц-ем 
	mpz_init(c);			//иниц-ем 
	mpz_init(p);			//иниц-ем 
	mpz_init(one);			//иниц-ем 

	mpz_init_set_str (one, "1", 10);
	mpz_init_set_str (base, "2", 10);

	mpz_set(p,*P);
	//printf("p = ");
	//gmp_scanf ("%Zd",  p);	//вводим значение

	mpz_sub (exp,p,one);
	mpz_pow_ui(mod,p,2);//возводим значение в квадрат
	mpz_powm(c,base,exp,mod);
	if(mpz_cmp_ui(c,1)==0)
		return true;
	return false;
	//gmp_printf ("\n\np: %Zd\n", p);
	//gmp_printf ("\n\none: %Zd\n", one);
	//gmp_printf ("\n\nexp: %Zd\n", exp);
	//gmp_printf ("\n\nmod: %Zd\n", mod);
	//gmp_printf ("\n\nbase: %Zd\n", base);
	//gmp_printf ("\n\nres: %Zd\n", c);
}

void findSimpleViferih()
{
	findSimple();
	mpz_t index,one;
	mpz_init(index);
	mpz_init(one);
	mpz_set_str(index,"0",10);
	mpz_set_str(one,"1",10);
	printf("\nРезультат:\n");
	while(mpz_get_ui(index)<vectorSimple.size())
	{
		
		if(isSimpleViferih(vectorSimple[mpz_get_ui(index)]))
		{
			printf("Число ");
			gmp_printf ("%Zd", vectorSimple[mpz_get_ui(index)]);
			printf(" является простым числом Вифериха\n");
		}
		//else
		//{
		//    printf("Число ");
		//	gmp_printf ("%Zd", vectorSimple[mpz_get_ui(index)]);
		//	printf(" не является простым числом Вифериха\n");
		//}
		mpz_add(index,index,one);
	}
	printf("\n");
}
char buf[SHRT_MAX/4];
bool isSimpleVolstenholm(mpz_t  *K)
{
	mpz_t *n,*k;		//целочисленный тип из библиотеки gmp
	mpq_t *res,*b;

	n=(mpz_t*) calloc(1,sizeof(mpz_t));
	k=(mpz_t*) calloc(1,sizeof(mpz_t));
	res=(mpq_t*) calloc(1,sizeof(mpq_t));
	b=(mpq_t*) calloc(1,sizeof(mpq_t));
	mpq_init(*b);
	mpz_init(*n);
	mpz_init(*k);			//иниц-ем 
	mpq_init(*res);

	mpz_init_set (*k, *K);
	mpz_mul_ui(*n,*k,2);
	//mpz_init_set_str (*n, "33686", 10);
	
	res = getBinomK(n, k);
	gmp_sprintf ( buf, "%Qi",*res);
	mpz_set_str (*n, buf, 10);
	mpz_pow_ui (*k, *k, 4);
	mpz_mod (*n, *n, *k);
	if(mpz_cmp_ui(*n,2)==0)
		return true;
	else 
		return false;
	//gmp_printf("%Zd\n",*n);
}

void findSimpleVolstenholm()
{

	findSimple();
	mpz_t index,one;
	mpz_init(index);
	mpz_init(one);
	mpz_set_str(index,"0",10);
	mpz_set_str(one,"1",10);
	printf("\nРезультат:\n");
	while(mpz_get_ui(index)<vectorSimple.size())
	{
		if(isSimpleVolstenholm(vectorSimple[mpz_get_ui(index)])==true)
		{
			printf("Число ");
			gmp_printf ("%Zd", vectorSimple[mpz_get_ui(index)]);
			printf(" является простым числом Вольстенхольма\n");
		}
		//else
		//{
		//    printf("Число ");
		//	gmp_printf ("%Zd", vectorSimple[mpz_get_ui(index)]);
		//	printf(" не является простым числом Вольстенхольма\n");
		//}
		mpz_add(index,index,one);
	}
	printf("\n");

	
}

mpq_t* getBinomK(mpz_t *N, mpz_t *K)
{

	mpq_t *res, *a, *b,*n,*k,*oneQ;
	mpz_t *index, *one;

	index=(mpz_t*) calloc(1,sizeof(mpz_t));
	one=(mpz_t*) calloc(1,sizeof(mpz_t));
	res=(mpq_t*) calloc(1,sizeof(mpq_t));
	a=(mpq_t*) calloc(1,sizeof(mpq_t));
	b=(mpq_t*) calloc(1,sizeof(mpq_t));
	n=(mpq_t*) calloc(1,sizeof(mpq_t));
	k=(mpq_t*) calloc(1,sizeof(mpq_t));
	oneQ=(mpq_t*) calloc(1,sizeof(mpq_t));

	mpz_init(*index);	
	mpz_sub (*index,*N,*K);
	mpq_init(*res);			//иниц-ем 
	mpq_init(*a);	
	mpq_init(*b);	
	mpz_init(*one);	
	mpq_init(*k);	
	mpq_init(*n);	
	mpq_init(*oneQ);	
	mpz_init_set_str (*one, "1", 10);
//	mpq_set_str (*oneQ, "1", 10);
	mpq_set_z (*oneQ, *one);
	mpq_set_z (*res, *one);
	//mpq_init_set_str (*oneQ, "1", 10);
	//mpq_set_z (*n, *N);
	mpq_set_z (*k, *K);
	mpq_set_z (*n, *K);
	
	while(mpz_sgn(*index)>0)
	{
		mpz_sub (*index,*index,*one);

		mpq_add(*n,*n,*oneQ);
		mpq_sub (*b,*n,*k);
		mpq_div (*a, *n, *b);
		mpq_mul(*res,*res,*a);
		
	}
	return res;
}

bool isSimple(mpz_t* A)
{
	mpz_t* a;
	mpz_t *n,*k;		//целочисленный тип из библиотеки gmp
	mpq_t *res;

	n=(mpz_t*) calloc(1,sizeof(mpz_t));
	k=(mpz_t*) calloc(1,sizeof(mpz_t));
	res=(mpq_t*) calloc(1,sizeof(mpq_t));
	a=(mpz_t*) calloc(1,sizeof(mpz_t));
	mpz_init(*a);
	mpz_init(*n);
	mpz_init(*k);			//иниц-ем 
	mpq_init(*res);

	mpz_set (*a, *A);
	mpz_set (*n, *a);
	mpz_set (*k, *a);
	mpz_mul_ui(*n,*n, 2);
	//mpz_init_set_str (*k, "16843", 10);
	//char buf[SHRT_MAX*10];
	
	res = getBinomK(n, k);
	
	gmp_sprintf ( buf, "%Qi",*res);
	mpz_set_str (*n, buf, 10);
	mpz_pow_ui (*k, *k, 3);
	mpz_mod (*n, *n, *k);
	if(mpz_cmp_ui(*n,2)==0)
		return true;
	else 
		return false;
	//gmp_printf("%Zd\n",*n);
}

void addSimple_2()
{
	mpz_t *a;
	a=(mpz_t*) calloc(1,sizeof(mpz_t));
	mpz_init_set_str (*a, "2", 10);
	vectorSimple.insert(vectorSimple.end(),a);
}
void addSimple_3()
{
	mpz_t *a;
	a=(mpz_t*) calloc(1,sizeof(mpz_t));
	mpz_init_set_str (*a, "3", 10);
	vectorSimple.insert(vectorSimple.end(),a);
}


void findSimple()
{
	mpz_t *one,*a,*b;
	mpq_t *res;
	//ch=(mpz_t*) calloc(1,sizeof(mpz_t));
	one=(mpz_t*) calloc(1,sizeof(mpz_t));
	res=(mpq_t*) calloc(1,sizeof(mpq_t));
	a=(mpz_t*) calloc(1,sizeof(mpz_t));
	b=(mpz_t*) calloc(1,sizeof(mpz_t));
	mpz_init(*a);
	mpz_init(*b);
	//mpz_set (*ch, *a);
	mpz_init_set_str (*one, "1", 10);

	cout<<"a = ";
	gmp_scanf ("%Zd", a);
	cout<<"b = ";
	gmp_scanf ("%Zd", b);

	if(mpz_cmp_ui(*a,2)<=0)
		addSimple_2();
	if(mpz_cmp_ui(*a,3)<=0)
		addSimple_3();

	while(mpz_cmp(*a,*b)!=0)
	{
		
		if(isSimple(a)==true)
		{
			mpz_t *d;
			d=(mpz_t*) calloc(1,sizeof(mpz_t));
			mpz_init(*d);
			mpz_set(*d,*a);
			vectorSimple.insert(vectorSimple.end(),d);
		}
		mpz_add(*a,*a,*one);
	}

}

void findSuperSimple()
{
	mpz_t index,one,num;
	mpz_init(index);
	mpz_init(one);
	mpz_init(num);
	mpz_set_str(index,"0",10);
	mpz_set_str(one,"1",10);
	findSimple();
	printf("\nРезультат:\n");
	while(true)
	{
	  if(mpz_get_ui(*vectorSimple[mpz_get_ui(index)])>=vectorSimple.size())
	  {
		  break;
	  }
		mpz_sub(num,*vectorSimple[mpz_get_ui(index)],one);
		gmp_printf ("%Zd\n", vectorSimple[mpz_get_ui(num)]);
		mpz_add(index,index,one);
	}
	printf("\n");

}

void clearAllVectors()
{
vectorSimple.clear();
}