/*******************************************************
	Zadanie o fladze holenderskiej:
	===============================
	- Kolory:  Czerwony, biały, niebieski
	- M: ilość urn
	- Urny są ponumerowane od 0 do M-1
	
	Poniższe rozwiązania będą używać następującego 
	niezmiennika dla głównej pętli:
	
		Niezmiennik N(c,b,n): 
			Dla każdego 0 <=k < c: kol(k)=kCzerwony; 
			Dla każdego c <= k < b: kol(k)=kBialy; 
			Dla każdego n < k <= M-1: kol(k)=kNiebieski; 
			0<=c<=b, b-1<=n<=M-1

*******************************************************/

#include <stdio.h>
#include <stdbool.h>


typedef enum {kCzerwony, kBialy, kNiebieski} Kolor;

/** 
	Następujące zmienne są globalne (widoczne w funkcjach)
	(Uwaga: Nie jest dobrym stylem używania zmiennych globalnych!)
	
	W naszym rozwiązaniu używamy jednak tylko zmienną M, oraz funkcje kol() i zam(). Nie czytamy/piszemy bezpośrednio do tablicy urny[].
*/
Kolor urny[] = {kNiebieski, kCzerwony, kBialy, kBialy}; //Przykładowe wejście. Inne: kBialy, kNiebieski, kCzerwony, kBialy, kNiebieski, kCzerwony};
const int M = sizeof(urny) / sizeof(Kolor); //const oznacza że nie wolno zmieniać M

/**
	Pisze porządek urn do standardowego wyjścia.
*/
void print_urny(void) 
{
	for (int i = 0; i < M; ++i) 
	{
		printf("%d", urny[i]);
	}
	printf("\n",M);
}

/**
	Zwraca kolor 'i'-tej urny.
*/
Kolor kol(int i) 
{
	return urny[i];
}

/**
	Zamienia 'i'-ta z 'j'-ta urną. 
	Komunikat że robot się zepsuł jeśli 'i==j'.
*/
void zam(int i, int j) 
{
	if(i==j) 
	{
		printf("Robot się zepsuł!\n");
	}
	int temp = urny[i];
	urny[i] = urny[j];
	urny[j] = temp;
}


	
/** 
	Rozwiązanie (bez optymalizacji)	
*/
void make_netherland_flag_1(void) 
{
	int c = 0, b = 0, n = M-1; //N(c,b,n) zachodzi 

	while (b <= n) //musimy sprawdzić każdy żeton
	{
		if (kol(b) == kBialy) 
		{ //N(c,b,n); kol(b)=biały; to jest najprostszy przypadek
			++b; 
		}
		else if (kol(b) == kNiebieski) 
		{ //N(c,b,n); kol(b)=niebieski
			if (b < n) // Tak na prawdę ten warunek tylko potrzebny w skrajnym przypadku b==n, co się zdarzy tylko raz. 
			{
				zam(b, n); //Jeśli kol(n)=niebieski, to zamieniamy tutaj niepotrzebnie niebieski z niebieskim; patrz poniżej zoptymalizowaną wersję funkcji.
			}
			--n;
		} 
		else 
		{ //N(c,b,n); kol(b)=czerwony; to jest najtrudniejszy przypadek
			if (c < b) 
			{
				zam(c, b); //przed zmianą: kol(c)=biały; kol(b)=czerwony
			}
			++c; //zwiększenie liczników następuje niezależnie od tego, czy coś zamieniliśmy  (c<b) czy nie (c==b)
			++b;
		}
	}
}

/** 
	Optymalizacja 1: (*)likwidacja warunku if (b < n) poprzez zmiany warunku głównej pętli na 'b < n' i rozparzenia przypadku 'b==n' poza pętli
*/
void make_netherland_flag_opt_1(void) 
{
	int c = 0, b = 0, n = M-1; //N(c,b,n) zachodzi

	while (b < n) 
	{
		if (kol(b) == kBialy) 
		{ //N(c,b,n); kol(b)=biały; to jest najprostszy przypadek
			++b; 
		}
		else if (kol(b) == kNiebieski) 
		{ //N(c,b,n); kol(b)=niebieski; b < n
			// (*) Nie musimy już sprawdzać b < n
			zam(b, n); //Jeśli kol(n)=niebieski, to zamieniamy tutaj niepotrzebnie niebieski z niebieskim; patrz poniżej zoptymalizowaną wersję funkcji.
		} 
		else 
		{ //N(c,b,n); kol(b)=czerwony; to jest najtrudniejszy przypadek
			if (c < b) 
			{
				zam(c, b); //przed zmianą: kol(c)=biały; kol(b)=czerwony
			}
			++c; //zwiększenie liczników następuje niezależnie od tego, czy coś zamieniliśmy  (c<b) czy nie (c==b)
			++b;
		}
	}
	if (b == n && c < b && kol(b) == kCzerwony)
	{ // Tylko wtedy musimy jeszcze coś zrobić
		zam(c, b);
	}
}


/**
	Optymalizacja 2A: (*)unika zamiany niebieski z niebieskim, ale za to zostaje nam sprawdzanie 'b<n'
*/
void make_netherland_flag_opt_2a(void) 
{
	int c = 0, b = 0, n = M-1; //N(c,b,n) zachodzi 

	while (b <= n) //musimy sprawdzić każdy żeton
	{
		if (kol(b) == kBialy) 
		{ //N(c,b,n); kol(b)=biały; to jest najprostszy przypadek
			++b; 
		}
		else if (kol(b) == kNiebieski) 
		{ //N(c,b,n); kol(b)=niebieski
			
			// (*) Żeby uniknąć zamiany niebieski z niebieskim
			while (b < n && kol(n) == kNiebieski)
			{
				--n;
			}
			
			if (b < n) 
			{
				// (*) Teraz kol(n)!=niebieski
				zam(b, n); 
			}
			--n;
			
			/* Niefajnie: Kolor żetonu na pozycji 'b' sprawdzamy dwa razy: w następnej iteracji głównej pętli, oraz przed chwilą jak żeton leżał (jeszcze przed zamianą) na pozycji 'n'. */
			
		} 
		else 
		{ //N(c,b,n); kol(b)=czerwony; to jest najtrudniejszy przypadek
			if (c < b) 
			{
				zam(c, b); //przed zmianą: kol(c)=biały; kol(b)=czerwony
			}
			++c; //zwiększenie liczników następuje niezależnie od tego, czy coś zamieniliśmy  (c<b) czy nie (c==b)
			++b;
		}
	}
}


/**
	Optymalizacja 2B: (*) dalsze unikanie sprawdzania koloru tego samego żetonu dwa razy
*/
void make_netherland_flag_opt_2b(void) 
{
	int c = 0, b = 0, n = M-1; //N(c,b,n) zachodzi 

	while (b <= n) //musimy sprawdzić każdy żeton
	{
		if (kol(b) == kBialy) 
		{ //N(c,b,n); kol(b)=biały; to jest najprostszy przypadek
			++b; 
		}
		else if (kol(b) == kNiebieski) 
		{ //N(c,b,n); kol(b)=niebieski
			
				
			// (*) Zmienna zapamiętująca kol(n) żeby kol(n) nie wykonywać więcej niż raz.
			Kolor kolor_n; // == kol(n) jeśli n > b
				
				
			// (*) Wariant 1: (Wada: sprawdzamy 'b < n' jakieś dwa razy więcej niż wcześniej)  
			// ================================================================
			/* if (b < n) 
			{ 	// Unikamy b==n, bo kol(b) już czytaliśmy.
				kolor_n = kol(n);
			}
			while (b < n && kolor_n == kNiebieski) 
			{ //Zmniejszamy n żeby uniknąć zamiany niebieskiego z niebieskim
				--n;
				if (b < n) 
				{
					kolor_n = kol(n);
				}
			} */
			// ================================================================
			
			
			// (*) Wariant 2: (Dobry, ale długi kod)
			// ================================================================
			/* bool wiekszy_i_niebieski; // == b<n && kol(n)==kNiebieski
			if (b < n)
			{
				kolor_n = kol(n); 
				wiekszy_i_niebieski = kolor_n == kNiebieski;
			}
			else
			{
				wiekszy_i_niebieski = false;
			}
			
			while (wiekszy_i_niebieski)
			{
				--n;
				if (b < n)
				{
					kolor_n = kol(n); 
					wiekszy_i_niebieski = kolor_n == kNiebieski;
				}
				else
				{
					wiekszy_i_niebieski = false;
				}
			} */
			// ================================================================
			
			
			// (*) Wariant 3: (Najlepszy)
			// ================================================================
			while (b < n && (kolor_n = kol(n)) == kNiebieski) 
			{ //Zmniejszamy n żeby uniknąć zamiany niebieskiego z niebieskim
				--n;
			}
			// ================================================================
			
			
			if (b < n) 
			{ // kol(n)!=niebieski 
				// (*) Skoro pamiętamy kol(n), możemy zrobić więcej i
				// 	   zapobiec ponownym wczytaniu koloru żetonu 'n'. 
				if (kolor_n == kBialy) 
				{
					zam(b, n);
				}						
				else 
				{ // kol(n)=czerwony (i kol(b)=niebieski), więc musimy n-tą urnę dać do przodu na pozycję c (a c-tą urnę dać na pozycję b, a b-tą urnę na pozycję n).
					zam(n, c);
					if (c < b) 
					{
						zam(n, b);
					}
					++c;
				}
				++b;
				--n;
			}
			else 
			{ // b == n, kol(b) == kol(n) == kNiebieski
				--n; 
			}
		} 
		else 
		{ //N(c,b,n); kol(b)=czerwony; to jest najtrudniejszy przypadek
			if (c < b) 
			{
				zam(c, b); //przed zmianą: kol(c)=biały; kol(b)=czerwony
			}
			++c; //zwiększenie liczników następuje niezależnie od tego, czy coś zamieniliśmy  (c<b) czy nie (c==b)
			++b;
		}
	}
}


/**
	Optymalizacja 2C: kol(b) sprawdzany już tylko raz
*/
void make_netherland_flag_opt_2c(void) 
{
	int c = 0, b = 0, n = M-1; //N(c,b,n) zachodzi 

	while (b <= n) //musimy sprawdzić każdy żeton
	{
		Kolor kolor_b = kol(b);
		if (kolor_b == kBialy) 
		{ //N(c,b,n); kol(b)=biały; to jest najprostszy przypadek
			++b; 
		}
		else if (kolor_b == kNiebieski) 
		{ //N(c,b,n); kol(b)=niebieski
			
			Kolor kolor_n;
			while (b < n && (kolor_n = kol(n)) == kNiebieski) 
			{ //Zmniejszamy n żeby uniknąć zamiany niebieskiego z niebieskim
				--n;
			}
			if (b < n) 
			{ // kol(n)!=niebieski 
				if (kolor_n == kBialy) 
				{
					zam(b, n);
				}						
				else 
				{ // kol(n)=czerwony (i kol(b)=niebieski), więc musimy n-tą urnę dać do przodu na pozycję c (a c-tą urnę dać na pozycję b, a b-tą urnę na pozycję n).
					zam(n, c);
					if (c < b) 
					{
						zam(n, b);
					}
					++c;
				}
				++b;
			}
			--n;
		} 
		else 
		{ //N(c,b,n); kol(b)=czerwony; to jest najtrudniejszy przypadek
			if (c < b) 
			{
				zam(c, b); //przed zmianą: kol(c)=biały; kol(b)=czerwony
			}
			++c; //zwiększenie liczników następuje niezależnie od tego, czy coś zamieniliśmy  (c<b) czy nie (c==b)
			++b;
		}
	}
}


/**
	Optymalizacja 2D: Jak 2C, tylko konstrukcja switch-case zamiast zmiennej 'kol_b'
*/
void make_netherland_flag_opt_2d(void) 
{
	int c = 0, b = 0, n = M-1;
	while (b <= n) 
	{
		switch (kol(b)) //Teraz wczytujemy kol(b) tylko raz
		{
			case kBialy:
				++b;
			break;
			case kNiebieski: 
			{ //Nawiasy w case tylko potrzebne jeśli się deklaruje nową zmienną (poniżej np. int kolor_n)
				Kolor kolor_n;
				while (b < n && (kolor_n = kol(n)) == kNiebieski) 
				{ //Zmniejszamy n żeby uniknąć zamiany niebieskiego z niebieskim
					--n;
				}
				if (b < n) 
				{ // kol(n)!=niebieski 
					if (kolor_n == kBialy) 
					{
						zam(b, n);
					}						
					else 
					{ // kol(n)=czerwony (i kol(b)=niebieski), więc musimy n-tą urnę dać do przodu na pozycję c (a c-tą urnę dać na pozycję b, a b-tą urnę na pozycję n).
						zam(n, c);
						if (c < b) 
						{
							zam(n, b);
						}
						++c;
					}
					++b;
				}
				--n;
			}
			break;
			case kCzerwony:
				if (c < b) 
				{
					zam(c, b);
				}
				++c;
				++b;
			break; // break w ostatnim case już nie potrzebny, ale można dla czytelności dopisać
		}
	}
}


/**
	Optymalizacja 3 (Najlepsze): Łączy pomysły Opt 1 & Opt 2D (Mniej sprawdzań 'b<n')
*/
void make_netherland_flag_opt_3(void) 
{
	int c = 0, b = 0, n = M-1;
	while (b < n) 
	{
		switch (kol(b)) //Teraz wczytujemy kol(b) tylko raz
		{
			case kBialy:
				++b;
			break;
			case kNiebieski: 
			{ //Nawiasy w case tylko potrzebne jeśli się deklaruje nową zmienną (poniżej np. int kolor_n)
				Kolor kolor_n = kol(n); // OK, bo b < n
				if (kolor_n == kNiebieski)
				{
					--n;
					while (b < n && (kolor_n = kol(n)) == kNiebieski) 
					{ //Zmniejszamy n żeby uniknąć zamiany niebieskiego z niebieskim
						--n;
					}
				}
				if (b < n) 
				{ // kol(n)!=niebieski 
					if (kolor_n == kBialy) 
					{
						zam(b, n);
					}						
					else 
					{ // kol(n)=czerwony (i kol(b)=niebieski), więc musimy n-tą urnę dać do przodu na pozycję c (a c-tą urnę dać na pozycję b, a b-tą urnę na pozycję n).
						zam(n, c);
						if (c < b) 
						{
							zam(n, b);
						}
						++c;
					}
					++b;
				}				
				--n;
			}
			break;
			case kCzerwony:
				if (c < b) 
				{
					zam(c, b);
				}
				++c;
				++b;
			break; // break w ostatnim case już nie potrzebny, ale można dla czytelności dopisać
		}
	}
	if (b == n && c < b && kol(b) == kCzerwony)
	{ // Tylko wtedy musimy jeszcze coś zrobić
		zam(c, b);
	}
}


/**
	Alternatywne rozwiązanie z ćwiczeń:
	Za pomocą zmiennej kolor_b skracamy przypadek kol(n) == niebieski. 

	Rozwiązanie nie zawiera optymalizację OPT 1, ale może ją łatwo dodać. 
*/
int make_netherland_flag_alt_var(void) 
{
	int c = 0, b = 0, n = M-1;
	Kolor kolor_b = kol(b);
	Kolor kolor_n; // Deklaracja nie może występować wewnątrz 'case', więc robimy to tutaj. 
	while (b <= n) 
	{
		switch (kolor_b)
		{
		case kBialy:
			++b;
			kolor_b = kol(b);
			break;
		case kNiebieski:
			while (b < n && (kolor_n = kol(n)) == kNiebieski) 
			{ //Zmniejszamy n żeby uniknąć zamiany niebieskiego z niebieskim
				--n;
			}
			if (b < n) 
			{ // kol(n)!=niebieski 
				zam(b, n);
				kolor_b = kolor_n;
				--n;
			}
			break;
		default: //case kCzerwony
			if (c < b) 
			{
				zam(c, b);
			}
			++c;
			++b;
			kolor_b = kol(b);
			break;
		}
	}
}


/** 
	Dwa razy make_polish_flag_2(). Za pierwszym razem dzielimy czerwony od białego i niebieskiego (które traktujemy jako jeden kolor). Za drugim razem dzielimy już tylko biały od niebieskiego.
 */
int make_netherland_flag_via_polish_flag(void) 
{
	int c = 0, x = M-1;
	// Niezmiennik: kol(k)=czerwony dla 0 <= k < c; kol(k)!=czerwony dla x < k <= M-1; zachodzi 0 <= c <= x+1,  x<= M-1 
	while (c < x) {
		if (kol(c) == kCzerwony) 
		{
			++c;
		}
		else 
		{
			while(c < x && kol(x) != kCzerwony) 
			{
				--x;
			}
			if (c < x) 
			{
				zam(c, x);
				++c;
				--x;
			}
		}
	}
	int b = c, n = M-1;
	// Niezmiennik: kol(k)=czerwony dla 0 <= k < c; kol(k)=biały dla c <= k < b; kol(k)=niebieski dla n < k <= M-1; zachodzi 0 <= c <= b <= n+1,  n<= M-1 
	while (b < n) {
		if (kol(b) == kBialy) 
		{
			++b;
		}
		else 
		{
			while(b < n && kol(n) == kNiebieski) 
			{
				--n;
			}
			if (b < n) 
			{
				zam(b, n);
				++b;
				--n;
			}
		}
	}
	
}
	
/**
	Funkcja main wywołująca 
*/
int main(void) {
	print_urny();
	// make_netherland_flag_1();
	// make_netherland_flag_opt_1();
	// make_netherland_flag_opt_2a();
	// make_netherland_flag_opt_2b();
	// make_netherland_flag_opt_2c();
	// make_netherland_flag_opt_2d();
	// make_netherland_flag_opt_3();
	make_netherland_flag_alt_var();
	// make_netherland_flag_via_polish_flag();
	print_urny();
	return 0;
}