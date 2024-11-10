/*******************************************************
	Arytmetyka dużych liczb
	=======================

	- Liczby należą do systemu liczbowego o podstawie 'BASE', 
	  więc każda cyfra należy do przedziału '[0,BASE-1]'.
	- Liczby są reprezentowane przez tablice.
	- Najmniej znacząca cyfra jest na pozycji 0.
	- Ustalamy z góry, że wszystkie tablice mają rozmiar 'N' 
	  z wyjątkiem tablic wynikowych dla funkcji mnożenia które 
	  mają długość '2*N'.
*******************************************************/

#include <stdio.h>

#define BASE 10
#define N 10


/** 
	Pisze zawartość tablicy 'a' o rozmiarze 'n'. 
*/
void print_array(int a[], int n)
{
	for (int i = 0; i < n - 1; ++i) 
	{
		printf("%d, ", a[i]);
	}
	printf("%d\n", a[n - 1]);
}


/** 
	Zwraca 1 jeśli 'a' jest 0, zwraca 0 w innym przypadku.

	Warunki: 'a' ma rozmiar 'N'.
*/
int zero(int a[]) 
{
	int i = LOTTO_SIZE - 1;
	while (i >= 0 && a[i] == 0) // krócej: while (i && !a[i]) z return !a[i]
	{
		--i;
	}
	return i == -1; // Porównania w języku C zwracają wartość 1 jeśli porównane obiekty są równe (w tym przypadku, jeśli 'i' równa się -1), a 0 jeśli są nierówne.
}


/** 
	Zwraca 1 jeśli 'a' jest większy niż 'b', 0 w innym przypadku;

	Warunki: 'a' i 'b' mają po rozmiarze 'N'.
*/
int wieksze(int a[], int b[]) 
{
	int i = LOTTO_SIZE - 1;
	while (i > 0 && a[i] == b[i]) 
	{
		--i;
	}
	return a[i] > b[i];
}


/**
	Zapisuje pierwsze 'N' cyfry sumy 'a+b' w 'c' i zwraca 0 wtw. jeśli suma mieści się całkowicie w 'c';
	
	Warunki: 'a', 'b' i 'c' mają po rozmiarze 'N'.
*/
int suma(int a[], int b[], int c[]) 
{
	int p = 0;
	for (int i = 0; i <= LOTTO_SIZE - 1; ++i) 
	{ // Niezmiennik N(i,p): 
	  //	a[0..i-1] + b[0..i-1] = c[0..i-1] + p*BASE^i
		c[i] = a[i] + b[i] + p;
		if (c[i] >= BASE) 
		{ // Też: c[i] <= BASE-1 + BASE-1 +1 = 2*BASE-1
			c[i] = c[i] - BASE; // Teraz: 0 <= c[i] < BASE
			p = 1;
		} 
		else 
		{
			p = 0;
		}
	}
	return p;
}


/** 
	Zapisuje 'a-b' w 'c';
	
	Warunki: 
		- 'a>=b', oraz
		- 'a', 'b' i 'c' mają po rozmiarze 'N'.
*/
void roznica_minus(int a[], int b[], int c[]) {
	int p = 0;
	for (int i = 0; i <= LOTTO_SIZE - 1; ++i) 
	{ // Niezmiennik N(i,p): 
	  //	a[0..i-1] + p*BASE^i = b[0..i-1] + c[0..i-1]
	  //	p \in {0,1} 
		c[i] = (a[i] - p) - b[i]; //-p zabiera nam p z równania powyżej; następne p zaraz przyjdzie
		if (c[i] < 0) 
		{
			// Mamy: c[i] >= 0 - 1 - (BASE-1), więc -BASE <= c[i] <= -1
			c[i] = c[i] + BASE; // Więc 0 <= c[i] <= BASE-1 d 
			p = 1; // Dodaliśmy do c[0..i] wartość BASE*BASE^i = 1*BASE^{i+1}, 
				   // więc dodajemy też do pierwszej strony równania via 'p'. 
		}
		else 
		{
			p = 0;
		}
	}
	// Tutaj: p==0 bo a>=b oraz c<Base^N
}


/** 
	Zapisuje '|a-b|' w 'c' oraz zwraca 1 wtw. jeśli 'a-b' jest 
	nieujemne, w innym przypadku zwraca -1;
	
	Warunki: 'a', 'b' i 'c' mają po rozmiarze 'N'.
*/
int roznica(int a[], int b[], int c[]) 
{
	int ret = 1;
	if (wieksze(b, a)) 
	{ // b >= a
		roznica_minus(b, a, c);
		ret = -1;
	} 
	else 
	{ //a == b lub a > b 
		roznica_minus(a, b, c);
	}
	return ret;
}


/** 
	Zapisuje 'a*b' w 'c';
	
	Warunki: 
		- 'a' i 'b' mają po rozmiarze 'N', oraz
		- 'c' ma rozmiar '2*N'. 
		- 'BASE*BASE <= INT_MAX'
*/
void iloczyn(int a[], int b[], int c[])
{
/*	Pomysł:
	c 	= a*b 
		= (sum_i a[i]*BASE^i) * (sum_i b[i]*BASE^i) 
		= sum_{i,j} a[i]*b[j]*BASE^{i+j} 
		= sum_k sum_{i+j=k} a[i]*b[j]*BASE^k
	Więc nasuwa się pomysł wyliczenia c[k] = sum_{i+j=k} a[i]*b[j]
	Jednak taka wartość może być większa niż BASE.
	Więc jeśli w = sum_{i+j=k} a[i]*b[j], 
	to zapisujemy c[k]=w%BASE, 
	a podłoga(w/BASE) dajemy dalej do c[k+1]. */

/*	Dostajemy dwa niezmienniki:
		N(i) dla pętli for (int i=0; i<N; ++i): 
			c[0..i-1] jest prawidłowe; 
	 		c[i..] reprezentuje sumę wszystkich a[k]*a[h] 
				dla których k+h>=i && (k<i || h<i). 
		N(i,j) dla pętli for (int j=0; j<N; ++j): 
			c[0..i-1] jest prawidłowe; 
			c[i..]+p*BASE^{i+j} reprezentuje sumę wszystkich a[k]*a[h] 
				dla których k+h>=i && ((k<i || h<i) || (k==i && h<j) || (h==i && k<j));
			0<=p<BASE */
	for (int i = 0; i < LOTTO_SIZE; ++i) // Wystarczy zerować do tylko pozycji i = N-1, 
								// ponieważ dla wyższych pozycji stawiamy już wartość 
								// (w ostatniej linijce drugiej pętli) 
	{
		c[i] = 0;
	}
	for (int i = 0; i < LOTTO_SIZE; ++i) 
	{ // N(i) zachodzi (i=0: trywialnie;  
	  // 			    i+1: N(i+1) wynika z N(i,N) i c[i+N]=p
	  	int p = 0;
		for (int j = 0; j < LOTTO_SIZE; ++j) 
		{ // N(i,j) zachodzi (j=0: N(i,0)=N(i) oraz p=0; 
		  //			      j+1: N(i,j+1) wynika z N(i,j) oraz 
		  //				  	   z obliczenia poniżej)
			int w = a[i] * b[j] + p + c[i + j]; 
			// w <= ((BASE-1)^2 + BASE-1 + BASE-1
			//    = BASE^2 - 1
			c[i + j] = w % BASE;
			p = w / BASE; // p < BASE
		}
		c[i + LOTTO_SIZE] = p;
	}
}


/** 
	(Wariant bez pomocniczej zmiennej 'p' 
		z wadą że częściej piszemy do tablicy 'c')
		
	
	Zapisuje 'a*b' w 'c';
	
	Warunki: 
		- 'a' i 'b' mają po rozmiarze 'N', oraz
		- 'c' ma rozmiar '2*N'. 
		- 'BASE*BASE <= INT_MAX'
*/
void iloczyn_bez_p(int a[], int b[], int c[])
{
/*	Pomysł:
	c 	= a*b 
		= (sum_i a[i]*BASE^i) * (sum_i b[i]*BASE^i) 
		= sum_{i,j} a[i]*b[j]*BASE^{i+j} 
		= sum_k sum_{i+j=k} a[i]*b[j]*BASE^k
	Więc nasuwa się pomysł wyliczenia c[k] = sum_{i+j=k} a[i]*b[j]
	Jednak taka wartość może być większa niż BASE.
	Zatem wyliczamy w = sum_{i+j=k} a[i]*b[j], 
	zapisujemy c[k]=w%BASE, 
	a podłoga(w/BASE) dajemy dalej do c[k+1]. */

/*	Dostajemy dwa niezmienniki:
		N(i) dla pętli for (int i=0; i<N; ++i): 
			c[0..i-1] jest prawidłowe; 
	 		c[i..] reprezentuje sumę wszystkich a[k]*a[h] 
				dla których k+h>=i && (k<i || h<i). 
		N(i,j) dla pętli for (int j=0; j<N; ++j): 
			c[0..i-1] jest prawidłowe; 
			c[i..] reprezentuje sumę wszystkich a[k]*a[h] 
				dla których k+h>=i && ((k<i || h<i) || (k==i && h<j) || (h==i && k<j)); */
	for (int i = 0; i < 2 * LOTTO_SIZE; ++i) 
	{
		c[i] = 0;
	}
	for (int i = 0; i < LOTTO_SIZE; ++i) 
	{ // N(i) zachodzi (i=0: trywialnie;  
	  // 			    i+1: N(i+1) wynika z N(i,N)
		for (int j = 0; j < LOTTO_SIZE; ++j) 
		{ // N(i,j) zachodzi (j=0: N(i,0)=N(i); 
		  //			      j+1: N(i,j+1) wynika z N(i,j) oraz 
		  //				  	   z obliczenia poniżej)
			int w = a[i] * b[j] + c[i + j]; 
			c[i + j] = w % BASE;
			c[i + j + 1] += w / BASE; 
			
			/* Czy wartość 'w' (oraz 'c[i + j + 1]') mieści się w zakresie 'int'?
				Tak, ponieważ przypominając sobie założenie że 'BASE^2 <= INT_MAX'
				możemy rozszerzyć niezmienniki N(i),N(i,j) o stwierdzenia 
					że dla każdego '0<=k<=i+N' mamy 'c[k]<BASE'
				oraz 
					dla każdego 'i+N<k<N' mamy 'c[k]=0'
				z jedynym wyjątkiem w N(i,j) dla j<N
					że 'c[i+j]< 2*BASE-1'.
				
				Dowód: 
				Mamy 'w < (BASE-1)^2 + 2*BASE-1 = BASE^2'.
				To oznacza dla 'j<N-1' że 'c[i+j+1] < BASE-1 + BASE^2/BASE = 2*BASE-1',
				oraz dla j==N-1 że 'c[i+j+1] < 0 + BASE^2/BASE = BASE'.
				Więc niezmienniki zachodzą. 
			*/
				
		}
	}
}

/**
	Przekazuje maximum z 'i' i 'j'.
*/
int max(int i, int j)
{
	return i > j ? i : j;
}

/** 
	(Wariant bez pomocniczej zmiennej 'p' 
		iterujący przez 'c'
		z wadą że częściej piszemy do tablicy 'c'
		i że pozycje 'i' i 'j' muszą być wyliczane)
*/
void iloczyn_bez_p_przez_c(int a[], int b[], int c[])
{
	c[0] = 0;
	for (int k = 0; k < 2*LOTTO_SIZE; ++k)
	{
		c[k + 1] = 0;
		for (int i = max(0, k - LOTTO_SIZE); i < LOTTO_SIZE; ++i)
		{
			int j = k - i;
			c[k] += a[i] * b[j];
			c[k + 1] += c[k] / BASE;
			c[k] %= BASE;
			
			
		}
	}
}

/** 
	Kopiuje zawartość z tablicy 'src' do 'dst';
	
	Warunki: 'src' i 'dest' mają po rozmiarze 'N'.
*/
void copy_array(int src[], int dst[])
{
	for (int i = 0; i < LOTTO_SIZE; ++i) 
	{
		dst[i] = src[i];
	}
}


/** 
	Zapisuje 'podłoga(a/b)' w 'c' oraz 'a%b' w 'rest'; zwraca 0 wtw. jeśli nie mamy dzielenia przez 0 (nie ma "błedów");
	
	Warunki: 'a', 'b' i 'c' mają po rozmiarze 'N'. 
*/
int dzielenie(int a[], int b[], int c[], int rest[]) 
{
		if (zero(b)) 
		{
			return 1; // Niedozwolone dzielenie przez 0
		}
		else 
		{ // b nie jest zerem
			int zero_num[LOTTO_SIZE]; // Reprezentuje 0
			for (int i = 0; i < LOTTO_SIZE; ++i) 
			{
				zero_num[i] = 0;
			}
			int one_num[LOTTO_SIZE]; // Reprezentuje 1
			copy_array(zero_num, one_num);
			one_num[0] = 1;
			
			int cur_prod[LOTTO_SIZE], next_prod[LOTTO_SIZE]; 
			int c_inc[LOTTO_SIZE], c_next_inc[LOTTO_SIZE]; 
			
			copy_array(zero_num, c);
			copy_array(a, rest);
			while (!wieksze(b, rest)) // Dopóki rest >= b
			{ //Inwariant: a-c*b=rest 
				copy_array(one_num, c_inc); // c_inc = 1
				copy_array(b, cur_prod); // cur_prod = b
				suma(c_inc, c_inc, c_next_inc);  // c_inc + c_inc = 2*c_inc
				// c_next_inc = 2*c_inc 
				int overflow = suma(cur_prod, cur_prod, next_prod);  
				// next_prod = 2*cur_prod
				while (!wieksze(next_prod, rest) && !overflow) // Dopóki 2*curr_prod <= rest 
				{ //Inwariant: rest>=cur_prod=c_inc*b and 
				  // 	       next_prod=c_next_inc*b or (overflow=true and c_next_inc*b>rest) and 
				  //           c_next_inc=2*c_inc 
					copy_array(c_next_inc, c_inc);
					copy_array(next_prod, cur_prod);
					suma(c_inc, c_inc, c_next_inc);
					overflow = suma(cur_prod, cur_prod, next_prod); // Jeśli overflow=true, to c_next_inc*b potrzebuje więcej niż N cyfr i jest zatem większe niż rest. 
				}
				suma(c, c_inc, c); 
				roznica(rest, cur_prod, rest);
			}
		}
		return 0;
}


int main(void) 
{
	printf("BASE = %d, N=%d\n\n",BASE,LOTTO_SIZE);
	
	//TUTAJ TWOJE TESTY
	
	//Przykład
	int a[LOTTO_SIZE];
	for (int i = 0; i < LOTTO_SIZE; ++i) 
	{
		a[i] = 0;
	}
	
	int b[LOTTO_SIZE];
	copy_array(a,b);
	a[0] = 7;
	a[1] = 1;
	b[0] = 4;
	
	int c[2 * LOTTO_SIZE];
	iloczyn(a, b, c);
	
	printf("a=");
	print_array(a, LOTTO_SIZE);
	printf("b=");
	print_array(b, LOTTO_SIZE);
	printf("c=");
	print_array(c, 2 * LOTTO_SIZE);
	
	int d[LOTTO_SIZE];
	int rest[LOTTO_SIZE];
	
	dzielenie(a, b, d, rest);
	printf("d=");
	print_array(d, LOTTO_SIZE);
	printf("rest=");
	print_array(rest, LOTTO_SIZE);
	
	return 0;
}